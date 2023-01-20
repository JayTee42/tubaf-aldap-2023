#include <stdio.h>

#define CASE_DIFF ('a' - 'A')
// #define CASE_DIFF 32

void toggle_case(char* str);

int main(void) {
	// Ask the user for their name:
	char name[32 + 1];

	printf("Please enter your name -> ");
	scanf("%32s", name);

	// Toggle upper- / lowercase:
	toggle_case(name);

	// Print the result:
	printf("Your name with toggled case: %s\n", name);
}

void toggle_case(char* str) {
	for (unsigned int i = 0; str[i]; i++) {
		if ((str[i] >= 'A') && (str[i] <= 'Z')) {
			str[i] += CASE_DIFF;
		} else if ((str[i] >= 'a') && (str[i] <= 'z')) {
			str[i] -= CASE_DIFF;
		}
	}
}
