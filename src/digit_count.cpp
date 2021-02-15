// printing numbers upto a given length

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

void print(int *data, int start, int limit)
{
	int value = 0;
	if (limit == 0)
	{
		for (int i = 0; i < start; i++)
		{
			value = value * 10 + data[i];
		}
		printf("%d", value);
		printf("\n");
	}
	else
	{
		for (int i = 0; i <= 9; i++)
		{
			data[start] = i;
			print(data, start + 1, limit - 1);
		}
	}
}

void main()
{
	int data[100] = { 0 }, num;
	printf("enter a number: ");
	scanf("%d", &num);
	print(data, 0, num-1);
	system("pause");
}