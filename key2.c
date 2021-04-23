//
// Created by yura on 13.04.2021.
//

#include "key2.h"
#include <string.h>
#include <stdlib.h>

int insert2(Table* table, KeySpace2* kS2){
    int i = hash(table, kS2);
    KeySpace2* ptr_prev = NULL;
    int j = check2(table, kS2, i);
    if (j >= 0){
        return 1;//дублирование ключей
    }
    if (table->csize2 > table->msize2){
        return 2;//переполнение
    }
    if (table->ks2[i]->realese == 0){
        table->ks2[i]->key = kS2->key;
        table->ks2[i]->next = NULL;
        table->ks2[i]->realese++;
        table->ks2[i]->inf = kS2->inf;
        table->csize1++;
    }else{
        ptr_prev = table->ks2[i];//проверить
        table->ks2[i] = kS2;
        table->ks2[i]->next = ptr_prev;
        table->ks2[i]->realese++;
    }
    return 0;//все ок
}

int hash(Table* table,KeySpace2* kS2){//метод горнера
    int hash_result = 0;
    for (int i = 0; i < strlen(kS2->key); i++){
        hash_result = (hash_result^(int)kS2->key[i]) % table->msize2;
    }
    hash_result = (hash_result*2+1) % table->msize2;
    return hash_result;
}


int check2(Table* table, KeySpace2* ks2, int i){
    int l = 0;
    char* key = table->ks2[i]->key;
    if (table->ks2[i]->realese == 0){
        return -1;//нет такого элемента (в принципе)
    } else{
        while (key != NULL){
            if (strcmp(key, ks2->key) == 0){
                return l;
            } else{
                key = table->ks2[i]->next->key;
            }
            l++;
        }
        return -1;
    }
}

Table table2_new(Table table, int Msize){
    table.ks2 = calloc(Msize, sizeof (KeySpace2));
    for (int i = 0; i < table.msize2; i++){
        table.ks2[i] = malloc(sizeof (KeySpace2));
        table.ks2[i]->inf = NULL;
        table.ks2[i]->realese = 0;
        table.ks2[i]->next = NULL;
        table.ks2[i]->key = NULL;
    }
    return table;
}



hash_and_len delete_write_2(Table* table){
    KeySpace2* ks2 = NULL;
    char* k = NULL;
    hash_and_len m;
    k = scan_char(k);
    int n, i;
    ks2 = malloc(sizeof (KeySpace2));
    ks2->key = k;
    i = hash(table, ks2);
    n = check2(table, ks2, i);
    m.hash = i;
    m.len = n;
    return m;
}

void delete_2(Table* table, hash_and_len m){
    KeySpace2 *ptr = NULL, *ptr_next = NULL;
    int n = m.len, i = m.hash;
    for (int j = 0; j < n-1; j++){
        ptr = table->ks2[i];
        ptr = ptr->next;
    }
    if (n == 0){
        ptr = table->ks2[i];
        table->ks2[i] = NULL;
        free(ptr);
    } else{
        ptr_next = ptr->next;
        ptr->next = ptr->next->next;
        free(ptr_next);
        table->ks2[i]->realese--;
    }
}

KeySpace2* add(KeySpace2* ks2, int i, int l, Table* table){
    KeySpace2* ptr = NULL;
    for (int j = 0; j < l; j++){
        ptr = table->ks2[i];
        ptr = ptr->next;
    }
    if (l == 0){
        ptr = table->ks2[i];
    }
    ks2 = ptr;
    return ks2;
}

int comparison(Table* table, int number1, int len, int hash){
    KeySpace2 *ptr = NULL;
    for (int i = 0; i < len; i++){
        ptr = table->ks2[hash];
        ptr = ptr->next;
    }
    if (len == 0){
        ptr = table->ks2[hash];
    }
    if (table->ks1[number1].inf == ptr->inf){
        return 0;
    }
    return -1;
}

