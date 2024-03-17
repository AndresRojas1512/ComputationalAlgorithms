#include "ui.h"

void menu(void)
{
    std::cout << std::endl;
    puts("0. Интерполяция.");
    puts("1. Сравнение интерполяций.");
    puts("2. Решение уравнения.");
    puts("3. Решение системы.");
    puts("4. Выход.");
}

int input_choice(int *choice)
{
    puts("--------------------------------------");
    printf("Введите операцию: ");
    int result = scanf("%d", choice);
    clean_buffer();
    if (!result)
        return ERROR_CHOICE_READ_UB;
    if (*choice > 9 || *choice < 0)
        return ERROR_CHOICE_READ_RANGE;
    return EXIT_SUCCESS;
}

void clean_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}