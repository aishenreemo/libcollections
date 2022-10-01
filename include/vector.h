// Copyright (c) 2022 Aishen
//
// MIT LICENSE
// https://github.com/aishenreemo/libcollections/blob/master/license.md

#ifndef __COLLECTIONS_VECTOR_H__
#define __COLLECTIONS_VECTOR_H__

// public structs/enum declarations

// vector_t
//
// struct for creating vectors. vectors are used to store elements with a same type.
// in this implementation, this struct uses a list of (void) pointers that can point to anything.
struct __vector_t__;

// vector_result_t
//
// types of error returned when interacting with vectors,
// explain the error using vector_print_error() function
enum   __vector_result_t__;

// public aliases
typedef struct __vector_t__        vector_t;
typedef enum   __vector_result_t__ vector_result_t;

// public functions

// vector_init
//
// a function that initializes a vector,
// returns an error if it failed allocating some space
//
// example
//
// ```c
// vector_t vec;
// vector_result_t vec_err;
// vector_init(&vec, &vec_err);
//
// // if failed
// if (vec_err != VECTOR_SUCCESS) {
//	eprintf("An occured while initializing vector: %s\n", vector_print_error(vec_err));
//	exit(EXIT_FAILURE);
// }
// ```
void vector_init(
	vector_t        *,
	vector_result_t *
);

// vector_get
//
// a function that gets an item from a vector.
// returns an error if specified index overlaps.
//
// example
//
// ```c
// for (uint i = 0; i < vector_len(&vec); i++) {
//	void *item;
//
//	// change NULL to a vector_result_t
//	// pointer if you want to catch errors
//	vector_get_f(&vec, i, item, NULL);
//
//
//	// do stuff with item
//	// ...
// }
// ```
void vector_get(
	vector_t        *,
	unsigned int     ,
	void            *,
	vector_result_t *
);

// vector_push
//
// a function that pushes an item to a vector,
// returns an error if specified item is NULL
// or failed to resize vector capacity.
//
// example
// ```c
// typedef struct {
//	char name[16];
//	unsiged int age;
// } person_t
//
// // ...
// person_t *p = malloc(sizeof(person_t));
// p->name = "aishen";
// p->age = 17;
//
// // change NULL to a vector_result_t
// // pointer if you want to catch errors
// vector_push(&vec, p, NULL);
// ```
void vector_push(
	vector_t        *,
	void            *,
	vector_result_t *
);

// vector_remove
//
// a function that removes an item from a vector,
// returns an error if specified index overlaps
// or failed to resize vector capacity.
//
// example
// ```c
// vector_result_t vec_err;
// // removes the first item
// vector_remove(&vec, 0, &vec_err);
//
// if (vec_err != VECTOR_SUCCESS) {
//	eprintf("An occured while removing an item from a vector: %s\n", vector_print_error(vec_err));
//	exit(EXIT_FAILURE);
// }
// ```
void vector_remove(
	vector_t        *,
	int              ,
	vector_result_t *
);

// vector_remove
//
// a function that frees a vector assuming you wont use it anymore
//
// example
// ```c
// vector_drop(&vec)
// ```
void vector_drop(
	vector_t        *,
	vector_result_t *
);

// vector_remove
//
// a function for debbuging errors
void vector_print_error(vector_result_t);

#endif // __COLLECTIONS_VECTOR_H__
