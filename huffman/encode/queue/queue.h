#ifndef _Queue_h
#define _Queue_h

#include <stdlib.h>

typedef struct Queue {
    int begin, end;
    int max_size;
    int mod;
    size_t element_size;
    void **contents;
} Queue;

Queue *Queue_create(size_t element_size, int max_size);

void Queue_destroy(Queue *queue);

void Queue_clear(Queue *queue);

void Queue_clear_destroy(Queue *queue);

int Queue_push(Queue *queue, void *elem);

void *Queue_pop(Queue *queue);

#define Queue_first(A) ((A)->contents[(A)->begin])
#define Queue_last(A) ((A)->contents[(A)->end - 1])

static inline int Queue_count(Queue *queue) {
    int rv = queue->end - queue->begin;
    return (rv > 0) ? rv : (rv + queue->mod);
}

static inline void *Queue_get(Queue *queue, int i) {
   if (i >= Queue_count(queue)) {
        return NULL;
   }
   return queue->contents[queue->begin + i];
}

#endif
