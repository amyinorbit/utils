/*===--------------------------------------------------------------------------------------------===
 * assert.h
 *
 * Created by Amy Parent <amy@amyparent.com>
 * Copyright (c) 2022 Amy Parent
 *
 * Licensed under the MIT License
 *===--------------------------------------------------------------------------------------------===
*/
#ifndef _UTILS_ASSERT_H_
#define _UTILS_ASSERT_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIKELY(x)   (x)
#define UNLIKELY(x) (x)
#define ASSERT(x)   (assert_impl((x), __FILE__, __LINE__, #x))

void assert_impl(bool val, const char *file, unsigned line, const char *expr);


#ifdef __cplusplus
}
#endif

#endif /* ifndef _UTILS_ASSERT_H_ */
