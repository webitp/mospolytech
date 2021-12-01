#include "../includes.h"

#pragma once

class Input
{
public:
    static void get(std::string &template_variable, std::string &values, std::string &action)
    {
        std::cout << "Input function ID: " << std::endl;
        std::cout << "1. Zhegalkin" << std::endl;
        std::cout << "2. SDNF" << std::endl;
        std::cout << "3. SKNF" << std::endl;
        std::cin >> action;
        
        std::cout << "Input variable name: ";
        std::cin >> template_variable;
        
        std::cout << "Input function values: ";
        std::cin >> values;
    }
};
