#include <execinfo.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "vec.h"


#define VEC_INITIAL_CAPACITY 6

#define VEC_FATAL_ERR(condition, msg, ...)							\
	do {											\
		if (condition) {								\
			fprintf(stderr, "%s: " msg, __func__, ##__VA_ARGS__);	\
			vec_print_trace();							\
			exit(EXIT_FAILURE);							\
		}										\
	} while (false)


static void vec_print_trace() {
	void *array[40];
	size_t size = backtrace(array, 40);
	char **strings = backtrace_symbols(array, size);

	if (strings == NULL) return;

	printf("\t\e[31mobtained %ld stack frames.\n", size);
	for (int i = 0; i < size; i++) {
		printf("\t\t%d: %s\n", i, strings[i]);
	}

	printf("\e[0m\n");

	free(strings);
}


void vec_init(struct vec_t *const vec, size_t size) {
	VEC_FATAL_ERR(vec == NULL, "invalid argument.");
	VEC_FATAL_ERR(size == 0, "size cannot be \033[1m0\033[0m.");

	vec->capacity = 6;
	vec->length = 0;

	vec->items = calloc(sizeof(void *), vec->capacity);
	vec->size = size;

	VEC_FATAL_ERR(vec->items == NULL, "failed to calloc.");
}


void vec_push(struct vec_t *const vec, void const *const item) {
	VEC_FATAL_ERR(vec == NULL, "invalid argument.");
	VEC_FATAL_ERR(item == NULL, "invalid argument.");
	VEC_FATAL_ERR(vec->items == NULL, "vec is not initialized");

	if (vec->capacity <= vec->length + 1) {
		vec->capacity *= 2;
		vec->items = realloc(vec->items, sizeof(void *) * vec->capacity);

		VEC_FATAL_ERR(vec->items == NULL, "failed to realloc");
	}

	void *item_copy = malloc(vec->size);

	VEC_FATAL_ERR(item_copy == NULL, "failed to malloc.");

	memcpy(item_copy, item, vec->size);
	vec->items[vec->length] = item_copy;
	vec->length += 1;
}


void vec_insert(struct vec_t *const vec, void const *const restrict item, size_t index) {
	VEC_FATAL_ERR(vec == NULL, "invalid argument.");
	VEC_FATAL_ERR(item == NULL, "invalid argument.");
	VEC_FATAL_ERR(vec->items == NULL, "vec is not initialized");

	if (vec->capacity <= vec->length + 1) {
		vec->capacity *= 2;
		vec->items = realloc(vec->items, sizeof(void *) * vec->capacity);

		VEC_FATAL_ERR(vec->items == NULL, "failed to realloc");
	}

	void *item_copy = malloc(vec->size);

	VEC_FATAL_ERR(item_copy == NULL, "failed to malloc.");

	memcpy(item_copy, item, vec->size);

	VEC_FATAL_ERR(index < 0 || index > vec->length, "index out of bounds.");

	for (int i = index; i < vec->length; i++) {
		vec->items[i + 1] = vec->items[i];
	}

	vec->items[index] = item_copy;
	vec->length += 1;
}


void vec_remove(struct vec_t *const vec, size_t index) {
	VEC_FATAL_ERR(vec == NULL, "invalid argument.");
	VEC_FATAL_ERR(vec->items == NULL, "vec is not initialized.");
	VEC_FATAL_ERR(index >= vec->length, "index overlap.");

	free(vec->items[index]);
	for (uint i = index; i + 1 < vec->length; i++) {
		vec->items[i] = vec->items[i + 1];
	}

	vec->length -= 1;
}


void *vec_get(struct vec_t const *const vec, size_t index) {
	VEC_FATAL_ERR(vec == NULL, "invalid argument.");
	VEC_FATAL_ERR(vec->items == NULL, "vec is not initialized.");
	VEC_FATAL_ERR(index >= vec->length, "index overlap.");

	return vec->items[index];
}


void vec_concat(struct vec_t *const dest, struct vec_t const *const src) {
	VEC_FATAL_ERR(dest == NULL, "invalid argument.");
	VEC_FATAL_ERR(src == NULL, "invalid argument.");
	VEC_FATAL_ERR(dest->items == NULL, "vec is not initialized");
	VEC_FATAL_ERR(src->items == NULL, "vec is not initialized.");

	VEC_FATAL_ERR(
		dest->size != src->size,
		"destination vec doesnt share the same type with "
		"source vec."
	);

	for (uint i = 0; i < src->length; i++) {
		void *item = vec_get(src, i);
		void *item_copy = malloc(src->size);

		VEC_FATAL_ERR(item_copy == NULL, "failed to malloc.");

		memcpy(item_copy, item, src->size);
		vec_push(dest, item_copy);
	}
}


void vec_copy(struct vec_t *dest, struct vec_t const *const src) {
	VEC_FATAL_ERR(dest == NULL, "invalid argument.");
	VEC_FATAL_ERR(src == NULL, "invalid argument.");
	VEC_FATAL_ERR(dest->items == NULL, "vec is not initialized");
	VEC_FATAL_ERR(src->items == NULL, "vec is not initialized.");

	if (dest->length > 0) {
		vec_clear(dest);
	}

	vec_concat(dest, src);
}


void vec_clear(struct vec_t *const vec) {
	VEC_FATAL_ERR(vec == NULL, "invalid argument.");
	VEC_FATAL_ERR(vec->items == NULL, "vec is not initialized.");

	for (uint i = 0; i < vec->length; i++) {
		free(vec->items[i]);
		vec->items[i] = NULL;
	}

	vec->length = 0;
}


void vec_drop(struct vec_t *const vec) {
	vec_clear(vec);
	free(vec->items);
	vec->items = NULL;
}
