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
        // /* TODO: put a new process to queue [q] */
        q->proc[q->size++] = proc;
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose priority is the highest
         * in the queue [q] and remember to remove it from q
         * */
        struct pcb_t *returnProc = NULL;
        if(q->size > 0){
                int indexMin = 0;
                for(int i=0;i<q->size;i++){
                        if(q->proc[i]->prio < q->proc[indexMin]->prio){
                                indexMin = i;
                        }
                }
                returnProc = q->proc[indexMin];
                for(int i=indexMin;i <q->size-1;i++){
                        q->proc[i] = q->proc[i+1];
                }
                q->size --;
        }
        
        return returnProc;
}
