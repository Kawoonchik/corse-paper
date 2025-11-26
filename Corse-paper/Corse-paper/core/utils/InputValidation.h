#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H

#include <string>

class InputValidation {
public:
    std::string GetStringInput(const std::string& prompt);
    int         GetIntInput(const std::string& prompt);
    double      GetDoubleInput(const std::string& prompt);
};

#endif