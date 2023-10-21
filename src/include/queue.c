#include "../lib/queue.h"

struct queue {
    Element items[QUEUE_MAX_SIZE];
    int last, first, size;
};


void queue_init(Queue* queue)
{
    Queue q;
    q = malloc(sizeof(struct queue));
    q->last = -1;
    q->first = -1;
    q->size = 0;
    *queue = q;
}

bool queue_is_full(Queue queue)
{
    return queue->size == QUEUE_MAX_SIZE;
}

bool queue_is_empty(Queue queue)
{
    return queue->size == 0;
}

bool queue_enqueue(Queue queue, Element new_element)
{
    bool answer = false;
    if (!queue_is_full(queue)) {
        if (queue->last == QUEUE_MAX_SIZE - 1) {
            queue->last = 0;
        } else {
            queue->last += 1;
        }
        queue->items[queue->last] = new_element;
        queue->size += 1;
        answer = true;
    }
    return answer;
}

Element queue_dequeue(Queue queue)
{
    Element answer = NULL;
    if (!queue_is_empty(queue)) {
        if (queue->first == QUEUE_MAX_SIZE - 1) {
            queue->first = 0;
        } else {
            queue->first += 1;
        }
        queue->size -= 1;
        answer = queue->items[queue->first];
    }
    return answer;
}