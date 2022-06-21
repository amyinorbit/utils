/*===--------------------------------------------------------------------------------------------===
 * helpers.c
 *
 * Created by Amy Parent <amy@amyparent.com>
 * Copyright (c) 2022 Amy Parent. All rights reserved
 *
 * Licensed under the MIT License
 *===--------------------------------------------------------------------------------------------===
*/
#include <utils/helpers.h>
#include <utils/assert.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>


const char *fs_current_dir() {
    static char path[1024];
    getcwd(path, sizeof(path));
    return path;
}

bool fs_file_exists(const char *path) {
    ASSERT(path != NULL);
    
    return access(path, F_OK) == 0;
}

char *fs_make_path(const char *root, ...) {
    ASSERT(root != NULL);
    
    va_list args, copy;
    va_start(args, root);
    va_copy(copy, args);
    size_t len = strlen(root);
    const char *comp = NULL;
    while((comp = va_arg(args, const char *)) != NULL) {
        len += strlen(comp) + 1;
    }
    va_end(args);

    comp = NULL;
    char *path = safe_calloc(len + 1, 1);
    size_t idx = snprintf(path, 1 + len, "%s%c", root, DIR_SEP);

    while((comp = va_arg(copy, const char *)) != NULL) {
        idx += snprintf(&path[idx], 1 + len - idx, "%s%c", comp, DIR_SEP);
    }
    va_end(copy);
    
    return path;
}

char *fs_parent(const char *path) {
    ASSERT(path != NULL);
    
    const char *last_sep = strrchr(path, DIR_SEP);
    if(!last_sep) return NULL;
    
    size_t len = (last_sep - path);
    char *parent = safe_calloc(len, 1);
    memcpy(parent, path, len);
    parent[len] = '\0';
    return parent;
}

#ifdef UTILS_WINDOWS
/* This code is public domain -- Will Hartung 4/9/09 */

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
#endif

void str_trim_space(char *str) {
    ASSERT(str);
    
    char *start = str;
    while(*start && isspace(*start)) {
        ++start;
    }
    size_t len = strlen(start);
    memmove(str, start, len);
    
    str[len] = '\0';
    while(len && isspace(str[len-1])) {
        str[--len] = '\0';
    }
}


unsigned str_split_inplace(char *str, char delim, char **comps, unsigned max_comps) {
    ASSERT(str);
    ASSERT(comps || max_comps == 0);
    
    unsigned n = 1;
    if(max_comps) comps[0] = str;
    
    while((str = strchr(str, delim)) != NULL && (!max_comps || n < max_comps)) {
        *str = '\0';
        ++str;
        if(max_comps) comps[n++] = str;
    }
    return n;
}
