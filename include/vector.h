// Copyright (c) 2022 Aishen
//
// MIT LICENSE
// https://github.com/aishenreemo/libcollections/blob/master/license.md

#ifndef __COLLECTIONS_VECTOR_H__
#define __COLLECTIONS_VECTOR_H__

#include <stdlib.h>

// public structs/enum
struct __vector_t__ {
	void **items;
	unsigned int length;
	unsigned int capacity;
};

enum __vector_result_t__ {
	VECTOR_RESULT_SUCCESS,
	VECTOR_RESULT_UNDEFINED,
	VECTOR_RESULT_INIT_CALLOC_FAILURE,
	VECTOR_RESULT_GET_INDEX_OVERLAP,
	VECTOR_RESULT_PUSH_REALLOC_FAILURE,
	VECTOR_RESULT_PUSH_ITEM_INVALID,
	VECTOR_RESULT_REMOVE_INDEX_OVERLAP,
	VECTOR_RESULT_REMOVE_REALLOC_FAILURE,
	VECTOR_RESULT_CONCAT_MALLOC_FAILURE,
};

// public aliases
typedef struct __vector_t__        vector_t;
typedef enum   __vector_result_t__ vector_result_t;

// public functions declarations

void vector_init(vector_t *, vector_result_t *);
void *vector_get(vector_t *, unsigned int, vector_result_t *);
void vector_push(vector_t *, void *, vector_result_t *);
void vector_concat(vector_t *, vector_t *, size_t, vector_result_t *);
void vector_copy(vector_t *, vector_t *, size_t, vector_result_t *);

void vector_remove(vector_t *, unsigned int, vector_result_t *);
void vector_clear(vector_t *, vector_result_t *);

void vector_drop(vector_t *);

void vector_print_error(vector_result_t);

#endif // __COLLECTIONS_VECTOR_H__
