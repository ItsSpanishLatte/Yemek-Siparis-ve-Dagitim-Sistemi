#ifndef ORDER_QUEUE_H
#define ORDER_QUEUE_H

typedef struct Order {
    int orderId;
    int foodId;
    char customerName[50];
    char phone[20];
    char address[100];
    struct Order* next;
} Order;

typedef struct {
    Order* front;
    Order* rear;
} OrderQueue;

void initOrderQueue(OrderQueue* q);
int isOrderQueueEmpty(OrderQueue* q);
void enqueueOrder(OrderQueue* q, int orderId, int foodId,
                  const char* name, const char* phone, const char* address);
Order* dequeueOrder(OrderQueue* q);
void listOrders(OrderQueue* q);

#endif
