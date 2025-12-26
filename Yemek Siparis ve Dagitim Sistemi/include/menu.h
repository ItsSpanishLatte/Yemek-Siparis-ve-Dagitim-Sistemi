#ifndef MENU_H
#define MENU_H

typedef struct MenuItem {
    int id;
    char name[50];
    float price;
    int prepTime;
    struct MenuItem* next;
} MenuItem;

MenuItem* createMenuItem(int id, const char* name, float price, int prepTime);
void addMenuItem(MenuItem** head, int id, const char* name, float price, int prepTime);
void listMenu(MenuItem* head);
void deleteMenuItem(MenuItem** head, int id);
void updateMenuItem(MenuItem* head, int id);
MenuItem* findMenuItem(MenuItem* head, int id);
void saveMenuToFile(MenuItem* head);
MenuItem* loadMenuFromFile();
int isMenuIdExists(MenuItem* head, int id);

#endif

