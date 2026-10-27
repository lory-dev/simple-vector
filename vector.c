#include "vector.h"
#include <string.h>
#include <stdlib.h>

Vector* vec_create(ElemType type) {
    Vector* vec = malloc(sizeof(Vector));
    if (vec == NULL || type < T_SHORT || type > T_CHAR) {
        return NULL;
    }
    vec->data = NULL;
    vec->length = 0;
    vec->capacity = 0;
    vec->type = type;
    return vec;
}

static size_t sizeof_type(ElemType type) {
    switch (type) {
        case T_SHORT:
            return sizeof(short);
        case T_INT:
            return sizeof(int);
        case T_LONG:
            return sizeof(long);
        case T_LONGLONG:
            return sizeof(long long);
        case T_FLOAT:
            return sizeof(float);
        case T_DOUBLE:
            return sizeof(double);
        case T_CHAR:
            return sizeof(char);
        default:
            return 0;
    }
}

static int grow_vector(Vector* vec) {
    size_t new_capacity = (vec->capacity > 0) ? (2 * vec->capacity) : 1;
    void* tmp = realloc(vec->data, new_capacity * sizeof_type(vec->type));
    if (tmp == NULL) {
        return 1;
    }
    vec->data = tmp;
    vec->capacity = new_capacity;
    return 0;
}

int vec_push_back(Vector* vec, const void* data) {
    if (vec == NULL || data == NULL) {
        return 1;
    }
    if (vec->length == vec->capacity) {
        if (grow_vector(vec) != 0) {
            return 1;
        }
    }
    char* bytes = (char *)vec->data;
    char* slot = bytes + vec->length * sizeof_type(vec->type);
    memcpy(slot, data, sizeof_type(vec->type));
    vec->length += 1;
    return 0;
}

int vec_pop_back(Vector* vec) {
    if (vec == NULL) {
        return 1;
    }
    if (vec->length == 0) {
        return 1;
    }
    // todo: add quarter scale back check
    vec->length -= 1;
    return 0;
}

size_t vec_size(Vector *vec) {
    if (vec == NULL) {
        return 0;
    }
    return vec->length;
}

int vec_insert(Vector *vec, size_t pos, void *data) {
    if (vec == NULL || data == NULL || pos > vec->length) {
        return 1;
    }
    if (vec->length == vec->capacity) {
        if (grow_vector(vec) != 0) {
            return 1;
        }
    }
    char* bytes = (char *)vec->data;
    char* dst_slot = bytes + (pos + 1) * sizeof_type(vec->type);
    char* src_slot = bytes + pos * sizeof_type(vec->type);
    size_t size = (vec->length - pos) * sizeof_type(vec->type);
    memmove(dst_slot, src_slot, size);
    memcpy(src_slot, data, sizeof_type(vec->type));
    vec->length += 1;
    return 0;
}

int vec_erase(Vector* vec, size_t pos) {
    if (vec == NULL || pos >= vec->length) {
        return 1;
    }
    // todo: add quarter scale back check
    char* bytes = (char *)vec->data;
    char* dst_slot = bytes + pos * sizeof_type(vec->type);
    char* src_slot = bytes + (pos + 1) * sizeof_type(vec->type);
    size_t size = (vec->length - pos - 1) * sizeof_type(vec->type);
    memmove(dst_slot, src_slot, size);
    vec->length -= 1;
    return 0;
}

void* vec_at(Vector* vec, size_t pos) {
    if (vec == NULL || pos >= vec->length) {
        return NULL;
    }
    char* bytes = (char *)vec->data;
    char* data_at = bytes + pos * sizeof_type(vec->type);
    return data_at;
}

void vec_clear(Vector* vec) {
    if (vec == NULL) {
        return;
    }
    vec->length = 0;
    vec->capacity = 0;
    free(vec->data);
    vec->data = NULL;
}

bool vec_empty(Vector* vec) {
    if (vec == NULL) {
        return false;
    }
    return vec->length == 0;
}

void vec_destroy(Vector* vec) {
    if (vec == NULL) {
        return;
    }
    free(vec->data);
    free(vec);
}
