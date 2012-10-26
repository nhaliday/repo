#include "queue.h"

Queue *Queue_create(size_t element_size, int max_size) {
    Queue *queue = malloc(sizeof(Queue));
    queue->max_size = max_size;
    queue->mod = max_size + 1;
    queue->contents = calloc(queue->mod, sizeof(void *));
    queue->begin = 0;
    queue->end = 0;
    queue->element_size = element_size;

    return queue;
}

void Queue_clear(Queue *queue) {
    int i = 0;
    if (queue->element_size > 0) {
        for (i = queue->begin; i != queue->end; i = (i + 1) % queue->mod) {
            if (queue->contents[i] != NULL) {
                free(queue->contents[i]);
            }
        }
    }
}

void Queue_destroy(Queue *queue) {
    if (queue) {
        if (queue->contents) free(queue->contents);
        free(queue);
    }
}

void Queue_clear_destroy(Queue *queue) {
    Queue_clear(queue);
    Queue_destroy(queue);
}

int Queue_push(Queue *queue, void *el) {
    if (Queue_count(queue) >= queue->max_size) {
        return -1;
    }
    queue->contents[queue->end] = el;
    queue->end = (queue->end + 1) % queue->mod;
    return 0;
}

void *Queue_pop(Queue *queue) {
    if (Queue_count(queue) < 1) {
        return NULL;
    }
    void *rv = queue->contents[queue->begin];
    queue->begin = (queue->begin + 1) % queue->mod;
    return rv;
}
