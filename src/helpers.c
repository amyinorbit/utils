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
