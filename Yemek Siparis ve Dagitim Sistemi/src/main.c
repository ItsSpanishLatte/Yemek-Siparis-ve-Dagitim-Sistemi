#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void showMainMenu() {
    printf("\n--- Yemek Siparis ve Dagitim Sistemi ---\n");
    printf("1. Menuye yemek ekle\n");
    printf("2. Menuyu listele\n");
    printf("3. Yemek sil\n");
    printf("4. Yemek guncelle\n");
    printf("0. Cikis\n");
    printf("Seciminiz: ");
}

int main() {
    MenuItem* menu = NULL;
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

    } while (choice != 0);

    printf("Programdan cikiliyor...\n");
    return 0;
}
