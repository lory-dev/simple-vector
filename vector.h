#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef enum element_type {
    T_SHORT, T_INT, T_LONG, T_LONGLONG, T_FLOAT, T_DOUBLE, T_CHAR
} ElemType;

typedef struct {
    void* data;
    size_t length; // slots being used
    size_t capacity; // total slots allocated
    ElemType type;
} Vector;

/*
 * Create a Vector with the specified element type.
 * Returns NULL on failure.
 */
Vector* vec_create(ElemType type);

/*
 * Adds an element to the end of the vector. `data` must match the Vector's type.
 * Returns 0 when successful.
 */
int vec_push_back(Vector* vec, const void* data);

/*
 * Removes the last element in the vector. If the vector is empty, this fails.
 * Returns 0 when successful.
 */
int vec_pop_back(Vector* vec);

/*
 * Gets the amount of elements in the vector.
 */
size_t vec_size(Vector* vec);

/*
 * Inserts an element in the vector at the specified position. `pos` must not be larger than the vector's length.
 * Returns 0 when successful.
 */
int vec_insert(Vector* vec, size_t pos, void* data);

/*
 * Removes an element in the vector from the specified position. `pos` must be less than the vector's length.
 * Returns 0 when successful.
 */
int vec_erase(Vector* vec, size_t pos);

/*
 * Returns a pointer to a value at the specified position.
 */
void* vec_at(Vector* vec, size_t pos);

/*
 * Removes all of the elements in the vector.
 */
void vec_clear(Vector* vec);

/*
 * Returns whether the vector is empty.
 */
bool vec_empty(Vector* vec);

/*
 * Frees the vector.
 */
void vec_destroy(Vector* vec);

#endif
