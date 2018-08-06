#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

typedef struct LinkNode
{
    int data;
    struct LinkNode *next;
}Node;

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;

Node *CreatNode(int data)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    if(NULL == newnode)
    {
        perror("malloc");
        return NULL;
    }

    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

Node *InitLink()
{
    return CreatNode(0);
}

int IsEmpty(Node *head)
{
    if(head->next)
    {
        return 0;
    }
    else
        return 1;
}

void PushFront(Node *head, int data)
{
    Node *newnode = CreatNode(data);
    newnode->next = head->next;
    head->next = newnode;
}

void PopFront(Node *head, int *data)
{

    assert(data);
    assert(head);
    if(IsEmpty(head))
    {
        printf("empty link\n");
        return;
    }
    Node *del = head->next;
    *data = del->data;
    head->next = del->next;
    free(del);
    del = NULL;
}

void DestroyLink(Node *head)
{
    int data = 0;
    assert(head);
    while(!IsEmpty(head))
    {
        PopFront(head, &data);
    }
    free(head);
}

void *product_run(void *arg)
{
    int data = 0;
    Node *head = (Node *)arg;
    while(1)
    {
        sleep(1);
        data = rand() % 1000;
        pthread_mutex_lock(&mylock);
        PushFront(head, data);
        pthread_mutex_unlock(&mylock);
        pthread_cond_signal(&mycond);
        printf("product is done, data=%d\n", data);
    }
}

void *consumer_run(void *arg)
{
    int data = 0;
    Node *head = (Node *)arg;
    while(1)
    {
        pthread_mutex_lock(&mylock);
        while(IsEmpty(head))
            pthread_cond_wait(&mycond, &mylock);
        PopFront(head, &data);
        pthread_mutex_unlock(&mylock);
        printf("consumer is done, data=%d\n", data);
    }
}

void testprocon()
{
    Node *head = InitLink();
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, product_run, (void*)head);
    pthread_create(&tid2, NULL, consumer_run, (void*)head);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    DestroyLink(head);
    pthread_mutex_destroy(&mylock);
    pthread_cond_destroy(&mycond);

}

int main()
{
    testprocon();
    return 0;
}
