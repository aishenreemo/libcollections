// Copyright (c) 2022 Aishen
//
// MIT LICENSE
// https://github.com/aishenreemo/libcollections/blob/master/license.md

#ifndef __COLLECTIONS_VECTOR_H__
#define __COLLECTIONS_VECTOR_H__

struct __vector_t__;
enum   __vector_result_t__;

// public aliases
typedef struct __vector_t__        vector_t;
typedef enum   __vector_result_t__ vector_result_t;

void vector_init(
	vector_t        *,
	vector_result_t *
);
void vector_get(
	vector_t        *,
	unsigned int     ,
	void            *,
	vector_result_t *
);

void vector_push(
	vector_t        *,
	void            *,
	vector_result_t *
);

void vector_remove(
	vector_t        *,
	int              ,
	vector_result_t *
);

void vector_drop(
	vector_t        *,
	vector_result_t *
);

void vector_print_error(vector_result_t);

#endif // __COLLECTIONS_VECTOR_H__
