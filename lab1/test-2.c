
#include <stdio.h>
#include <stdlib.h> 
#define FULL 100

typedef struct node
{
    int passenger;
    struct node *next;
} node;

typedef struct queue
{
    int count;
    node *front;
    node *rear;
} queue;

void initialize (queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

int isempty (queue *q)
{
    return (q->rear == NULL);
}

void enqueue (queue *q, int value)
{
    if (q->count < FULL)
    {
        node *tmp;
        tmp = (node *) calloc(1, sizeof(node));
        tmp->passenger = value;
        tmp->next = NULL;
        if (!isempty (q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
        }
        else
        {
            q->front = q->rear = tmp;
        }
        q->count++;
    }
    else
    {
        printf ("Sorry. The queue is full.\n");
    }
}

int dequeue (queue *q)
{
    node *tmp;
    int n = q->front->passenger;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free (tmp);
    return (n);
}

void display (node *head)
{
    if (head == NULL)
    {
        printf ("NULL\n");
    }
    else
    {
        printf (" ", head -> passenger);
        display(head->next);
    }
}

int main (void)
{
    queue *q;
    q = (queue *) calloc(1, sizeof(queue));
    
    initialize(q);
    enqueue(q,1345);
    enqueue(q,2678);
    enqueue(q,3951);
    
    printf ("Passengers waiting in line: ");
    display(q->front);
   
    dequeue(q);
    printf("Passengers now waiting in line: ");
    display(q->front);
    
    return (0);
}