#include "sort.h"

/**
 * swap_ints - a function that swaps two integers in an array.
 * @a: first integer to swap.
 * @b: second integer to swap.
 */
void swap_ints(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * bitonic_merge - a function that sorts a bitonic sequence
 * inside an array of integers.
 * @array: array of integers.
 * @size: size of the array.
 * @start: starting index of the sequence in array to sort.
 * @seq: size of the sequence to sort.
 * @flow: direction to sort in.
 */
void bitonic_merge(int *array, size_t size, size_t start, size_t seq,
		char flow)
{
	size_t x, jump = seq / 2;

	if (seq > 1)
	{
		for (x = start; x < start + jump; x++)
		{
			if ((flow == UP && array[x] > array[x + jump]) ||
			    (flow == DOWN && array[x] < array[x + jump]))
				swap_ints(array + x, array + x + jump);
		}
		bitonic_merge(array, size, start, jump, flow);
		bitonic_merge(array, size, start + jump, jump, flow);
	}
}

/**
 * bitonic_seq - a function that converts an array of integers into a
 * bitonic sequence.
 * @array: array of integers.
 * @size: size of the array.
 * @start: starting index of a block of the building bitonic sequence.
 * @seq: size of a block of the building bitonic sequence.
 * @flow: direction to sort the bitonic sequence block in.
 */
void bitonic_seq(int *array, size_t size, size_t start, size_t seq, char flow)
{
	size_t cut = seq / 2;
	char *str = (flow == UP) ? "UP" : "DOWN";

	if (seq > 1)
	{
		printf("Merging [%lu/%lu] (%s):\n", seq, size, str);
		print_array(array + start, seq);

		bitonic_seq(array, size, start, cut, UP);
		bitonic_seq(array, size, start + cut, cut, DOWN);
		bitonic_merge(array, size, start, seq, flow);

		printf("Result [%lu/%lu] (%s):\n", seq, size, str);
		print_array(array + start, seq);
	}
}

/**
 * bitonic_sort - a function that sorts an array of integers in
 * ascending order using the bitonic sort algorithm.
 * @array: array of integers.
 * @size: size of the array.
 *
 * Description: prints the array after each swap.
 */
void bitonic_sort(int *array, size_t size)
{
	if (array == NULL || size < 2)
		return;

	bitonic_seq(array, size, 0, size, UP);
}
