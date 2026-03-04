#include "Validate.h"
#include <iostream>
#include <limits>

int getValidatedInt(int lower, int upper,
    const std::string& prompt,
    const std::string& errorMsg)
{
    while (true)
    {
        std::cout << prompt;
        int value;
        if (!(std::cin >> value))
        {
            // Non-integer input: clear and discard the rest of the line
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << errorMsg << std::endl;
            continue;
        }

        // Remove any remaining characters on the same line (e.g., stray spaces)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value < lower || value > upper)
        {
            std::cout << errorMsg << std::endl;
            continue;
        }

        return value;
    }
}