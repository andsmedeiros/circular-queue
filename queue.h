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

typedef enum{
    false,
    true
} bool;


typedef unsigned char info;

#ifndef QUEUE_H
#define QUEUE_H


#if !(defined LL_QUEUE) && !(defined ARY_QUEUE)
    #define WARN_MSG 
    #warning "No queue mode defined. Assuming linked list mode!"
    #define LL_QUEUE
#endif /*!(defined LL_QUEUE) && !(defined ARY_QUEUE)*/

#ifdef LL_QUEUE
    #ifndef WARN_MSG
        #warning "Linked list queue mode!"
    #endif /*WARN_MSG*/

    typedef struct _node * node;
    typedef struct _queue* queue;

#elif defined ARY_QUEUE
    #ifndef WARN_MSG
        #warning "Array queue mode!"
    #endif /*WARN_MSG*/

    typedef int node;
    typedef struct _queue* queue;
#endif /*LL_QUEUE*/

/*Cria nova fila com o número de elementos especificados*/
queue newQueue(int);

/*Libera a memória da fila passada via argumento*/
void freeQueue(queue);

/*Retorna true se a fila estiver cheia; false caso contrário*/
bool full(queue);

/*Retorna true se a fila estiver vazia; false caso contrário*/
bool empty(queue);

/*Retorna true se houver ocorrido um overflow; false caso contrário*/
bool overflow(queue);

/*Checa se há espaço na fila e, caso haja, enfileira o elemento passado*/
void push(queue, info);

/*Desenfileira um elemento. NÃO VERIFICA SE A FILA ESTÁ VAZIA!*/
info pop(queue);

/*Limpa a bandeira de overflow de uma fila*/
void clearOverflow(queue);

/*Retorna o tamanho total da fila*/
int queueSize(queue);

/*Retorna o total de elementos enfileirados*/
int elemsCount(queue);
#endif  /* QUEUE_H */

