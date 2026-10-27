# Simple Vector
Simple Vector is a C library that implements vectors (dynamically sized arrays).
This library was made as a learning project to practice dynamically allocated memory (on the heap) and should probably not be used in production software.
It is not type agnostic, and supports short, int, long, long long, float, double and char; it does not yet support strings.

## Usage
Creating a vector:
```c
Vector* vec = vec_create(T_SHORT);
```

Each vector has a type, chosen when it's created. The values you pass in must have that same type:

```c
Vector* ints = vec_create(T_INT);

int n = 42;
vec_push_back(ints, &n);
```

Supported types are `T_SHORT`, `T_INT`, `T_LONG`, `T_LONGLONG`, `T_FLOAT`, `T_DOUBLE`, and `T_CHAR`.

Adding and reading values:

```c
Vector* vec = vec_create(T_DOUBLE);

double a = 1.5, b = 2.5;
vec_push_back(vec, &a);
vec_push_back(vec, &b);

double* first = vec_at(vec, 0);
printf("%f\n", *first);   /* 1.500000 */
```

`vec_at` returns `NULL` if the index is out of range, so check the result before you read through it:

```c
double* item = vec_at(vec, 10);
if (item == NULL) {
    printf("no element at index 10\n");
}
```

Inserting and removing:

```c
double c = 0.5;
vec_insert(vec, 0, &c);   /* puts 0.5 at the front */
vec_erase(vec, 1);        /* removes the element at index 1 */
```

Checking the size and state:

```c
size_t count = vec_size(vec);
if (vec_empty(vec)) {
    printf("the vector is empty\n");
}
```

Clearing and freeing:

```c
vec_clear(vec);     /* removes all elements, keeps the vector usable */
vec_destroy(vec);   /* frees the vector */
```

## Return values

Functions that can fail return `0` on success and `1` on failure:

- `vec_push_back`, `vec_insert`, `vec_erase`, and `vec_pop_back`
- `vec_create` returns `NULL` on failure, including for an unknown type.
- `vec_at` returns `NULL` if the index is out of range.

## Memory

Every vector from `vec_create` must be passed to `vec_destroy` exactly once.

A pointer from `vec_at` is only valid until the next `vec_push_back`, `vec_insert`, or `vec_erase`. Those calls can move the buffer, so read the value again after changing the vector.
