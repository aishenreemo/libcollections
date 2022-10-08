#include <libcollections/vector.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "unit_test.h"

vector_t test_vec;
vector_result_t test_resvec;

void test_vector_init() {
	UT_TEST();
	UT_NAME("test_vector_init");

	vector_init(&test_vec, &test_resvec);

	UT_ASSERT("vector_init failed.", test_resvec == VECTOR_RESULT_SUCCESS);
	UT_SUCCEED();
}

void test_vector_null() {
	UT_TEST();
	UT_NAME("test_vector_push_vec_null");

	vector_init(NULL, &test_resvec);
	UT_ASSERT("vector_init unknown behavior.", test_resvec == VECTOR_RESULT_UNDEFINED);

	vector_push(NULL, NULL, &test_resvec);
	UT_ASSERT("vector_push unknown behavior.", test_resvec == VECTOR_RESULT_UNDEFINED);

	vector_push(&test_vec, NULL, &test_resvec);
	UT_ASSERT("vector_push item not null.", test_resvec == VECTOR_RESULT_PUSH_ITEM_INVALID);

	vector_get(NULL, 0, &test_resvec);
	UT_ASSERT("vector_get unknown behavior.", test_resvec == VECTOR_RESULT_UNDEFINED);

	vector_remove(NULL, 0, &test_resvec);
	UT_ASSERT("vector_remove unknown behavior.", test_resvec == VECTOR_RESULT_UNDEFINED);

	UT_SUCCEED();
}

void test_vector_push() {
	UT_TEST();
	UT_NAME("test_vector_push");

	const char *str = "test string";
	char *test_output = calloc(sizeof(char), strlen(str) + 1);
	strcpy(test_output, str);

	vector_push(&test_vec, test_output, &test_resvec);

	UT_ASSERT("vector_push failed.", test_resvec == VECTOR_RESULT_SUCCESS);
	UT_SUCCEED();
}

void test_vector_get() {
	UT_TEST();
	UT_NAME("test_vector_get");

	char *test_output = vector_get(&test_vec, 0, &test_resvec);

	// printf("%s\n", test_output);
	// test string

	UT_ASSERT("vector_get failed.", test_resvec == VECTOR_RESULT_SUCCESS);
	UT_SUCCEED();
}

void test_vector_remove() {
	UT_TEST();
	UT_NAME("test_vector_remove");

	vector_remove(&test_vec, 0, &test_resvec);
	UT_ASSERT("vector_remove failed.", test_resvec == VECTOR_RESULT_SUCCESS);
	UT_ASSERT("vector_length unexpected", test_vec.length == 0);

	vector_get(&test_vec, 0, &test_resvec);
	UT_ASSERT("vector_remove doesnt remove item.", test_resvec == VECTOR_RESULT_GET_INDEX_OVERLAP);

	UT_SUCCEED();
}

void test_vector_drop() {
	UT_TEST();
	UT_NAME("test_vector_remove");

	vector_drop(&test_vec);

	UT_SUCCEED();
}

void test_vector_concat() {
	UT_TEST();
	UT_NAME("test_vector_concat");

	bool init_success_vec1;
	bool init_success_vec2;
	bool push_success_vec1[3];
	bool push_success_vec2[3];
	bool concat_success = true;

	vector_t local_test_vec1;
	vector_t local_test_vec2;
	vector_init(&local_test_vec1, &test_resvec);
	init_success_vec1 = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_init(&local_test_vec2, &test_resvec);
	init_success_vec2 = test_resvec == VECTOR_RESULT_SUCCESS;

	char *a = malloc(sizeof(char)); *a = 'a';
	char *b = malloc(sizeof(char)); *b = 'b';
	char *c = malloc(sizeof(char)); *c = 'c';
	vector_push(&local_test_vec1, a, &test_resvec);
	push_success_vec1[0] = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_push(&local_test_vec1, b, &test_resvec);
	push_success_vec1[1] = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_push(&local_test_vec1, c, &test_resvec);
	push_success_vec1[2] = test_resvec == VECTOR_RESULT_SUCCESS;

	char *d = malloc(sizeof(char)); *d = 'd';
	char *e = malloc(sizeof(char)); *e = 'e';
	char *f = malloc(sizeof(char)); *f = 'f';
	vector_push(&local_test_vec2, d, &test_resvec);
	push_success_vec2[0] = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_push(&local_test_vec2, e, &test_resvec);
	push_success_vec2[1] = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_push(&local_test_vec2, f, &test_resvec);
	push_success_vec2[2] = test_resvec == VECTOR_RESULT_SUCCESS;

	vector_concat(&local_test_vec1, &local_test_vec2, sizeof(char), &test_resvec);
	const char expected_vec[6] = {'a', 'b', 'c', 'd', 'e', 'f'};

	for (uint i = 0; i < 6; i++) {
		char *ch = vector_get(&local_test_vec1, i, &test_resvec);

		if (test_resvec != VECTOR_RESULT_SUCCESS) {
			concat_success = false;
			break;
		}

		if (*ch != expected_vec[i]) {
			concat_success = false;
			break;
		}
	}

	vector_drop(&local_test_vec1);
	vector_drop(&local_test_vec2);

	UT_ASSERT("init failed vec 1", init_success_vec1);
	UT_ASSERT("init failed vec 2", init_success_vec2);
	UT_ASSERT(
		"push failed vec 1",
		push_success_vec1[0] && push_success_vec1[1] && push_success_vec1[2]
	);
	UT_ASSERT(
		"push failed vec 1",
		push_success_vec1[0] && push_success_vec1[1] && push_success_vec1[2]
	);
	UT_ASSERT("concat failed", concat_success);

	UT_SUCCEED();
}

