#pragma once
#ifndef VALIDATE_H
#define VALIDATE_H

#include <string>

// Function prototype
int getValidatedInt(int lower, int upper,
    const std::string& prompt,
    const std::string& errorMsg);

#endif