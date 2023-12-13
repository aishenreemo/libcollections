#include "vec.h"


int main() {
	struct vec_t num_vec;
	int num;

	vec_init(&num_vec, sizeof(int));

	num = 1;
	vec_push(&num_vec, &num);

	num = 2;
	vec_push(&num_vec, &num);

	num = 3;
	vec_push(&num_vec, &num);

	vec_drop(&num_vec);
}
