#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ask_array_length(void) {
	unsigned int length;

	printf("Please enter the array length -> ");
	scanf("%u", &length);

	if (length == 0) {
		printf("That's boring!\n");
		exit(0);
	}

	return length;
}

void fill_array(int* numbers, unsigned length) {
	for (unsigned int i = 0; i < length; i++) {
		numbers[i] = 1 + (rand() % 100);
	}
}

void calc_stats(
	const int* numbers,
	unsigned int length,
	int* min,
	int* max,
	double* avg
) {
	// Use the first array element for init:
	int curr_min = numbers[0], curr_max = numbers[0];
	double sum = numbers[0];

	for (unsigned int i = 1; i < length; i++) {
		int num = numbers[i];

		// Update the statistics with the current element:
		if (num > curr_max) {
			curr_max = num;
		}

		if (num < curr_min) {
			curr_min = num;
		}

		sum += (double)num;
	}

	// Write the statistics to the output pointers:
	*min = curr_min;
	*max = curr_max;
	*avg = sum /= length;
}

int main(void) {
	// Seed the random number generator:
	srand(time(NULL));

	// Read length dynamically:
	unsigned int length = ask_array_length();

	// Allocate the array:
	// Don't do that (VLA: Variable-length array on stack):
	// --> int numbers[length]; <--
	// Instead, use the heap:
	int* numbers = malloc(length * sizeof(int));

	if (!numbers) {
		printf("Sorry, out of memory :(\n");
		exit(-1);
	}

	// Fill with random integers:
	fill_array(numbers, length);

	// Calculate statistics:
	int min, max;
	double avg;

	calc_stats(numbers, length, &min, &max, &avg);

	// Print the result:
	printf("Min: %d, max: %d, average: %.3lf\n", min, max, avg);

	// Free the heap-allocated array:
	free(numbers);
}