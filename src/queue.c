#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
        //*TODO: put a new process to queue [q] */
        if (q->size >= MAX_QUEUE_SIZE)
        {
                return;
        }
        q->proc[q->size] = proc;
        q->size++;
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if (!empty(q))
        {
                // uint32_t highest_priority = 0;
                uint32_t id = 0;

                struct pcb_t *pointer_to_highest_priority_proc = q->proc[0];

                //* Search for the highest priority in the queue
                for (int i = 0; i < q->size; i++)
                {
                        if (pointer_to_highest_priority_proc->prio < q->proc[i]->prio)
                        {
                                // highest_priority = q->proc[i]->prio;
                                id = i;
                                pointer_to_highest_priority_proc = q->proc[i];
                        }
                }

                //*Modify the queue after taking the highest priority process out of the queue
                for (int i = id; i < q->size - 1; i++)
                {
                        q->proc[i] = q->proc[i + 1];
                }
                q->proc[q->size - 1] = NULL;
                q->size--;
                return pointer_to_highest_priority_proc;
        }
        else
        {
                return NULL;
        }
}
