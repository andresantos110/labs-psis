#ifndef FUNCS_H
#define FUNCS_H

#include<stdio.h>

int f1();

int f2();

int f3(int);

typedef struct message_type{
    int funct_type; //type = 0 no arg; type = 1 arg.
    char f_name[100];
    int arg;

} message_type;

#endif // FUNCS_H
