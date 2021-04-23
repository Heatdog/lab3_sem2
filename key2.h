//
// Created by yura on 13.04.2021.
//

#ifndef LAB3_SEM2_KEY2_H
#define LAB3_SEM2_KEY2_H

#include "for_all.h"


typedef struct y{
    int hash;
    int len;
}hash_and_len;

int insert2(Table*, KeySpace2*);
int hash(Table* ,KeySpace2*);

Table table2_new(Table, int );
int check2(Table*, KeySpace2*, int);
void delete_2(Table*, hash_and_len);
hash_and_len delete_write_2(Table*);
KeySpace2* add(KeySpace2*, int, int, Table*);
int comparison(Table*, int, int, int);


#endif //LAB3_SEM2_KEY2_H