#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>

typedef struct {
	int x, y;
} point_t;

double calc_euclidean_dist(point_t p0, point_t p1) {
	double dist_x = (double)p1.x - (double)p0.x;
	double dist_y = (double)p1.y - (double)p0.y;

	// I checked, `pow()` is optimized away here :)
	// So yeah, let's use it.
	return sqrt(pow(dist_x, 2) + pow(dist_y, 2));
}

typedef struct {
	point_t center;
	unsigned int radius;
} circle_t;

int check_collision(circle_t c0, circle_t c1) {
	double touch_dist = c0.radius + c1.radius;
	return calc_euclidean_dist(c0.center, c1.center) < touch_dist;
}

unsigned int ask_circle_count(void) {
	printf("Please enter the number of circles -> ");

	unsigned int count;
	scanf("%u", &count);

	if (count == 0) {
		printf("No circles, boring!");
		exit(0);
	}

	return count;
}

circle_t* generate_circles(unsigned int count) {
	// Allocate heap memory for the circles:
	circle_t* circles = malloc(count * sizeof(circle_t));

	if (!circles) {
		printf("Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	// Fill it with random data:
	for (unsigned int i = 0; i < count; i++) {
		circles[i] = (circle_t) {
			.center = { .x = rand() % 100, .y = rand() % 100 },
			.radius = 5 + (rand() % 36) // 5 ... 40
		};
	}

	return circles;
}

void walk_circles(const circle_t* circles, unsigned int count) {
	for (unsigned int i = 0; i < count; i++) {
		// Print info about the current circle:
		circle_t circ = circles[i];

		printf(
			"[%u] { center = (%d, %d), radius = %u }\n",
			i, circ.center.x, circ.center.y, circ.radius
		);

		// Check for collisions:
		for (unsigned int j = i + 1; j < count; j++) {
			if (check_collision(circ, circles[j])) {
				printf(" - Collides with %u.\n", j);
			}
		}
	}
}

int main(void) {
	// Initialize the random number generator:
	srand(time(NULL));

	// Ask the user for the number of circles:
	unsigned int count = ask_circle_count();

	// Allocate the array and fill it with random circles:
	circle_t* circles = generate_circles(count);

	// Print the circles and their collisions:
	walk_circles(circles, count);

	// Free the heap memory containing the circles:
	free(circles);
}
