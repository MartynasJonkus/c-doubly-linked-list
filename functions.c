#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "functions.h"

void freeList(Stud **start){
    Stud *temp;

    while(*start != NULL){
        temp = *start;
        *start = (*start)->next;
        free(temp->firstName);
        free(temp->lastName);
        temp->prev = NULL;
        temp->next = NULL;
        free(temp);
    }

    *start = NULL;
    printf("List memory freed. Pointers set to NULL.\n");
}

/*void insertToList(Stud **start){
    Stud *temp = *start;
    if(temp == NULL){
        printf("The list has no nodes yet.\n");
        return;
    }

    assert(temp != NULL);

    int nodeCount = 1;
    while(temp->next != NULL){
        ++nodeCount;
        temp = temp->next;
    }

    int index;
    do{
        printf("Input the index of the node, before which you want to insert the new node:\n");
        index = Validation(0, nodeCount - 1);
    }while(index == -1);


    int bufferSize = 255;
    char buffer[255];
    char firstName[30], lastName[30];
    int grade;

    while(1){
        printf("Input the data, format - ([firstName] [lastName] [grade]), names upto 30 letters:\n");
        fgets(buffer, bufferSize + 1, stdin);
        int valid = sscanf(buffer, "%s%s%d", firstName, lastName, &grade);
        if(valid == 3 && grade > 0 && grade <= 10)
            break;
        printf("Wrong input format.\n");
    }

    Stud *newNode = getNewNode(firstName, lastName, grade);
    temp = *start;
    for(int i = 0; i < index; ++i){
        temp = temp->next;
    }

    newNode->prev = temp->prev;
    temp->prev = newNode;
    newNode->next = temp;
    if(newNode->prev != NULL)
        newNode->prev->next = newNode;
    if(index == 0)
        *start = newNode;
}*/

void insertToList(Stud **start){
    Stud *temp = *start;
    if(temp == NULL){
        printf("The list has no nodes yet.\n");
        return;
    }
    assert(temp != NULL);

    printf("Input the index of the node, before which you want to insert the new node:\n");
    int index = Validation(0, INT_MAX);

    int bufferSize = 255;
    char buffer[255];
    char firstName[30], lastName[30];
    int grade;

    while(1){
        printf("Input the data, format - ([firstName] [lastName] [grade]), names upto 30 letters:\n");
        fgets(buffer, bufferSize + 1, stdin);
        int valid = sscanf(buffer, "%s%s%d", firstName, lastName, &grade);
        if(valid == 3 && grade > 0 && grade <= 10)
            break;
        printf("Wrong input format.\n");
    }

    Stud *newNode = getNewNode(firstName, lastName, grade);
    temp = *start;
    for(int i = 0; i <= index; ++i){
        if(i == index && temp != NULL){
            newNode->prev = temp->prev;
            temp->prev = newNode;
            newNode->next = temp;
            if(newNode->prev != NULL)
                newNode->prev->next = newNode;
            if(index == 0)
                *start = newNode;
            break;
        }
        if(temp->next == NULL){
            free(newNode);
            printf("Wrong index input. Exceeds range of list.\n");
            break;
        }
        temp = temp->next;
    }
}

void createList(FILE *inputFile, Stud **start){
    assert(inputFile != NULL);

    int bufferSize = 255;
    char buffer[255];
    char firstName[30], lastName[30];
    int grade;
    char enter;

    while(fgets(buffer, bufferSize + 1, inputFile)){
        if((sscanf(buffer, "%s%s%d%c", firstName, lastName, &grade, &enter) == 4) && enter == '\n'){
            Stud *newNode = getNewNode(firstName, lastName, grade);
            Stud *temp = *start;
            if(*start == NULL){
                *start = newNode;
                continue;
            }
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    printf("List succesfully created.\n");
}

Stud *getNewNode(char firstName[], char lastName[], int grade){
    assert((grade > 0) && (grade <= 10) && strlen(firstName) <= 31 && strlen(lastName) <= 31);

    Stud *newNode = malloc(sizeof(Stud));

    newNode->firstName = malloc(strlen(firstName) + 1);
    strcpy(newNode->firstName, firstName);
    newNode->lastName = malloc(strlen(lastName) + 1);
    strcpy(newNode->lastName, lastName);

    newNode->grade = grade;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

void printList(Stud *start){
    Stud *temp = start;
    if(temp == NULL){
        printf("The list has no nodes yet.\n");
        return;
    }

    assert(temp != NULL);

    printf("\n");
    while(temp != NULL){
        printf("%s %s %d\n", temp->firstName, temp->lastName, temp->grade);
        temp = temp->next;
    }
}

void openFile(FILE **fileName){
    char input[100];
    int c;

    while(1){
        printf("Input the students data file name: ");
        scanf("%99s", input);
        while ((c = getchar()) != '\n' && c != EOF);
        *fileName = fopen(input, "r");
        if(*fileName == NULL){
            printf("File can't be opened.\n");
            continue;
        }
        break;
    }
}

int printMenu(void){
    printf("\nPress 0 to create the list of students from the data file\n");
    printf("Press 1 to print the list of students\n");
    printf("Press 2 to insert new student to the list\n");
    printf("Press 3 to free the memory of the list\n");
    printf("Press 4 to exit the program\n");
    int option = Validation('m', 4);
    return option;
}

int Validation(char mode, int max){
    assert(max >= 0);

    char line[256], enter;
    int isInt, number;

    fgets(line, sizeof line, stdin);
    isInt = sscanf(line, "%d%c", &number, &enter);
    if(isInt && enter == '\n' && number >= 0 && number <= max){
        return number;
    }
    if(mode == 'm'){
        printf("Please input a valid option.\n");
        printMenu();
    }else{
        printf("Wrong index input. Exceeds range of list.\n");
        return -1;
    }
}