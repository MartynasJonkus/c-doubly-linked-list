#ifndef PROCEDURINIO_PROGRAMAVIMO_PRATYBOS_4_FUNCTIONS_H
#define PROCEDURINIO_PROGRAMAVIMO_PRATYBOS_4_FUNCTIONS_H

struct Stud{
    char *firstName;
    char *lastName;
    int grade;

    struct Stud *prev;
    struct Stud *next;
};
typedef struct Stud Stud;

void openFile(FILE **fileName);

int printMenu(void);
int Validation(char mode, int max);

Stud *getNewNode(char firstName[], char lastName[], int grade);
void createList(FILE *inputFile, Stud **start);
void printList(Stud *start);
void insertToList(Stud **start);
void freeList(Stud **start);

#endif
