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


typedef struct t{
    KeySpace1* ks1;
    KeySpace2* ks2;
    int msize1;
    int msize2;
    int csize1;
    int csize2;
}Table;

typedef struct n{
    int* mass;
    int n;
}mass_int;

typedef struct I{
    Info* inf;
    int key1;
    char* key2;
}Item;



void scan_info(Info* );
void scan_int(int* );
void scan_string(char[]);
void scan_char(char *);
int dialog(const char*[], int );
void delTable(Table*);
int insert(Table*, KeySpace1, KeySpace2);

#endif //LAB3_SEM2_FOR_ALL_H
