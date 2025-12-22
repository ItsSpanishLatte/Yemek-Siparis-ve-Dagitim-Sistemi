#ifndef INCOME_STACK_H
#define INCOME_STACK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IncomeNode {
    int orderId;
    float amount;
    char date[20];
    struct IncomeNode* next;
} IncomeNode;

void pushIncome(IncomeNode** top, int orderId, float amount, const char* date);
void listIncomes(IncomeNode* top);
float calculateDailyIncome(IncomeNode* top, const char* date);
void saveIncomeToFile(IncomeNode* top);
IncomeNode* loadIncomeFromFile();

#ifdef __cplusplus
}
#endif

#endif
