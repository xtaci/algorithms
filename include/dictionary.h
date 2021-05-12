/*******************************************************************************
* DANIEL'S ALGORITHM IMPLEMENTAIONS
*
*  /\  |  _   _  ._ o _|_ |_  ._ _   _
* /--\ | (_| (_) |  |  |_ | | | | | _>
*         _|
* 
* .Net Dictionary Implementation (Cache friendly hash table)
*
******************************************************************************/

#pragma once

#include <cstdint>
#include <cassert>
#include <vector>
#include "hash_code.h"
#include "prime.h"

namespace alg
{

template< typename TKey, typename TValue, typename THash = hash_code<TKey> >
class Dictionary
{
public:
	struct KeyValuePair
	{
		TKey Key;
		TValue Value;
	};

private:
	struct Entry : public KeyValuePair
	{
		int32_t HashCode;
		int32_t Next;

		Entry()
			: HashCode(-1)
			, Next(-1)
		{
		}

		void Reset()
		{
			HashCode = -1;
			Next = -1;
			Key = TKey();
			Value = TValue();
		}
	};

private:
	std::vector<int32_t> m_Buckets;
	std::vector<Entry> m_Entries;
	int32_t m_Count;
	int32_t m_FreeList;
	int32_t m_FreeCount;

	friend class Iterator;
public:

	template<typename DictType, typename EntryType, typename TIter>
	class IteratorBase
	{
	protected:
		DictType* Dict;
		int32_t Index;
		EntryType* Current;

		friend class Dictionary;

		IteratorBase(DictType* dict)
			: Dict(dict)
			, Index(0)
			, Current(nullptr)
		{
		}

	public:
		TIter& operator++()
		{
			while ((uint32_t) Index < (uint32_t) Dict->m_Count)
			{
				if (Dict->m_Entries[Index].HashCode >= 0)
				{
					Current = &Dict->m_Entries[Index];
					Index++;
					return *static_cast<TIter*>(this);
				}
				Index++;
			}

			Index = Dict->m_Count + 1;
			Current = nullptr;
			return *static_cast<TIter*>(this);
		}

		TIter operator++(int32_t)
		{
			TIter tmp = *static_cast<TIter*>(this);
			++(*this);
			return tmp;
		}

		bool operator == (const TIter& other) const
		{
			return Dict == other.Dict
				&& Index == other.Index
				&& Current == other.Current;
		}

		bool operator != (const TIter& other) const
		{
			return !(*this == other);
		}
	};

	class Iterator : public IteratorBase<Dictionary, Entry, Iterator>
	{
		friend class Dictionary;
	private:
		Iterator(Dictionary* dict)
			: IteratorBase<Dictionary, Entry, Iterator>(dict)
		{
		}
	public:
		KeyValuePair& operator*() const
		{
			return *Current;
		}
	};

	class ConstIterator : public IteratorBase<const Dictionary, const Entry, ConstIterator>
	{
		friend class Dictionary;
	private:
		ConstIterator(const Dictionary* dict)
			: IteratorBase<const Dictionary, const Entry, ConstIterator>(dict)
		{
		}
	public:
		const KeyValuePair& operator*() const
		{
			return *Current;
		}
	};

public:
	typedef Iterator iterator;
	typedef ConstIterator const_iterator;

public:
	Dictionary(int32_t capacity = 0)
		: m_Count(0)
		, m_FreeList(-1)
		, m_FreeCount(0)
	{
		_Init(capacity);
	}

	~Dictionary()
	{
		Clear();
	}

	int32_t Size() const
	{
		return m_Count - m_FreeCount;
	}

	TValue& operator[](const TKey& key)
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			return m_Entries[i].Value;
		}
		throw MxKeyNotFoundException();
	}
	const TValue& operator[](const TKey& key) const
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			return m_Entries[i].Value;
		}
		throw MxKeyNotFoundException();
	}

	bool TryGetValue(const TKey& key, TValue& outValue) const
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			outValue = m_Entries[i].Value;
			return true;
		}
		else
		{
			return false;
		}
	}

	TValue TryGetValueOrDefault(const TKey& key, const TValue& defaultValue) const
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			return m_Entries[i].Value;
		}
		else
		{
			return defaultValue;
		}
	}

	const TValue& TryGetValueRefOrDefault(const TKey& key, const TValue& defaultValue) const
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			return m_Entries[i].Value;
		}
		else
		{
			return defaultValue;
		}
	}

	TValue* TryGetValuePtr(const TKey& key)
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			return &m_Entries[i].Value;
		}
		else
		{
			return nullptr;
		}
	}

	const TValue* TryGetValuePtr(const TKey& key) const
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			return &m_Entries[i].Value;
		}
		else
		{
			return nullptr;
		}
	}

	void AddOrUpdate(const TKey& key, const TValue& value)
	{
		_Insert(key, value, false);
	}

	bool ContainsKey(const TKey& key) const
	{
		int32_t i = _FindEntry(key);
		return i >= 0;
	}

	bool Contains(const std::pair<TKey, TValue>& pair) const
	{
		int32_t i = _FindEntry(pair.first);
		return i >= 0 && pair.second == m_Entries[i].Value;
	}

	bool Add(const TKey& key, const TValue& value)
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			return false;
		}

		return _Insert(key, value, true);
	}

	bool Add(const TKey& key, TValue&& value)
	{
		int32_t i = _FindEntry(key);
		if (i >= 0)
		{
			return false;
		}

		return _Insert(key, value, true);
	}

	bool Remove(const TKey& key)
	{
		int32_t hashCode = THash()(key) & 0x7FFFFFFF;
		int32_t bucket = hashCode % m_Buckets.size();
		int32_t last = -1;
		for (int i = m_Buckets[bucket]; i >= 0; last = i, i = m_Entries[i].Next)
		{
			if (m_Entries[i].HashCode == hashCode && m_Entries[i].Key == key)
			{
				if (last < 0)
				{
					m_Buckets[bucket] = m_Entries[i].Next;
				}
				else
				{
					m_Entries[last].Next = m_Entries[i].Next;
				}
				m_Entries[i].HashCode = -1;
				m_Entries[i].Next = m_FreeList;
				m_Entries[i].Key = TKey();
				m_Entries[i].Value = TValue();
				m_FreeList = i;
				m_FreeCount++;

				return true;
			}
		}
		return false;
	}

	void Clear()
	{
		if (m_Count > 0)
		{
			memset(m_Buckets.data(), -1, m_Buckets.size() * sizeof(m_Buckets[0]));
			for (auto& entry : m_Entries)
			{
				entry.Reset();
			}
			m_FreeList = -1;
			m_FreeCount = 0;
			m_Count = 0;
		}
	}

	Iterator Begin()
	{
		return ++Iterator(this);
	}

	ConstIterator Begin() const
	{
		return CBegin();
	}

	ConstIterator CBegin() const
	{
		return ++ConstIterator(this);
	}

	Iterator End()
	{
		Iterator ret(this);
		ret.Index = m_Count + 1;
		ret.Current = nullptr;
		return ret;
	}

	ConstIterator End() const
	{
		return CEnd();
	}

	ConstIterator CEnd() const
	{
		ConstIterator ret(this);
		ret.Index = m_Count + 1;
		ret.Current = nullptr;
		return ret;
	}

	//STL style
	iterator begin()
	{
		return Begin();
	}

	const_iterator begin() const
	{
		return CBegin();
	}

	const_iterator cbegin() const
	{
		return CBegin();
	}

	iterator end()
	{
		return End();
	}

	const_iterator end() const
	{
		return CEnd();
	}

	const_iterator cend() const
	{
		return CEnd();
	}
