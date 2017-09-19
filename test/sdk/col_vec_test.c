#include <stdlib.h>
#include <stdio.h>

#include <dslink/col/vector.h>
#include "cmocka_init.h"

static
void col_vec_init_test(void **state) {
    (void) state;

    Vector vec;
    vector_init(&vec, 10, sizeof(int));
    assert_int_equal(vec.capacity, 10);
    assert_int_equal(vec.size, 0);

    vector_free(&vec);
}

static
void col_vec_append_test(void **state) {
    (void) state;

    Vector vec;
    vector_init(&vec, 10, sizeof(int));

    int n = 4711;
    long index = vector_append(&vec, &n);
    assert_int_equal(index, 0);
    assert_int_equal(*(int*)vector_get(&vec, index), 4711);

    n = 815;
    index = vector_append(&vec, &n);
    assert_int_equal(index, 1);
    assert_int_equal(*(int*)vector_get(&vec, index), 815);

    vector_free(&vec);
}

static
void col_vec_resize_test(void **state) {
    (void) state;

    Vector vec;
    vector_init(&vec, 2, sizeof(int));

    int n = 4711;
    vector_append(&vec, &n);
    n = 815;
    vector_append(&vec, &n);

    assert_int_equal(vec.capacity, 2);
    assert_int_equal(vec.size, 2);

    n = 42;
    long index = vector_append(&vec, &n);
    assert_int_equal(index, 2);
    assert_int_equal(*(int*)vector_get(&vec, index), 42);
    assert_int_equal(vec.capacity, 4);
    assert_int_equal(vec.size, 3);

    vector_free(&vec);
}

static
void col_vec_set_get_test(void **state) {
    (void) state;

    Vector vec;
    vector_init(&vec, 10, sizeof(int));

    int n = 4711;
    vector_append(&vec, &n);
    n = 815;
    vector_append(&vec, &n);

    assert_int_equal(*(int*)vector_get(&vec, 0), 4711);
    assert_int_equal(*(int*)vector_get(&vec, 1), 815);

    n = 42;
    vector_set(&vec, 0, &n);
    assert_int_equal(*(int*)vector_get(&vec, 0), 42);
    n = 66;
    vector_set(&vec, 1, &n);
    assert_int_equal(*(int*)vector_get(&vec, 1), 66);

    assert_null(vector_get(&vec, 2));

    vector_free(&vec);
}

static
void col_vec_remove_test(void **state) {
    (void) state;

    Vector vec;
    vector_init(&vec, 10, sizeof(int));

    int n = 4711;
    vector_append(&vec, &n);
    n = 815;
    vector_append(&vec, &n);
    n = 42;
    vector_append(&vec, &n);
    n = 66;
    vector_append(&vec, &n);
    assert_int_equal(vec.capacity, 10);
    assert_int_equal(vec.size, 4);

    assert_int_equal(*(int*)vector_get(&vec, 0), 4711);
    assert_int_equal(*(int*)vector_get(&vec, 1), 815);
    assert_int_equal(*(int*)vector_get(&vec, 2), 42);
    assert_int_equal(*(int*)vector_get(&vec, 3), 66);

    vector_remove(&vec, 1);
    assert_int_equal(vec.capacity, 10);
    assert_int_equal(vec.size, 3);

    assert_int_equal(*(int*)vector_get(&vec, 0), 4711);
    assert_int_equal(*(int*)vector_get(&vec, 1), 42);
    assert_int_equal(*(int*)vector_get(&vec, 2), 66);

    vector_free(&vec);
}

static
void col_vec_iterate_test(void **state) {
    (void) state;

    Vector vec;
    vector_init(&vec, 10, sizeof(int));

    int n = 4711;
    vector_append(&vec, &n);
    n = 815;
    vector_append(&vec, &n);
    n = 42;
    vector_append(&vec, &n);
    n = 66;
    vector_append(&vec, &n);

    uint32_t count = 0;
    dslink_vector_foreach(&vec) {
        switch (count) {
            case 0:
                assert_int_equal(*(int*)data, 4711);
                break;
            case 1:
                assert_int_equal(*(int*)data, 815);
                break;
            case 2:
                assert_int_equal(*(int*)data, 42);
                break;
            case 3:
                assert_int_equal(*(int*)data, 66);
                break;
            default:
                assert_non_null(NULL);
                break;
        }
        ++count;
    }
    dslink_vector_foreach_end();

    vector_free(&vec);
}

int cmp_int(const void* lhs, const void* rhs)
{
    if(*(int*)lhs == *(int*)rhs) {
        return 0;
    }
    return -1;
}

static
void col_vec_find_test(void **state) {
    (void) state;

    Vector vec;
    vector_init(&vec, 10, sizeof(int));

    int n = 4711;
    vector_append(&vec, &n);
    n = 815;
    vector_append(&vec, &n);
    n = 42;
    vector_append(&vec, &n);
    n = 66;
    vector_append(&vec, &n);

    n = 42;
    int idx = vector_find(&vec, &n, cmp_int);
    assert_int_equal(idx, 2);
    assert_int_equal(*(int*)vector_get(&vec, idx), 42);

    n = 88;
    idx = vector_find(&vec, &n, cmp_int);
    assert_int_equal(idx, -1);

    idx = vector_find(NULL, &n, cmp_int);
    assert_int_equal(idx, -1);

    vector_free(&vec);
}

static
void col_vec_count_test(void **state) {
    (void) state;

    assert_int_equal(vector_count(NULL), 0);

    Vector vec;
    vector_init(&vec, 10, sizeof(int));

    assert_int_equal(vector_count(&vec), 0);

    int n = 4711;
    vector_append(&vec, &n);
    n = 815;
    vector_append(&vec, &n);
    n = 42;
    vector_append(&vec, &n);
    n = 66;
    vector_append(&vec, &n);

    assert_int_equal(vector_count(&vec), 4);

    vector_free(&vec);
}

static
void col_vec_add_test(void **state) {
    (void) state;

    Vector vec;
    vector_init(&vec, 10, sizeof(int));

    int n = 1;
    for(; n < 1024; ++n) {
        vector_append(&vec, &n);
    }

    vector_free(&vec);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(col_vec_init_test),
        cmocka_unit_test(col_vec_append_test),
        cmocka_unit_test(col_vec_resize_test),
        cmocka_unit_test(col_vec_set_get_test),
        cmocka_unit_test(col_vec_remove_test),
        cmocka_unit_test(col_vec_iterate_test),
        cmocka_unit_test(col_vec_find_test),
        cmocka_unit_test(col_vec_count_test),
        cmocka_unit_test(col_vec_add_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
