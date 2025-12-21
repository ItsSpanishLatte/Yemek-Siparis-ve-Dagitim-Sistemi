#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order_queue.h"

void initOrderQueue(OrderQueue* q) {
    q->front = q->rear = NULL;
}

int isOrderQueueEmpty(OrderQueue* q) {
    return q->front == NULL;
}

void enqueueOrder(OrderQueue* q, int orderId, int foodId,
                  const char* name, const char* phone, const char* address) {
    Order* newOrder = (Order*)malloc(sizeof(Order));
    if (newOrder == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return;
    }

    newOrder->orderId = orderId;
    newOrder->foodId = foodId;
    strcpy(newOrder->customerName, name);
    strcpy(newOrder->phone, phone);
    strcpy(newOrder->address, address);
    newOrder->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newOrder;
    } else {
        q->rear->next = newOrder;
        q->rear = newOrder;
    }

    printf("Siparis kuyruga eklendi. ID: %d\n", orderId);
}

Order* dequeueOrder(OrderQueue* q) {
    if (isOrderQueueEmpty(q)) {
        printf("Siparis kuyrugu bos.\n");
        return NULL;
    }

    Order* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    return temp;
}

void listOrders(OrderQueue* q) {
    if (isOrderQueueEmpty(q)) {
        printf("Siparis kuyrugu bos.\n");
        return;
    }

    Order* temp = q->front;
    printf("\n--- SIPARIS KUYRUGU ---\n");
    while (temp != NULL) {
        printf("Siparis ID: %d | Yemek ID: %d | Muster: %s\n",
               temp->orderId, temp->foodId, temp->customerName);
        temp = temp->next;
    }
}