void test_vector_clear() {
	UT_TEST();
	UT_NAME("test_vector_clear");

	bool init_success_vec;
	bool clear_before;
	bool clear_after;

	vector_t local_test_vec;
	vector_init(&local_test_vec, &test_resvec);
	init_success_vec = test_resvec == VECTOR_RESULT_SUCCESS;

	char *a = malloc(sizeof(char)); *a = 'a';
	char *b = malloc(sizeof(char)); *b = 'b';
	char *c = malloc(sizeof(char)); *c = 'c';
	vector_push(&local_test_vec, a, &test_resvec);
	vector_push(&local_test_vec, b, &test_resvec);
	vector_push(&local_test_vec, c, &test_resvec);

	const char expected_vec_before[3] = {'a', 'b', 'c'};
	clear_before = local_test_vec.length == 3 && test_resvec == VECTOR_RESULT_SUCCESS;
	for (uint i = 0; i < 3; i++) {
		char *ch = vector_get(&local_test_vec, i, &test_resvec);

		if (test_resvec != VECTOR_RESULT_SUCCESS) {
			clear_before = false;
			break;
		}

		if (*ch != expected_vec_before[i]) {
			clear_before = false;
			break;
		}
	}

	vector_clear(&local_test_vec, &test_resvec);
	clear_after = local_test_vec.length == 0 && test_resvec == VECTOR_RESULT_SUCCESS;

	vector_drop(&local_test_vec);

	UT_ASSERT("init failed vec", init_success_vec);
	UT_ASSERT("unexpected clear before vec", clear_before);
	UT_ASSERT("unexpected clear after vec", clear_after);
	UT_SUCCEED();
}

void test_vector_copy() {
	UT_TEST();
	UT_NAME("test_vector_copy");

	bool init_success_vec1;
	bool init_success_vec2;
	bool push_success_vec1[3];
	bool push_success_vec2[3];
	bool copy_success = true;

	vector_t local_test_vec1;
	vector_t local_test_vec2;
	vector_init(&local_test_vec1, &test_resvec);
	init_success_vec1 = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_init(&local_test_vec2, &test_resvec);
	init_success_vec2 = test_resvec == VECTOR_RESULT_SUCCESS;

	char *a = malloc(sizeof(char)); *a = 'a';
	char *b = malloc(sizeof(char)); *b = 'b';
	char *c = malloc(sizeof(char)); *c = 'c';
	vector_push(&local_test_vec1, a, &test_resvec);
	push_success_vec1[0] = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_push(&local_test_vec1, b, &test_resvec);
	push_success_vec1[1] = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_push(&local_test_vec1, c, &test_resvec);
	push_success_vec1[2] = test_resvec == VECTOR_RESULT_SUCCESS;

	char *d = malloc(sizeof(char)); *d = 'd';
	char *e = malloc(sizeof(char)); *e = 'e';
	char *f = malloc(sizeof(char)); *f = 'f';
	vector_push(&local_test_vec2, d, &test_resvec);
	push_success_vec2[0] = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_push(&local_test_vec2, e, &test_resvec);
	push_success_vec2[1] = test_resvec == VECTOR_RESULT_SUCCESS;
	vector_push(&local_test_vec2, f, &test_resvec);
	push_success_vec2[2] = test_resvec == VECTOR_RESULT_SUCCESS;

	vector_copy(&local_test_vec1, &local_test_vec2, sizeof(char), &test_resvec);
	const char expected_vec[3] = {'d', 'e', 'f'};

	for (uint i = 0; i < 3; i++) {
		char *ch = vector_get(&local_test_vec1, i, &test_resvec);

		if (test_resvec != VECTOR_RESULT_SUCCESS) {
			copy_success = false;
			break;
		}

		if (*ch != expected_vec[i]) {
			copy_success = false;
			break;
		}
	}

	vector_drop(&local_test_vec1);
	vector_drop(&local_test_vec2);

	UT_ASSERT("init failed vec 1", init_success_vec1);
	UT_ASSERT("init failed vec 2", init_success_vec2);
	UT_ASSERT(
		"push failed vec 1",
		push_success_vec1[0] && push_success_vec1[1] && push_success_vec1[2]
	);
	UT_ASSERT(
		"push failed vec 1",
		push_success_vec1[0] && push_success_vec1[1] && push_success_vec1[2]
	);
	UT_ASSERT("copy failed", copy_success);

	UT_SUCCEED();
}

int main(void) {
	printf("%s\n", __FILE__);

	UT_INIT();

	test_vector_init();
	test_vector_null();
	test_vector_push();
	test_vector_get();
	test_vector_remove();
	test_vector_drop();

	test_vector_concat();
	test_vector_clear();
	test_vector_copy();

	UT_INFO();
	UT_END();
}
