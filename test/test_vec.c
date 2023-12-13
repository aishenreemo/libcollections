#include <stdio.h>
#include "vec.h"


int main() {
	struct vec_t num_vec;

	vec_init(&num_vec, sizeof(int));

	vec_push(&num_vec, &(int) {1});
	vec_push(&num_vec, &(int) {2});
	vec_push(&num_vec, &(int) {3});

	for (int i = 0; i < num_vec.length; i++) {
		printf("%d ", *(int *) vec_get(&num_vec, i));
	}

	printf("\n");

	vec_drop(&num_vec);
}
