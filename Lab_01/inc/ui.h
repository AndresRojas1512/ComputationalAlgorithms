#ifndef UI_H
#define UI_H

#include <iostream>

#define ERROR_CHOICE_READ_UB 10
#define ERROR_CHOICE_READ_RANGE 11

void menu();
void clean_buffer();
int input_choice(int *choice);

#endif