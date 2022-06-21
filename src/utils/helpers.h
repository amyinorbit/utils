/*===--------------------------------------------------------------------------------------------===
 * helpers.h
 *
 * Created by Amy Parent <amy@amyparent.com>
 * Copyright (c) 2022 Amy Parent
 *
 * Licensed under the MIT License
 *===--------------------------------------------------------------------------------------------===
*/
#ifndef _UTILS_HELPERS_
#define _UTILS_HELPERS_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UNUSED(x)   ((void)(x))
#define LIKELY(x)   (x)
#define UNLIKELY(x) (x)
    
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Memory basics

static inline void *
safe_malloc(size_t bytes) {
    void *p = malloc(bytes);
    if(!p) {
        fprintf(stderr, "out of memory\n");
        abort();
    }
    return p;
}

static inline void *
safe_calloc(size_t count, size_t size) {
    void *p = calloc(count, size);
    if(!p) {
        fprintf(stderr, "out of memory\n");
        abort();
    }
    return p;
}

static inline void *
safe_realloc(void *ptr, size_t size) {
    void *p = realloc(ptr, size);
    if(!p) {
        fprintf(stderr, "out of memory\n");
        abort();
    }
    return p;
}

static inline char *
safe_strdup(const char *str) {
    char *copy = strdup(str);
    if(!copy) {
        fprintf(stderr, "out of memory\n");
        abort();
    }
    return copy;
}
    
// Filesystem utilities

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#define UTILS_WINDOWS
#define DIR_SEP '\\'
#else
#define DIR_SEP '/'
#endif

const char *fs_current_dir();
bool fs_file_exists(const char *path);
char *fs_make_path(const char *path, ...);
char *fs_parent(const char *path);

// String handling
#ifdef UTILS_WINDOWS
size_t getline(char **lineptr, size_t *n, FILE *stream);
#endif

void str_trim_space(char *str);
unsigned str_split_inplace(char *str, char delim, char **comps, unsigned max_comp);

#ifdef __cplusplus
}
#endif


#endif /* ifndef _UTILS_HELPERS_ */
