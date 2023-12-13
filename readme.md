## libcollections
libcollections is a free C library offering implementations of commonly used data structures in programming. You are welcome to use it into your own C projects, but I recommend considering implementing these data structures independently. The library does not involve complex concepts, making it comparable to other existing implementations. Feel free to use my code as a helpful reference for your implementations.

## install
- on UNIX systems, check the [makefile](./makefile) and run this script.
```sh
git clone https://github.com/aishenreemo/libcollections
cd libcollections
make
make install
```

## usage
Simply include the flag `-lcollections` when compiling to use this library.

### documentation

#### vector
A dynamically resizable array type, `struct vec_t`, found on [`<libcollections/vec.h>`](./include/vec.h).

- [Source Code](./src/vec.c)
- [Wikipedia](https://en.wikipedia.org/wiki/Vector#Computer_science).

##### example
```c
#include <libcollections/vector.h>

// ...

// initializes the vector
struct vec_t my_vec;
vec_init(&my_vec, sizeof(int)); // as an array of int(s)

// adding items
vec_push(&my_vec, &(int) {1}); // anonymous pointer to integer
vec_push(&my_vec, &(int) {2});
vec_push(&my_vec, &(int) {3});

// note: vec_push creates a copy on the heap
// of the item you passed on which is freed
// when you use `vec_drop()`

// iterating the array
for (int i = 0; i < my_vec.length; i++) {
    // getting item from array
    int const *number = vec_get(&my_vec, i);

    printf("%d ", *number);
    // or a one-liner `*vec_get(&my_vec, i)`
    // whatever fits you
}

// deallocating the array
vec_drop(&my_vec);
```

##### mutating values
```c
// vec_get returns `void const *` so consider
// typecasting it into `(T *)` if you want to mutate
// an specific value, heres an example of mutating the
// first value.
int *number_mut = (int *) vec_get(&my_vec, 0);
*number_mut = 5;
```
