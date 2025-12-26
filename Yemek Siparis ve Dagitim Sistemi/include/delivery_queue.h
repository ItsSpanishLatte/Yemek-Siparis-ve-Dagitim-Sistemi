#ifndef DELIVERY_QUEUE_H
#define DELIVERY_QUEUE_H

#include "order_queue.h"

typedef struct {
    Order* front;
    Order* rear;
} DeliveryQueue;

void initDeliveryQueue(DeliveryQueue* q);
int isDeliveryQueueEmpty(DeliveryQueue* q);
void enqueueDelivery(DeliveryQueue* q, Order* order);
Order* dequeueDelivery(DeliveryQueue* q);
void listDeliveries(DeliveryQueue* q);
void freeDeliveryQueue(DeliveryQueue* q);

#endif
