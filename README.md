# Algorithms & Data Structures in C++

## Build Status
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)

---

## **目标 (Goal):**
- 实现经典算法 (Classical algorithms implementations)
- 服务器端开发 (Linux/GCC based)
- 保证正确性、易于使用和改造 (Correctness, ease of use, and extensibility)
- 每个算法一个 `.h` 文件，并附带一个对应的演示程序 (One `.header` file per algorithm with a corresponding demo)
- **Graph output format:** Graphviz Dot格式 (e.g., `demograph`)

---

## **约定 (Conventions):**
1. 每个算法用一个 `.h` 文件表示，存放在 `include/` 文件夹下  
   (Each algorithm is represented by a `.h` file in the `include/` directory).
2. 演示程序放在 `src/` 文件夹下  
   (Demo programs are stored in the `src/` directory).
3. **Coding Standards:**  
   - Use 4 spaces for indentation (`TAB = 4` spaces).
   - Set `ts=4` in Vim for consistent spacing.
4. **Contribution Guidelines:**
   - Fork the repository, create new branches, and submit pull requests.
   - Ensure correctness before submitting. This is of utmost importance!
5. **Graph Output:** Graphs should follow the Graphviz Dot format.

---

## **已实现 (Implemented):**
| **Name**                           | **File**                                                                 |
|------------------------------------|--------------------------------------------------------------------------|
| Array shuffle                      | [shuffle.h](https://github.com/xtaci/algorithms/blob/master/include/shuffle.h) |
| Prime test (Trial Division)        | [prime.h](https://github.com/xtaci/algorithms/blob/master/include/prime.h) |
| Prime test (Miller-Rabin)          | [prime.h](https://github.com/xtaci/algorithms/blob/master/include/prime.h) |
| 2D Array                           | [2darray.h](https://github.com/xtaci/algorithms/blob/master/include/2darray.h) |
| Arbitrary Integer                  | [integer.h](https://github.com/xtaci/algorithms/blob/master/include/integer.h) |
| Linear congruential generator      | [random.h](https://github.com/xtaci/algorithms/blob/master/include/random.h) |
| Maximum subarray problem           | [max_subarray.h](https://github.com/xtaci/algorithms/blob/master/include/max_subarray.h) |
| Bit-Set                            | [bitset.h](https://github.com/xtaci/algorithms/blob/master/include/bitset.h) |
| Queue                              | [queue.h](https://github.com/xtaci/algorithms/blob/master/include/queue.h) |
| Stack                              | [stack.h](https://github.com/xtaci/algorithms/blob/master/include/stack.h) |
| Binary Heap                        | [heap.h](https://github.com/xtaci/algorithms/blob/master/include/heap.h) |
| Fibonacci Heap                     | [fib-heap.h](https://github.com/xtaci/algorithms/blob/master/include/fib-heap.h) |
| Priority Queue (List-based)        | [priority_queue.h](https://github.com/xtaci/algorithms/blob/master/include/priority_queue.h) |
| ... (List continues below)         |                                                                           |

<details>
<summary>Click to view the full list</summary>

| **Sorting Algorithms**             | **File**                                                                 |
|------------------------------------|--------------------------------------------------------------------------|
| Bubble Sort                        | [bubble_sort.h](https://github.com/xtaci/algorithms/blob/master/include/bubble_sort.h) |
| Selection Sort                     | [selection_sort.h](https://github.com/xtaci/algorithms/blob/master/include/selection_sort.h) |
| Insertion Sort                     | [insertion_sort.h](https://github.com/xtaci/algorithms/blob/master/include/insertion_sort.h) |
| Shell Sort                         | [shell_sort.h](https://github.com/xtaci/algorithms/blob/master/include/shell_sort.h) |
| Radix Sort                         | [radix_sort.h](https://github.com/xtaci/algorithms/blob/master/include/radix_sort.h) |
| QuickSort                          | [quick_sort.h](https://github.com/xtaci/algorithms/blob/master/include/quick_sort.h) |
| Merge Sort                         | [merge_sort.h](https://github.com/xtaci/algorithms/blob/master/include/merge_sort.h) |
| ...

</details>

---

## **贡献者 (Contributors):**
- **Samana:** Heavy work on MSVC compatibility.
- **Wycg1984:** K-Means implementation.
- **Xmuliang:** HeapSort, Kruskal MST.
- **Wyh267:** Base64, LRU, Bubble Sort, Selection Sort.
- **ZhangYou0122:** Push-Relabel Algorithm, Suffix Tree.
- **UsingtcNower:** Suffix Array.
- **Afernandez90:** AVL Trees.

---

## **如何贡献 (How to Contribute):**
1. Fork the repository.
2. Implement or improve algorithms in the `include/` folder. Add corresponding demos to `src/`.
3. Ensure the implementation is correct and adheres to the project conventions.
4. Create a pull request with a detailed description of your changes.
5. Your code will be reviewed and merged upon approval.

---

## **License**
This project is licensed under the MIT License. See the `LICENSE` file for more details.
