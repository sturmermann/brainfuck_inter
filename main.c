#include <stdio.h>
#include <stdlib.h>

#define size 1000
#define ERR "\n\nAbnormal situation. Abort\n\n"

typedef unsigned char ui8;

ui8 err = 0;
ui8 *shield;
int num = 0;

void treatment(char),
        ErrRaise(), changeValue(ui8 *, int),
        output(ui8 *), changePos(int *, int),
        input(ui8 *), execStr(char *, int);


void ErrRaise() {
    printf(ERR);
    err = 1;
}

void changePos(int *numPoint, int val) {
    int num = *numPoint;
    if (num == 0 && val == -1) {
        ErrRaise();
    } else if (num == size - 1 && val == 1) {
        ErrRaise();
    } else {
        num += val;
    }
    *numPoint = num;
}

void changeValue(ui8 *cell, int val) {
    if (*cell == 0 && val == -1) {
        *cell = 255;
    } else if (*cell == 255 && val == 1) {
        *cell = 0;
    } else {
        *cell += val;
    }
}

void output(ui8 *cell) {
    printf("%c ", (*cell));
}

void input(ui8 *cell) {
    (*cell) = getchar();
}

void loop(){
    char * s = malloc(1);
    int sz = 1;
    int cur = 1;
    int c = 0;
    while ((c = getchar()) != EOF && !err){
        s[sz-1] = c;
        if (s[sz-1] == ']'){
            cur--;
        }
        if (s[sz-1] == '['){
            cur++;
        }
        if (cur < 0){
            ErrRaise();
            return;
        }
        if (cur == 0){
            break;
        }
        s = realloc(s, sz+1);
        sz = sz+1;
    }
    s[sz-1] = '\0';
    while (shield[num] != 0){
        execStr(s, sz);
    }
}

void treatment(char c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\0':
        case '\n':
            break;
        case '+':
            changeValue(&shield[num], +1);
            break;
        case '-':
            changeValue(&shield[num], -1);
            break;
        case ',':
            input(&shield[num]);
            break;
        case '.':
            output(&shield[num]);
            break;
        case '>':
            changePos(&num, +1);
            break;
        case '<':
            changePos(&num, -1);
            break;
        case '[':
            loop();
            break;
        case ']': // the architecture does not allow this item in this function
        default:
            ErrRaise();
    }
}

void execStr(char *s, int sz) {
    for (int i = 0; i < sz; i++) {
        treatment(s[i]);
    }
}

int main() {
    shield = malloc(size);
    for (int i = 0; i < size; i++) {
        *(shield + i) = 0;
    }

    int c;
    while ((c = getchar()) != EOF && !err) {
        char *cr = malloc(2);
        cr[0] = c;
        cr[1] = '\0';
        execStr(cr, 2);
        if (err) break;
    }

    free(shield);
    shield = NULL;
    return 0;
}