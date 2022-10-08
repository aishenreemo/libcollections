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

int main(void) {
	printf("%s\n", __FILE__);

	UT_INIT();

	test_vector_init();
	test_vector_null();
	test_vector_push();
	test_vector_get();
	test_vector_remove();
	test_vector_drop();

	UT_INFO();
	UT_END();
}
