/******************************************************************************/
/*Biblioteca de fila (FIFO) circular com controle de overflow                 */
/*e implementação dupla em lista ligada e vetor.                              */
/*                                                                            */
/*Copyright (C) 2012 André Santos de Medeiros (andsmedeiros@gmail.com)        */
/*Esta biblioteca está licensiada sob a GNU GPLv2                             */
/*(http://www.gnu.org/licenses/gpl-2.0.html)                                  */
/******************************************************************************/
/******************************************************************************/
/*Circular queue (FIFO) library with overflow control and double              */
/*implementation: linked list and array.                                      */
/*                                                                            */
/*Copyright (C) 2012 André Santos de Medeiros (andsmedeiros@gmail.com)        */
/*This library is licensed under GNU GPLv2                                    */
/*(http://www.gnu.org/licenses/gpl-2.0.html)                                  */
/******************************************************************************/

#include "queue.h"
#include <stdlib.h>

#ifndef QUEUE_H
#error "Queue header not included! Do NOT include this file! Aborting!"
#endif /*QUEUE_H*/

#define node_size             (sizeof(struct _node))
#define queue_size            (sizeof(struct _queue))

struct _queue{
    info * ary;
    node first, last;
    bool overflow, underflow;
    int size, count;
};

struct _node{
    info information;
    struct _node * next;
};

#ifdef LL_QUEUE
queue newQueue(int size){
    queue new_queue;
    node last;
    int i;
    new_queue = malloc(queue_size);
    new_queue->first = new_queue->last = malloc(node_size);
    new_queue->overflow = false;
    new_queue->size = size;
    new_queue->count = 0;
    last = new_queue->last;
    for(i=0;i<size-1;i++){
        last->next = malloc(node_size);
        last = last->next;
    }
    last->next = new_queue->first;
    return new_queue;
}

void freeQueue(queue current){
    current->last = current->first->next;
    current->first->next = NULL;
    current->first = current->last;
    do{
        current->last = current->first->next;
        free(current->first);
        current->first = current->last;
    }while(current->first!= NULL);
    free(current);
}

bool full(queue current){
    return((current->count)>=(current->size) ? true : false);
}

bool empty(queue current){
    return((current->count)<=0 ? true : false);
}

bool overflow(queue current){
    return current->overflow;
}

bool underflow(queue current){
    return current->underflow;
}

void push(queue current, info information){
    if(full(current)){
        current->overflow = true;
        return;
    }
    current->last->next->information = information;
    current->last = current->last->next;
    (current->count)<0 ? (current->count) = 1 : (current->count)++;
}

info pop(queue current){
    if(current->count == 0){
        current->underflow = true;
        return NULL;
    }

    info information = current->first->information;
    current->first = current->first->next;
    (current->count)--;
    return information;
}

void clearOverflow(queue current){
    current->overflow = false;
}

int queueSize(queue current){
    return current->size;
}

int elemsCount(queue current){
    return current->count;
}

#elif defined ARY_QUEUE
#define inc(X)                ((X)+1)%current->size
queue newQueue(int size){
    queue new_queue = malloc(queue_size);
    new_queue->ary = malloc(size * sizeof(info));
    new_queue->first = new_queue->last = 0;
    new_queue->overflow = false;
    new_queue->count = 0;
    new_queue->size = size;
    return new_queue;
}

void freeQueue(queue current){
    free(current->ary);
    free(current);
}

bool full(queue current){
    return((current->count)>=(current->size) ? true : false);
}

bool empty(queue current){
    return(current->count<=0 ? true : false);
}

bool overflow(queue current){
    return current->overflow;
}

void push(queue current, info information){
    if(full(current)){
        current->overflow = true;
        return;
    }
    current->last = inc(current->last);
    current->ary[current->last] = information;
    (current->count)<0 ? (current->count) = 1 : (current->count)++;
}

info pop(queue current){
    info information = current->ary[current->first];
    current->first = inc(current->first);
    (current->count)--;
    return information;
}

void clearOverflow(queue current){
    current->overflow = false;
}

int queueSize(queue current){
    return current->size;
}

int elemsCount(queue current){
    return current->count;
}

#endif
