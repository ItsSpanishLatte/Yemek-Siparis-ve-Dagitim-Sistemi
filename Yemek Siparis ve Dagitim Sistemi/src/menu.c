#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

MenuItem* createMenuItem(int id, const char* name, float price, int prepTime) {
    MenuItem* newItem = (MenuItem*)malloc(sizeof(MenuItem));
    if (newItem == NULL) {
        printf("Bellek ayirma hatasi!\n");
        return NULL;
    }
    newItem->id = id;
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->prepTime = prepTime;
    newItem->next = NULL;
    return newItem;
}

void addMenuItem(MenuItem** head, int id, const char* name, float price, int prepTime) {
    MenuItem* newItem = createMenuItem(id, name, price, prepTime);
    if (*head == NULL) {
        *head = newItem;
    } else {
        MenuItem* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newItem;
    }
    printf("Yemek eklendi: %s\n", name);
}

void listMenu(MenuItem* head) {
    if (head == NULL) {
        printf("Menu bos.\n");
        return;
    }

    MenuItem* temp = head;
    printf("\n--- MENU ---\n");
    while (temp != NULL) {
        printf("ID: %d | Ad: %s | Fiyat: %.2f | Sure: %d dk\n",
               temp->id, temp->name, temp->price, temp->prepTime);
        temp = temp->next;
    }
}

void deleteMenuItem(MenuItem** head, int id) {
    if (*head == NULL) {
        printf("Menu bos.\n");
        return;
    }

    MenuItem* temp = *head;
    MenuItem* prev = NULL;

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("ID %d bulunamadi.\n", id);
        return;
    }

    if (prev == NULL)
        *head = temp->next;
    else
        prev->next = temp->next;

    free(temp);
    printf("Yemek silindi.\n");
}

void updateMenuItem(MenuItem* head, int id) {
    MenuItem* temp = head;

    while (temp != NULL && temp->id != id)
        temp = temp->next;

    if (temp == NULL) {
        printf("ID %d bulunamadi.\n", id);
        return;
    }

    printf("Yeni ad: ");
    scanf(" %[^\n]", temp->name);

    printf("Yeni fiyat: ");
    scanf("%f", &temp->price);

    printf("Yeni hazirlama suresi: ");
    scanf("%d", &temp->prepTime);

    printf("Yemek guncellendi.\n");
}

MenuItem* findMenuItem(MenuItem* head, int id) {
    MenuItem* temp = head;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return NULL;
}

void saveMenuToFile(MenuItem* head) {
    FILE* fp = fopen("menu.dat", "wb");
    if (!fp) return;

    MenuItem* temp = head;
    while (temp) {
        fwrite(temp, sizeof(MenuItem) - sizeof(MenuItem*), 1, fp);
        temp = temp->next;
    }
    fclose(fp);
}

MenuItem* loadMenuFromFile() {
    FILE* fp = fopen("menu.dat", "rb");
    if (!fp) return NULL;

    MenuItem* head = NULL;
    MenuItem data;

    while (fread(&data, sizeof(MenuItem) - sizeof(MenuItem*), 1, fp)) {
        addMenuItem(&head, data.id, data.name, data.price, data.prepTime);
    }

    fclose(fp);
    return head;
}

int isMenuIdExists(MenuItem* head, int id) {
    MenuItem* temp = head;
    while (temp) {
        if (temp->id == id)
            return 1;   // Var
        temp = temp->next;
    }
    return 0;           // Yok
}
