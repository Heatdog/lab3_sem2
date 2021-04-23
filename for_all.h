//
// Created by yura on 26.03.2021.
//

#ifndef LAB3_SEM2_FOR_ALL_H
#define LAB3_SEM2_FOR_ALL_H



typedef struct inf{
    int first_int;
    int second_int;
    char text[];
}Info;

typedef struct key1{
    int key;
    int par;
    Info *inf;
}KeySpace1;

typedef struct Key2{
    char* key;
    int realese;
    Info* inf;
    struct Key2* next;
}KeySpace2;


typedef struct I{
    Info* inf;
    int key1;
    int Par;
    char* key2;
}Item;


typedef struct k{
    Item* item;
    int n;
}mass_item;

typedef struct t{
    KeySpace1* ks1;
    KeySpace2** ks2;
    mass_item* massItem;
    int msize1;
    int msize2;
    int csize1;
    int csize2;
}Table;

typedef struct n{
    int* mass;
    int n;
}mass_int;




void scan_info(Info* );
void scan_int(int* );
void scan_string(char[]);
char* scan_char(char *);
int dialog(const char*[], int );
void delTable(Table*);
int insert(Table*, KeySpace1, KeySpace2*);
Table *delete_mass_item(Table*, int);

#endif //LAB3_SEM2_FOR_ALL_H
