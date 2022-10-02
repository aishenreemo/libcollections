// https://jera.com/techinfo/jtns/jtn002
// funi unit test framework i modified

#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <libcollections/vector.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum __test_result_t__ {
	TEST_RESULT_SUCCESS,
	TEST_RESULT_FAILURE,
};

struct __test_t__ {
	char *name;
	char *message;
	enum __test_result_t__ result;
};

#define UT_INIT() vector_init(&__test_vec__, NULL)
#define UT_SUCCESS "\033[1;32mSUCCESS\033[0m"
#define UT_FAILURE "\033[1;31mFAILURE\033[0m"

#define UT_TEST() struct __test_t__ *__t__ = malloc(sizeof(struct __test_t__))
#define UT_NAME(NAME) do { \
		uint name_len = strlen(NAME); \
		__t__->name = calloc(sizeof(char), name_len + 1); \
		strcpy(__t__->name, NAME);\
	} while(0)

#define UT_ASSERT(msg, bool_test) do { \
		if (bool_test) break; \
		uint message_len = strlen(msg); \
		__t__->result = TEST_RESULT_FAILURE; \
		__t__->message = calloc(sizeof(char), message_len + 1); \
		strcpy(__t__->message, msg); \
		vector_push(&__test_vec__, __t__, NULL); \
		return; \
	} while (0)

#define UT_SUCCEED() do { \
		__t__->result = TEST_RESULT_SUCCESS; \
		__t__->message = calloc(sizeof(char), 1); \
		__t__->message[0] = '\0';\
		vector_push(&__test_vec__, __t__, NULL); \
		return; \
	} while (0)


#define UT_INFO() do { \
		uint __failure_count__ = 0; \
		uint __vec_len__ = __test_vec__.length; \
		printf("---\n");\
		for (uint __i__ = 0; __i__ < __vec_len__; __i__++) { \
			struct __test_t__ *__t__ = vector_get(&__test_vec__, __i__, NULL); \
			bool __failed__ = __t__->result == TEST_RESULT_FAILURE;\
			printf("%s: ", __t__->name);\
			printf("%s ", __failed__ ? UT_FAILURE : UT_SUCCESS); \
			if (__failed__) printf("(%s)", __t__->message); \
			__failure_count__ += __failed__ ? 1 : 0; \
			printf("\n"); \
		} \
		printf( \
			"---\n%d failures + %d success = %d total\n\n", \
			__failure_count__, \
			__vec_len__ - __failure_count__, \
			__vec_len__ \
		);\
	} while(0)

#define UT_END() vector_drop(&__test_vec__)

vector_t __test_vec__;

#endif // __UNIT_TEST_H__
