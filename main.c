//LSP - 2213732, el. paštas - martynas.jonkus@mif.stud.vu.lt
//4 pratybų užduotis, 9 variantas
#include <stdio.h>
#include "functions.h"

int main(){
    Stud *start = NULL;

    FILE *data;
    openFile(&data);

    int option;
    while((option = printMenu()) != 4){
        if(option == 0)
            createList(data, &start);
        if(option == 1)
            printList(start);
        if(option == 2)
            insertToList(&start);
        if(option == 3)
            freeList(&start);
    }

    fclose(data);
    freeList(&start);
    printf("Exiting the program.\n");
    return 0;
}