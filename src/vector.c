// Copyright (c) 2022 Aishen
//
// MIT LICENSE
// https://github.com/aishenreemo/libcollections/blob/master/license.md

// idk how to name things forgive me xd

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "vector.h"

#define VECTOR_DEBUG_WARN "\033[1;33mwarn\033[0m"
#define VECTOR_DEBUG_WARN_FN(TEXT) VECTOR_DEBUG_WARN "(" TEXT ")"

// private struct/enum declarations

// private function declarations

// public function implementations
void vector_init(vector_t *vec, vector_result_t *err) {
	if (vec == NULL) {
		if (err != NULL) *err = VECTOR_RESULT_UNDEFINED;
		return;
	}

	vec->length = 0;
	vec->capacity = 6;
	vec->items = calloc(sizeof(void *), vec->capacity);

	if (err != NULL) *err = (vec->items == NULL)
		? VECTOR_RESULT_INIT_CALLOC_FAILURE
		: VECTOR_RESULT_SUCCESS;
}

void *vector_get(vector_t *vec, uint index, vector_result_t *err) {
	if (vec == NULL) {
		if (err != NULL) *err = VECTOR_RESULT_UNDEFINED;
		return NULL;
	} else if (index < 0 || index >= vec->length) {
		if (err != NULL) *err = VECTOR_RESULT_GET_INDEX_OVERLAP;
		return NULL;
	} else {
		if (err != NULL) *err = VECTOR_RESULT_SUCCESS;
		return vec->items[index];
	}
}

void vector_push(vector_t *vec, void *item, vector_result_t *err) {
	if (vec == NULL) {
		if (err != NULL) *err = VECTOR_RESULT_UNDEFINED;
		return;
	} else if (item == NULL) {
		if (err != NULL) *err = VECTOR_RESULT_PUSH_ITEM_INVALID;
		return;
	}

	if (vec->capacity <= vec->length + 1) {
		vec->capacity *= 2;
		vec->items = realloc(vec->items, sizeof(void *) * vec->capacity);

		if (vec->items == NULL) {
			if (err != NULL) *err = VECTOR_RESULT_PUSH_REALLOC_FAILURE;
			return;
		}
	}

	vec->items[vec->length] = item;
	vec->length += 1;

	if (err != NULL) *err = VECTOR_RESULT_SUCCESS;
}

void vector_concat(vector_t *dest, vector_t *source, size_t size, vector_result_t *err) {
	if (dest == NULL || source == NULL) {
		if (err != NULL) *err = VECTOR_RESULT_UNDEFINED;
		return;
	}

	for (uint i = 0; i < source->length; i++) {
		void *item = vector_get(source, i, err);
		if (err != NULL && *err != VECTOR_RESULT_SUCCESS) return;

		void *item_copy = malloc(size);
		if (item_copy == NULL) {
			if (err != NULL) *err = VECTOR_RESULT_CONCAT_MALLOC_FAILURE;
			return;
		}

		memcpy(item_copy, item, size);

		vector_push(dest, item_copy, err);
		if (err != NULL && *err != VECTOR_RESULT_SUCCESS) return;
	}

	if (err != NULL) *err = VECTOR_RESULT_SUCCESS;
}

void vector_copy(vector_t *dest, vector_t *source, size_t size, vector_result_t *err) {
	vector_clear(dest, err);
	if (err != NULL && *err != VECTOR_RESULT_SUCCESS) return;
	vector_concat(dest, source, size, err);
	if (err != NULL && *err != VECTOR_RESULT_SUCCESS) return;
	if (err != NULL) *err = VECTOR_RESULT_SUCCESS;
}

void vector_remove(vector_t *vec, uint index, vector_result_t *err) {
	if (vec == NULL) {
		if (err != NULL) *err = VECTOR_RESULT_UNDEFINED;
		return;
	} else if (index < 0 || index >= vec->length) {
		if (err != NULL) *err = VECTOR_RESULT_REMOVE_INDEX_OVERLAP;
		return;
	}

	if ((vec->capacity / 2) > vec->length + 1) {
		vec->capacity /= 2;
		vec->items = realloc(vec->items, sizeof(void *) * vec->capacity);
		if (vec->items == NULL) {
			if (err != NULL) *err = VECTOR_RESULT_REMOVE_REALLOC_FAILURE;
			return;
		}
	}

	free(vec->items[index]);
	for (uint i = index; (i + 1) < vec->length; i++) {
		vec->items[i] = vec->items[i + 1];
	}

	vec->length -= 1;

	if (err != NULL) *err = VECTOR_RESULT_SUCCESS;
}

void vector_clear(vector_t *vec, vector_result_t *err) {
	for (int i = (int) vec->length - 1; i + 1 > 0; i--) {
		vector_remove(vec, (uint) i, err);
		if (err != NULL && *err != VECTOR_RESULT_SUCCESS) return;
	}

	if (err != NULL) *err = VECTOR_RESULT_SUCCESS;
}

void vector_drop(vector_t *vec) {
	if (vec == NULL) return;

	vec->length = 0;
	for (uint i = 0; i < vec->length; i++) {
		free(vec->items[i]);
		vec->items[i] = NULL;
	}

	free(vec->items);
	vec->items = NULL;
}

void vector_print_error(vector_result_t result) {
	switch (result) {

	case VECTOR_RESULT_SUCCESS:
		break;
	case VECTOR_RESULT_UNDEFINED:
		printf(VECTOR_DEBUG_WARN ": ");
		printf("passing an invalid NULL value on a function.\n");
		break;
	case VECTOR_RESULT_INIT_CALLOC_FAILURE:
		printf(VECTOR_DEBUG_WARN_FN("vector_init") ": ");
		printf("failed to alloc memory.\n");
		break;
	case VECTOR_RESULT_PUSH_REALLOC_FAILURE:
		printf(VECTOR_DEBUG_WARN_FN("vector_push") ": ");
		printf("failed to realloc memory.\n");
		break;
	case VECTOR_RESULT_REMOVE_REALLOC_FAILURE:
		printf(VECTOR_DEBUG_WARN_FN("vector_remove") ": ");
		printf("failed to realloc memory.\n");
		break;
	case VECTOR_RESULT_CONCAT_MALLOC_FAILURE:
		printf(VECTOR_DEBUG_WARN_FN("vector_concat") ": ");
		printf("failed to alloc memory.\n");
		break;
	case VECTOR_RESULT_GET_INDEX_OVERLAP:
		printf(VECTOR_DEBUG_WARN_FN("vector_get") ": ");
		printf("out of index.\n");
		break;
	case VECTOR_RESULT_REMOVE_INDEX_OVERLAP:
		printf(VECTOR_DEBUG_WARN_FN("vector_remove") ": ");
		printf("out of index.\n");
		break;
	case VECTOR_RESULT_PUSH_ITEM_INVALID:
		printf(VECTOR_DEBUG_WARN_FN("vector_push") ": ");
		printf("passing an invalid NULL value.\n");
		break;
	}
}
