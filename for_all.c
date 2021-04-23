//
// Created by yura on 26.03.2021.
//

#include "for_all.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "key1.h"
#include "key2.h"

const char wrong[] = "You're wrong! Please, try again!\n";

void scan_int(int* i){
    int n;
    do {
        n = scanf("%d", i);
        if (n != 1){
            printf("%s", wrong);
            scanf("%*c");
        }
    } while (n != 1);
}

void scan_string(char text[]){
    int n;
    do{
        n = scanf("%s", text);
        if (n != 1){
            printf("%s", wrong);
            scanf("%*c");
        }
    } while (n != 1);
}

void scan_info(Info* inf){
    printf("Please, enter first number:\n");
    scan_int(&inf->first_int);
    printf("Please, enter second number:\n");
    scan_int(&inf->second_int);
    printf("Please, enter text\n");
    scan_string(inf->text);

}

int dialog(const char *msgs[], int N)
{
    int rc;
    int i;
    for(i = 0; i < N; ++i)
        puts(msgs[i]);
    puts("Make your choice: --> ");
    do {
        scan_int(&rc);
        if (rc > N-1 || rc < 0){
            puts("Try again!");
        }
    } while (rc > N-1 || rc < 0);
    return rc;
}

void delTable(Table* table){
    for (int i = 0; i < table->csize1; i++) {
        free(table->ks1[i].inf);
    }
    free(table->ks1);
}

char* scan_char(char *k){
    int n;
    char i[100];
    int len;
    do {
        n = scanf("%s", i);
        if (n != 1){
            printf("%s", wrong);
            scanf("%*c");
        }
    } while (n != 1);
    len = strlen(i);
    k = calloc(len + 1, sizeof (char ));
    memcpy(k, i, len+1);
    return k;
}

int insert(Table* table, KeySpace1 key1, KeySpace2* key2){
    int n1, n2;
    int k;
    n1 = insert1(table, key1);
    n2 = insert2(table, key2);
    if (n1 ==0 && n2 == 0){
        return 0;
    } else if (n1 == 1 || n2 == 1){
        if (n1 == 0){//если 2 не подошел, а 1 подошел
            k = check1(table, key1.key);
            delete1(table, k);
        }
        return 1;
    } else {
        if (n1 == 0){//аналогично
            k = check1(table, key1.key);
            delete1(table, k);
        }
        return 2;
    }
}


Table *delete_mass_item(Table* table, int number){
    for (int i = 0; i < table->massItem->n-1; i++){
        if (strcmp(table->ks1[number].inf->text, table->massItem[i].item->inf->text) == 0 &&
        table->ks1[number].inf->first_int == table->massItem[i].item->inf->first_int &&
        table->ks1[number].inf->second_int == table->massItem[i].item->inf->second_int){
            table->massItem[i] = table->massItem[table->massItem->n];
        }
    }
    table->massItem->n--;
    return table;
}
