#include "../includes.h"

#pragma once

class Output
{
public:
    static void inner(std::vector<std::string> output)
    {
        for (int i = 0; i < output.size() - 1; ++i)
            std::cout << output[i];
        std::cout << std::endl;
    }
    
    static void head(std::string template_variable, int variables_count)
    {
        std::cout << "f(";
        for (int i = 0; i < variables_count; ++i)
        {
            std::cout << template_variable + std::to_string(i + 1);
            if (i != variables_count - 1)
                std::cout << ", ";
        }
        std::cout << ") = ";
    }
};
