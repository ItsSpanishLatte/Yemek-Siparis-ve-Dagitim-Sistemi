#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "order_queue.h"
#include "delivery_queue.h"
#include "income_stack.h"

void showMainMenu() {
    printf("\n--- Yemek Siparis ve Dagitim Sistemi ---\n");
    printf("1. Menuye yemek ekle\n");
    printf("2. Menüyü listele\n");
    printf("3. Yemek sil\n");
    printf("4. Yemek guncelle\n");
    printf("5. Yeni siparis ekle\n");
    printf("6. Siparisleri listele\n");
    printf("7. Siradaki siparisi hazirla (teslimata aktar)\n");
    printf("9. Teslimat kuyrugunu listele\n");
    printf("10. Siparisi teslim et (gelire ekle)\n");
    printf("11. Gelir kayitlarini listele\n");
    printf("12. Secilen gun toplam gelir\n");
    printf("0. Cikis\n");
    printf("Seciminiz: ");
}

int main() {
    MenuItem* menu = NULL;

    OrderQueue orderQueue;
    initOrderQueue(&orderQueue);

    DeliveryQueue deliveryQueue;
    initDeliveryQueue(&deliveryQueue);

    IncomeNode* incomeStack = NULL;

    int choice;

    do {
        showMainMenu();
        scanf("%d", &choice);

        if (choice == 1) {
            int id, prep;
            float price;
            char name[50];

            printf("Yemek ID: ");
            scanf("%d", &id);

            printf("Yemek Adi: ");
            scanf(" %[^\n]", name);

            printf("Fiyat: ");
            scanf("%f", &price);

            printf("Hazirlama Suresi (dk): ");
            scanf("%d", &prep);

            addMenuItem(&menu, id, name, price, prep);
        }
        else if (choice == 2) {
            listMenu(menu);
        }
        else if (choice == 3) {
            int id;
            printf("Silinecek yemek ID: ");
            scanf("%d", &id);
            deleteMenuItem(&menu, id);
        }
        else if (choice == 4) {
            int id;
            printf("Guncellenecek yemek ID: ");
            scanf("%d", &id);
            updateMenuItem(menu, id);
        }
        else if (choice == 5) {
            int orderId, foodId;
            char cname[50], phone[20], address[100];

            printf("Siparis ID: ");
            scanf("%d", &orderId);

            printf("Yemek ID: ");
            scanf("%d", &foodId);

            printf("Musteri adi: ");
            scanf(" %[^\n]", cname);

            printf("Telefon: ");
            scanf(" %[^\n]", phone);

            printf("Adres: ");
            scanf(" %[^\n]", address);

            enqueueOrder(&orderQueue, orderId, foodId, cname, phone, address);
        }
        else if (choice == 6) {
            listOrders(&orderQueue);
        }
        else if (choice == 7) {
            Order* o = dequeueOrder(&orderQueue);
            if (o != NULL) {
                printf("Siparis hazirlandi ve teslimata aktarildi: ID %d\n", o->orderId);
                enqueueDelivery(&deliveryQueue, o);
            }
        }
        else if (choice == 9) {
            listDeliveries(&deliveryQueue);
        }
        else if (choice == 10) {
            Order* o = dequeueDelivery(&deliveryQueue);
            if (o != NULL) {
                char date[20];
                float amount = 0.0f;

                printf("Siparis teslim edildi: ID %d | Musteri: %s\n", o->orderId, o->customerName);
                printf("Tarih (YYYY-MM-DD): ");
                scanf(" %19s", date);

                MenuItem* m = findMenuItem(menu, o->foodId);
                if (m != NULL) {
                    amount = m->price;
                } else {
                    printf("Yemek bulunamadi (FoodID=%d). Tutari manuel gir: ", o->foodId);
                    scanf("%f", &amount);
                }

                pushIncome(&incomeStack, o->orderId, amount, date);

                printf("Gelire eklendi -> SiparisID: %d | Tutar: %.2f | Tarih: %s\n",
                       o->orderId, amount, date);

                free(o);
            }
        }
        else if (choice == 11) {
            listIncomes(incomeStack);
        }
        else if (choice == 12) {
            char date[20];
            printf("Hangi gun? (YYYY-MM-DD): ");
            scanf(" %19s", date);

            float total = calculateDailyIncome(incomeStack, date);
            printf("%s tarihli toplam gelir: %.2f\n", date, total);
        }

    } while (choice != 0);

    printf("Programdan cikiliyor...\n");
    return 0;
}
