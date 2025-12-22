#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "income_stack.h"

void pushIncome(IncomeNode** top, int orderId, float amount, const char* date) {
    IncomeNode* node = (IncomeNode*)malloc(sizeof(IncomeNode));
    if (node == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return;
    }
    node->orderId = orderId;
    node->amount = amount;
    strcpy(node->date, date);
    node->next = *top;
    *top = node;
}

void listIncomes(IncomeNode* top) {
    if (top == NULL) {
        printf("Gelir kaydi yok.\n");
        return;
    }

    printf("\n--- GELIR KAYITLARI (STACK) ---\n");
    IncomeNode* cur = top;
    while (cur != NULL) {
        printf("SiparisID: %d | Tutar: %.2f | Tarih: %s\n",
               cur->orderId, cur->amount, cur->date);
        cur = cur->next;
    }
}

float calculateDailyIncome(IncomeNode* top, const char* date) {
    float sum = 0.0f;
    IncomeNode* cur = top;

    while (cur != NULL) {
        if (strcmp(cur->date, date) == 0) {
            sum += cur->amount;
        }
        cur = cur->next;
    }
    return sum;
}
