#include <stdio.h>
#include <stdlib.h>
#include "delivery_queue.h"

void initDeliveryQueue(DeliveryQueue* q) {
    q->front = q->rear = NULL;
}

int isDeliveryQueueEmpty(DeliveryQueue* q) {
    return q->front == NULL;
}

void enqueueDelivery(DeliveryQueue* q, Order* order) {
    order->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = order;
    } else {
        q->rear->next = order;
        q->rear = order;
    }

    printf("Siparis teslimat kuyruguna alindi. ID: %d\n", order->orderId);
}

Order* dequeueDelivery(DeliveryQueue* q) {
    if (isDeliveryQueueEmpty(q)) {
        printf("Teslimat kuyrugu bos.\n");
        return NULL;
    }

    Order* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    return temp;
}

void listDeliveries(DeliveryQueue* q) {
    if (isDeliveryQueueEmpty(q)) {
        printf("Teslimat kuyrugu bos.\n");
        return;
    }

    Order* temp = q->front;
    printf("\n--- TESLIMAT KUYRUGU ---\n");
    while (temp != NULL) {
        printf("Siparis ID: %d | Muster: %s\n",
               temp->orderId, temp->customerName);
        temp = temp->next;
    }
}
