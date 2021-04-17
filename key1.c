//
// Created by yura on 26.03.2021.
//

#include "key1.h"
#include <stdio.h>
#include "stdlib.h"





int search1(Table* table, KeySpace1 keySp){
    int key = keySp.key;
    if (check1(table, key) >= 0){
        return -1;//дублирование ключей
    }
    if (keySp.par == 0){
        return 1;//нет родительского элемента
    } else{
        if (check1(table, keySp.par) == -1){
            return -1;//не нашли род элемента
        } else{
            return 1;//наши род элемент
        }
    }
}

int check1(Table* table, int key){
    for (int i = 0; i < table->csize1; i++){
        if (key == table->ks1[i].key){
            return i;
        }
    }
    return -1;
}

mass_int check_par1(Table* table, int keyPar){
    mass_int mass;
    int* all = NULL;
    int n = 0;
    for (int i = 0; i < table->csize1; i++) {
        if (keyPar == table->ks1[i].par){
            n++;
            if (all == NULL){
                all = malloc(sizeof (int));
            } else{
                all = realloc(all, n*sizeof (int ));
            }
            all[n-1] = table->ks1[i].key;
        }
    }
    mass.mass = all;
    mass.n = n;
    return mass;
}

int insert1(Table* table, KeySpace1 keySp){
    if (search1(table, keySp) == -1){
        return 1;//дублирование ключей или не нашли родительский элемент
    }
    if (table->csize1 > table->msize1){
        return 2;//переполнение
    }
    table->ks1[table->csize1] = keySp;
    table->csize1++;
    return 0;
}

void delete1(Table* table, int n){
    int key = table->ks1[n].key, l;
    mass_int MassInt = {NULL, 0};
    MassInt = check_par1(table, key);//массив всех дочек (находятся сами ключи)
    for (int i = 0; i < MassInt.n; i++){
        l = check1(table, MassInt.mass[i]);
        table->ks1[l].par = 0;//зануляем родительский
    }
    table->ks1[n] = table->ks1[table->csize1-1];
    table->csize1--;
    free(MassInt.mass);
}

void show_par1(Table* table, mass_int massInt, Table* table_new){
    KeySpace1 keyS;
    int j;
    table_new = malloc(sizeof (Table));
    table_new->ks1 = calloc(massInt.n, sizeof (KeySpace1));
    table_new->csize1 = massInt.n;
    table_new->msize1 = table_new->csize1;
    for (int i = 0; i < table_new->csize1; i++){
        table_new->ks1[i].inf = malloc(sizeof (Info)*2);
        j = check1(table, massInt.mass[i]);//номер ключа
        table_new->ks1[i] = table->ks1[j];
        keyS = table_new->ks1[i];
        printf("%d\t%d\t%d %d %s\n", keyS.key, keyS.par, keyS.inf->first_int, keyS.inf->second_int, keyS.inf->text);
    }
    delTable(table_new);
    free(table_new);
}
