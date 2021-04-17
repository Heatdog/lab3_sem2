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

void scan_char(char *k){
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
}

int insert(Table* table, KeySpace1 key1, KeySpace2 key2){
    int n1, n2;
    n1 = insert1(table, key1);
    n2 = insert2(table, key2);
    if (n1 + n2 == 0){
        return 0;
    }


}

int check(Table* table, KeySpace1 key1, KeySpace2 ke2){
    return 0;
}