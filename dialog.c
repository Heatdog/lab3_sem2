//
// Created by yura on 13.04.2021.
//

#include "key1.h"
#include <stdlib.h>
#include "stdio.h"
#include "key2.h"
#include <string.h>


const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};

int D_Add(Table *table){
    int k1, rc, keyParent;
    char* k2 = NULL;
    KeySpace1 key1 = {0, 0,  NULL};
    KeySpace2 key2 = {NULL, 0, NULL, NULL};
    Item item = {NULL, 0, NULL};
    printf("Please, enter key from first space in this form: \n");
    printf("Enter key: -->");
    scan_int(&k1);
    printf("Do you want to enter parent key for this key? If you dont want to do it, enter 0\n");
    scan_int(&keyParent);
    printf("Please, enter key from second space in this form: \n");
    scan_char(k2);
    key1.key = k1;
    key1.par = keyParent;
    strcpy(key2.key, k2);
    printf("Enter info:\n");
    item.inf = malloc(sizeof (Info)*2);
    scan_info(item.inf);
    key1.inf = item.inf;
    key2.inf = item.inf;
    rc = insert(table, key1, key2);
    printf("%s: %d\n", errmsgs[rc], k1);
    return 1;
}


int D_Find(Table* table){
    int k, n, l;
    KeySpace2 ks2;
    printf("In which space key do you want to find the element? (1 or 2)\n");
    scan_int(&l);
    do{
        printf("Please, enter key -->\n");
        if (l == 1){
            scan_int(&k);
            n = check1(table, k);
        }else if (l == 2){
            scan_char(ks2.key);
            n = check2(table, ks2);
        } else{
            printf("you`re wrong!\n");
        }
    } while (l != 1 && l != 2);
    if (n == -1){
        printf("We can`t find element with that key!\n");
    } else{
        printf("Search result: \n");
        if (l == 1){
            printf("Key --> %d\n", table->ks1[n].key);
            printf("Parent key --> %d\n", table->ks1[n].par);
            printf("Info --> %d, %d, %s\n", table->ks1[n].inf->first_int, table->ks1[n].inf->second_int, table->ks1[n].inf->text);
        } else{
            printf("Key --> %s\n", ks2.key);
            printf("Info --> %d, %d, %s\n", ks2.inf->first_int, ks2.inf->second_int, ks2.inf->text);
        }
    }
    return 1;
}

int D_Delete(Table* table){
    int k, n;
    printf("Please, enter key -->\n");
    scan_int(&k);
    n = check1(table, k);
    if (n == -1){
        printf("We can`t find this element!\n");
    } else{
        delete1(table, n);
    }
    return 1;
}

int D_Show(Table* table){
    KeySpace1 keyS;
    KeySpace2 keyS2;
    printf("Key 1\tParent key\tKey 2\tInfo\n");
    for (int i = 0; i < table->csize1; i++){
        keyS = table->ks1[i];

        printf("%d\t%d\t%d %d %s\n", keyS.key, keyS.par, keyS.inf->first_int, keyS.inf->second_int, keyS.inf->text);
    }
    return 1;
}

int D_Show_Par(Table* table){
    int keyPar;
    mass_int mass_int = {NULL, 0};
    Table* table_new = NULL;
    printf("Please, enter parent key -->\n");
    scan_int(&keyPar);//родительский ключ
    mass_int = check_par1(table, keyPar);//массив номеров дочерних ключей (в нем находятся сами ключи)
    if (mass_int.mass == NULL){
        printf("We can`t find any key with this parent key!\n");
    } else{
        printf("Key\tParent key\tInfo\n");
        show_par1(table, mass_int, table_new);
    }
    free(mass_int.mass);
    return 1;
}
