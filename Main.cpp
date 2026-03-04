/*
Adam Mashhadani
3/1/2026
Project: Oops! Shall We Try Again Lab
*/

#include <iostream>
#include "validate.h"

int main()
{
    int result = getValidatedInt(
        0, 100,
        "Please enter a value (0-100):",
        "Your value is invalid"
    );

    std::cout << "The value chosen by the user is "
        << result << std::endl;

    return 0;
}