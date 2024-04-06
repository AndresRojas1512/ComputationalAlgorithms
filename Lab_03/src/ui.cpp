#include "ui.h"

void menu(void)
{
    std::cout << std::endl;
    puts("1.1 Spline Interpolation.");
    puts("2.1 x = x0 ; x = xN when F(x0)'' = 0 and F(xN)'' = 0");
    puts("2.2 x = x0 Fi''(x0) = P''(x0) ; x = xN Fi''(xN) = 0");
    puts("2.3 x = x0 Fi''(x0) = P''(x0) ; x = xN Fi''(xN) = P''(xN)");
    puts("3.1 Compare Spline and Newton (3 grade) interpolation.");
}

int input_choice(int &choice)
{
    puts("--------------------------------------");
    printf("Введите операцию: ");
    std::cin >> choice;
    if (choice == 11 || choice == 21 || choice == 22 || choice == 23 || choice == 31 || choice == 4)
        return EXIT_SUCCESS;
    else
        return ERROR_CHOICE_READ_RANGE;
    return EXIT_SUCCESS;
}

void clean_buffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}