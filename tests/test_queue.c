#include <queue/queue.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <cmocka.h>

queue_t queue;
char *buf = NULL;

int init(void **state) {
    *state = &queue;
    buf = malloc(5*sizeof(char));
    assert_non_null(buf);
    memset(buf, 0, 5);
    queue_init(&queue, buf, 5);
    return 0;
}

int finish(void **state) {
    free(buf);
    return 0;
}

void test_queue_max(void **state) {
    queue_t *uut = (queue_t *)*state;
    queue_pop(uut);
    assert_false(uut->op_ok);
    uut->op_ok = true;
    queue_peek(uut);
    assert_false(uut->op_ok);
    queue_push(uut, 1);
    assert_int_equal(queue_pop(uut), 1);
    queue_push(uut, 2);
    queue_push(uut, 3);
    queue_push(uut, 4);
    queue_push(uut, 5);
    assert_int_equal(queue_pop(uut), 2);
    assert_int_equal(queue_pop(uut), 3);
    queue_push(uut, 6);
    assert_int_equal(queue_peek(uut), 4);
    assert_int_equal(queue_pop(uut), 4);
    assert_int_equal(queue_pop(uut), 5);
    queue_push(uut, 7);
    queue_push(uut, 8);
    queue_push(uut, 9);
    queue_push(uut, 10);
    queue_push(uut, 11);
    queue_push(uut, 12);
    assert_int_equal(uut->size, uut->cap);
    assert_int_equal(queue_pop(uut), 6);
}

void test_queue_roll(void **state) {
    queue_t *uut = (queue_t *)*state;
    queue_push(uut, 1);
    queue_push(uut, 2);
    queue_pop(uut);
    queue_push(uut, 3);
    queue_push(uut, 4);
    queue_push(uut, 5);
    queue_push(uut, 6);
    assert_int_equal(uut->size, uut->cap);
}

int main(int argc, char **argv) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_queue_max, init, finish),
        cmocka_unit_test_setup_teardown(test_queue_roll, init, finish)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
