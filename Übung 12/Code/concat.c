#include <stdio.h>
#include <stdlib.h> // malloc(), free(), size_t

#define MAX_LEN 50
#define FORMAT_STR "%50s"

// Replacement for `strlen()` from <string.h>:
size_t my_strlen(const char* str) {
	const char* start = str;
	for (; *str; str++);
	return str - start;
}

// Replacement for `memcpy()` from <string.h>
// (slightly altered types):
void my_memcpy(char* dst, const char* src, size_t len) {
	for (size_t i = 0; i < len; i++) {
		dst[i] = src[i];
	}
}

char* concat(const char* str1, const char* str2) {
	// Query the lengths of the two strings:
	size_t len1 = my_strlen(str1);
	size_t len2 = my_strlen(str2);

	// Allocate memory for the concatenated string.
	// Don't forget to account for the space and the \0.
	size_t len = len1 + 1 + len2 + 1;
	char* str = malloc(len * sizeof(char));

	if (!str) {
		printf("Failed to allocate memory!\n");
		exit(EXIT_FAILURE);
	}

	// Copy the strings into place:
	my_memcpy(str, str1, len1);
	str[len1] = ' ';
	my_memcpy(&str[len1 + 1], str2, len2 + 1);

	return str;
}

int main(void) {
	// Ask the user for two strings:
	char str1[MAX_LEN + 1], str2[MAX_LEN + 1];

	printf("Please enter the first string -> ");
	scanf(FORMAT_STR, str1);

	printf("Please enter the second string -> ");
	scanf(FORMAT_STR, str2);

	// Concatenate the strings:
	char* str = concat(str1, str2);
	printf("Concatenated string: \"%s\"\n", str);

	// Free the result:
	free(str);
}