private:
	int32_t _FindEntry(const TKey& key) const
	{
		if (m_Buckets.size() > 0)
		{
			int32_t hashCode = THash()(key) & 0x7FFFFFFF;
			for (int32_t i = m_Buckets[hashCode % m_Buckets.size()]; i >= 0; i = m_Entries[i].Next)
			{
				if (m_Entries[i].HashCode == hashCode && m_Entries[i].Key == key)
				{
					return i;
				}
			}
		}
		return -1;
	}

	void _Init(int32_t capacity)
	{
		int32_t size = GetNextPrime(capacity);
		m_Buckets.clear();
		m_Buckets.resize(size, -1);
		m_Entries.clear();
		m_Entries.resize(size);
		m_FreeList = -1;
	}

	template<typename TValueRef>
	bool _Insert(const TKey& key, TValueRef value, bool add)
	{
		if (m_Buckets.size() == 0)
		{
			_Init(3);
		}

		int32_t hashCode = THash()(key) & 0x7FFFFFFF;
		int32_t targetBucket = hashCode % m_Buckets.size();

		for (int32_t i = m_Buckets[targetBucket]; i >= 0; i = m_Entries[i].Next)
		{
			if (m_Entries[i].HashCode == hashCode && m_Entries[i].Key == key)
			{
				if (add)
				{
					return false;
				}
				m_Entries[i].Value = value;
				return true;
			}
		}

		int32_t index;
		if (m_FreeCount > 0)
		{
			index = m_FreeList;
			m_FreeList = m_Entries[index].Next;
			m_FreeCount--;
		}
		else
		{
			if (m_Count == m_Entries.size())
			{
				_Resize();
				targetBucket = hashCode % m_Buckets.size();
			}
			index = m_Count;
			m_Count++;
		}

		m_Entries[index].HashCode = hashCode;
		m_Entries[index].Next = m_Buckets[targetBucket];
		m_Entries[index].Key = key;
		m_Entries[index].Value = value;

		m_Buckets[targetBucket] = index;

		return true;
	}

	void _Resize()
	{
		_Resize(GetNextPrime(m_Count * 2), false);
	}

	void _Resize(int32_t newSize, bool forceNewHashCodes)
	{
		assert(newSize >= m_Entries.size());

		m_Buckets.resize(0);
		m_Buckets.resize(newSize, -1);
		m_Entries.resize(newSize);

		if (forceNewHashCodes)
		{
			for (int32_t i = 0; i < m_Count; i++)
			{
				if (m_Entries[i].HashCode != -1)
				{
					m_Entries[i].HashCode = (THash()(m_Entries[i].Key) & 0x7FFFFFFF);
				}
			}
		}
		for (int32_t i = 0; i < m_Count; i++)
		{
			if (m_Entries[i].HashCode >= 0)
			{
				int32_t bucket = m_Entries[i].HashCode % newSize;
				m_Entries[i].Next = m_Buckets[bucket];
				m_Buckets[bucket] = i;
			}
		}
	}


	static int GetNextPrime(int n)
	{
		static const int c_PrimeArraySize = 72;
		static const int c_Primes[c_PrimeArraySize] =
		{
			3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919,
			1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591,
			17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,
			187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263,
			1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369
		};
		static const int c_HashPrime = 101;

		if (n < 0)
		{
			return -1;
		}

		for (int i = 0; i < c_PrimeArraySize; i++)
		{
			int prime = c_Primes[i];
			if (prime >= n)
			{
				return prime;
			}
		}

		//outside of our predefined table. 
		//compute the hard way. 
		for (int i = (n | 1); i < INT32_MAX; i += 2)
		{
			if (is_prime(i) && ((i - 1) % c_HashPrime != 0))
			{
				return i;
			}
		}
		return n;
	}
};

}