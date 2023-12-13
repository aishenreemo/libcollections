#ifndef COLLECTIONS_VEC_H
#define COLLECTIONS_VEC_H


#include <stdlib.h>


struct vec_t {
	size_t capacity;
	size_t length;
	size_t size;
	void **items;
};


void vec_init(struct vec_t *const vec, size_t size);

void vec_push(struct vec_t *const vec, void const *const item);
void vec_insert(struct vec_t *const vec, void const *const restrict item, size_t index);

void vec_remove(struct vec_t *const vec, size_t index);

void *vec_get(struct vec_t const *const vec, size_t index);

void vec_concat(struct vec_t *const dest, struct vec_t const *const src);

void vec_copy(struct vec_t *dest, struct vec_t const *const src);

void vec_clear(struct vec_t *const vec);
void vec_drop(struct vec_t *const vec);


#endif // COLLECTIONS_VEC_H
