//
// Created by yura on 13.04.2021.
//

#include "key2.h"
#include <string.h>
#include <stdlib.h>

int insert2(Table* table, KeySpace2 kS2){
    int i = hash(table, kS2);
    KeySpace2* ptr;
    if (check2(table, kS2) >= 0){
        return 1;//дублирование ключей
    }
    if (table->csize2 > table->msize2){
        return 2;//переполнение
    }
    if (table->ks2[i].realese == 0){
        table->ks2[i].key = kS2.key;
        table->ks2[i].next = NULL;
        table->ks2[i].realese++;
        table->ks2[i].inf = kS2.inf;
        table->csize1++;
    }else{
        ptr = &table->ks2[i];//берем адрес ячейки с первым ключом
        table->ks2[i] = kS2;//вставляем нашу новую структуру
        table->ks2[i].next = ptr;//делаем связку старого с новым
        table->ks2[i].realese++;
    }
    return 0;//все ок
}

int hash(Table* table,KeySpace2 kS2){//метод горнера
    int hash_result = 0;
    for (int i = 0; i < strlen(kS2.key); i++){
        hash_result = (hash_result^(int)kS2.key[i]) % table->msize2;
    }
    hash_result = (hash_result*2+1) % table->msize2;
    return hash_result;
}


int check2(Table* table, KeySpace2 ks2){
    int i = hash(table, ks2);
    int l = 0;
    char* key = table->ks2[i].key;
    if (table->ks2[i].realese == 0){
        return -1;//нет такого элемента (в принципе)
    } else{
        while (key != NULL){
            l++;
            if (key == ks2.key){
                return l;
            } else{
                key = table->ks2[i].next->key;
            }
        }
        return -1;
    }
}

Table table2_new(Table table, int Msize){
    table.ks2 = calloc(Msize, sizeof (KeySpace2));
    for (int i = 0; i < table.msize2; i++){
        table.ks2[i].inf = NULL;
        table.ks2[i].realese = 0;
        table.ks2[i].next = NULL;
        table.ks2[i].key = NULL;
    }
    return table;
}