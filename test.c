#include <stdio.h>
#include "functions.h"
#include "assert.h"

void testMenu();
void testCreate(Stud **start, FILE *data);
void testInsert(Stud **start);
void testFree(Stud **start);

int main(){
    Stud *start = NULL;

    FILE *data = fopen("testData.txt", "r");
    freopen("test.txt", "r", stdin);

    testMenu();

    testCreate(&start, data);
    printList(start);

    testInsert(&start);
    printList(start);

    testFree(&start);

    fclose(data);
    printf("\nAll function tests passed.\n");
    printf("Exiting the program.\n");
    return 0;
}

void testMenu(){
    int option = printMenu();
    assert(option == 0);
    printf("printMenu function tests passed.\n");
}

void testCreate(Stud **start, FILE *data){
    createList(data, start);
    Stud *temp = *start;
    assert(temp->grade == 1);
    assert((temp->prev == NULL) && (temp->next->prev == temp));

    while(temp->next != NULL){
        temp = temp->next;
    }
    assert(temp->grade == 5);
    assert((temp->prev->next == temp) && (temp->next == NULL));
    printf("createList function tests passed.\n");
}

void testInsert(Stud **start){
    insertToList(start);
    insertToList(start);
    insertToList(start);
    Stud *temp = *start;
    assert(temp->grade == 9);
    assert((temp->prev == NULL) && (temp->next->prev == temp));

    temp = temp->next->next->next;
    assert(temp->grade == 9);
    assert((temp->prev->next == temp) && (temp->next->prev == temp));

    while(temp->next != NULL){
        temp = temp->next;
    }
    assert(temp->grade == 5);
    assert((temp->prev->next == temp) && (temp->next == NULL));
    printf("\ninsertToList function tests passed.\n");
}

void testFree(Stud **start){
    freeList(start);
    assert(*start == NULL);
    printf("\nfreeList function tests passed.\n");
}