#include <stdio.h>
#include "for_all.h"
#include <stdlib.h>
#include "dialog.h"
#include "key2.h"



int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete ,D_Show, D_Show_Par};
const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Show (use parent key)"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const int Msize = 7;


int main() {
    Table table = {NULL, NULL, Msize, Msize, 0,0};
    int rc;
    table.ks1 = calloc(Msize, sizeof (KeySpace1));
    table = table2_new(table, Msize);
    while ((rc = dialog(msgs, NMsgs)))
        if (!fptr[rc](&table))
            break;
    printf("That's all. Bye!\n");
    delTable(&table);
    return 0;
}