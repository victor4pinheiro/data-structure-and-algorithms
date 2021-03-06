#include <stdio.h>
#define MAX 50
#define ERROR -1

typedef int KEYTYPE;

typedef struct {
    KEYTYPE key;
} REGISTER;

typedef struct {
    REGISTER reg;
    int next;
} ELEMENT;

typedef struct {
    ELEMENT A[MAX];
    int initial;
    int available;
} LIST;

void initList(LIST* l) {
    int i;
    for (i = 0; i < MAX - 1; i++)
        l->A[i].next = i + 1;

    l->A[MAX-1].next = ERROR;
    l->initial = ERROR;
    l->available = 0;
}

int size(LIST* l) {
    int i = l->initial; // index of first valid element
    int number = 0; // count how many elements the list has it

    while (i != ERROR) {
        number++;
        i = l->A[i].next;
    }
    
    return number;
}

void showList(LIST* l) {
    int i = l->initial;
    printf("List: \" ");
    
    while (i != ERROR) {
        printf("%i", l->A[i].reg.key);
        i = l->A[i].next;
    }

    printf("\"\n");
}

int searchOrdeneredList(LIST* l, KEYTYPE ch) {
    int i = l->initial;
    
    while (i != ERROR && l->A[i].reg.key < ch)
        i = l->A[i].next;

    if (i != ERROR && l->A[i].reg.key == ch)
        return i;
    else return ERROR;
}

int getNode(LIST* l) {
    int result = l->available;
    if (l->available != ERROR)
        l->available = l->A[l->available].next;
    return result;
}

int insertElemList(LIST* l, REGISTER reg) {
    if (l->available == ERROR) return -1;
    int previous = ERROR;
    int i = l->initial;
    KEYTYPE ch = reg.key;

    while ((i != ERROR) && (l->A[i].reg.key < ch)) {
        previous = i;
        i = l->A[i].next;
    }

    if (i != ERROR && l->A[i].reg.key == ch) return -1;
    
    i = getNo(l);
    l->A[i].reg = reg;

    if (previous == ERROR) {
        l->A[i].next = l->initial;
        l->initial = i;
    } else {
        l->A[i].next = l->A[previous].next;
        l->A[previous].next = i;
    }

    return 0;
}

int deleteElemList(LIST* l, KEYTYPE ch) {
    int previous = ERROR;
    int i = l->initial;
    while ((i != ERROR) && (l->A[i].reg.key < ch)) {
        previous = i;
        i = l->A[i].next;
    }

    if (i == ERROR || l->A[i].reg.key != ch) return -1;
    if (previous == ERROR) l->initial = l->A[i].next;
    else l->A[previous].next = l->A[i].next;

    returnNode(l, i);
    return 0;
}

void returnNode(LIST* l, int j) {
    l->A[j].next = l->available;
    l->available = j;
}

void restartList(LIST* l) {
    initList(l);
}
