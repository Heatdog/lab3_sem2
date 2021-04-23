//
// Created by yura on 13.04.2021.
//

#include "key1.h"
#include <stdlib.h>
#include "stdio.h"
#include "key2.h"



const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow", "We can`t add both of keys"};

int D_Add(Table *table){
    int k1, rc, keyParent;
    char* k2 = NULL;
    KeySpace1 key1 = {0, 0,  NULL};
    KeySpace2* key2 = NULL;
    Item item = {NULL, 0, 0 ,NULL};
    printf("Please, enter key from first space in this form: \n");
    printf("Enter key: -->");
    scan_int(&k1);
    printf("Do you want to enter parent key for this key? If you dont want to do it, enter 0\n");
    scan_int(&keyParent);
    printf("Please, enter key from second space in this form: \n");
    k2 = scan_char(k2);
    key2 = malloc(sizeof (KeySpace2));
    key1.key = k1;
    key1.par = keyParent;
    key2->key = k2;
    printf("Enter info:\n");
    item.inf = malloc(sizeof (Info)*2);
    scan_info(item.inf);
    key1.inf = item.inf;
    key2->inf = item.inf;
    item.key1 = k1;
    item.Par = keyParent;
    item.key2 = k2;
    rc = insert(table, key1, key2);
    if (rc == 0){
        if (table->massItem->n == 0){
            table->massItem->item = malloc(sizeof (Item));
        } else{
            table->massItem->item = realloc(table->massItem->item, sizeof (Item)*(table->massItem->n + 1));
        }
        table->massItem->item[table->massItem->n] = item;//закидываем нашу переменную в массив
        table->massItem->n++;
    }
    printf("%s: %d\n", errmsgs[rc], k1);
    return 1;
}


int D_Find(Table* table){
    int k, n, l, i;
    KeySpace2* ks2 = NULL;
    ks2 = malloc(sizeof (KeySpace2));
    char* text = NULL;
    printf("In which space key do you want to find the element? (1 or 2)\n");
    scan_int(&l);
    do{
        printf("Please, enter key -->\n");
        if (l == 1){
            scan_int(&k);
            n = check1(table, k);
        }else if (l == 2){
            text = scan_char(text);
            ks2->key = text;
            i = hash(table, ks2);//номер ячейки
            n = check2(table, ks2, i);//номер
            ks2 = add(ks2, i, n, table);
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
            printf("Key --> %s\n", ks2->key);
            printf("Info --> %d, %d, %s\n", ks2->inf->first_int, ks2->inf->second_int, ks2->inf->text);
        }
    }
    return 1;
}

int D_Delete(Table* table){
    int k, n, l;
    hash_and_len f;
    printf("Please, enter first key -->\n");
    do{
        scan_int(&k);
        n = check1(table, k);//номер в таблице
        if (n == -1){
            printf("We can`t find this element!\n");
        }
    } while (n == -1);
    printf("Please, enter second key -->\n");
    do{
        f = delete_write_2(table);//разбить это
        if (f.len == -1){
            printf("We can`t find this element!\n");
        }
    } while (f.len == -1);
    l = comparison(table, n, f.len, f.hash);
    if (l == -1) {
        printf("the information doesn't match");
    } else{
        delete_2(table, f);
        delete1(table, k);
    }
    table = delete_mass_item(table, n);
    return 1;
}

int D_Show(Table* table){
    printf("Key 1\tParent key\tKey 2\tInfo\n");
    for (int i = 0; i < table->massItem->n; i++){
        printf("%d\t%d\t%s\t%d %d %s\n", table->massItem->item[i].key1, table->massItem->item[i].Par,  table->massItem->item[i].key2,
               table->massItem->item[i].inf->first_int,  table->massItem->item[i].inf->second_int,  table->massItem->item[i].inf->text);
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
