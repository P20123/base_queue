#include <queue/queue.h>
queue_t *queue_init(queue_t *self, char *buf, size_t size) {
    self->buffer = buf;
    self->cap = size;
    self->size = 0;
    self->rd = self->buffer;
    self->wr = self->buffer;
    self->op_ok = true;
    return self;
}


char queue_pop(queue_t *self) {
    char val = 0;
    if(self->size > 0){
        self->op_ok = true;
        self->size--;
        val = *self->rd;
        if(self->rd - self->buffer == self->cap - 1) {
            self->rd = self->buffer;
        }
        else {
            self->rd++;
        }
    }
    else {
        self->op_ok = false;
    }
    return val;
}


void queue_push(queue_t *self, char val) {
    if(self->size < self->cap) {
        *self->wr = val;
        self->size++;
        if(self->wr == self->buffer + self->cap - 1) {
            self->wr = self->buffer;
        }
        else {
            self->wr++;
        }
        self->op_ok = true;
    }
    else {
        self->op_ok = false;
    }
}

char queue_peek(queue_t *self) {
    char val = 0;
    if(self->size > 0) {
        self->op_ok = true;
        val = *self->rd;
    }
    else {
        self->op_ok = false;
    }
    return val;
}
