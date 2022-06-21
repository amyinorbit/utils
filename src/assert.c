/*===--------------------------------------------------------------------------------------------===
 * assert.c
 *
 * Created by Amy Parent <amy@amyparent.com>
 * Copyright (c) 2022 Amy Parent. All rights reserved
 *
 * Licensed under the MIT License
 *===--------------------------------------------------------------------------------------------===
*/
#include <utils/assert.h>
#include <utils/helpers.h>
#include <stdlib.h>
#include <stdio.h>

void assert_impl(bool val, const char *file, unsigned line, const char *expr) {
    if(LIKELY(val)) return;
    fprintf(stderr, "%s:%u: assertion `%s' failed\n", file, line, expr);
    abort();
}

