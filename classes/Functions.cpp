#include "../includes.h"

#include "functions/Zhegalkin.cpp"
#include "functions/SDNF.cpp"
#include "functions/SKNF.cpp"

#pragma once

class Functions
{
public:
    static void zhegalkin(std::string template_variable, std::string values)
    {
        Zhegalkin* zhegalkin = new Zhegalkin(template_variable, values);
        delete zhegalkin;
    }
    
    static void sdnf(std::string template_variable, std::string values)
    {
        SDNF* sdnf = new SDNF(template_variable, values);
        delete sdnf;
    }
    
    static void sknf(std::string template_variable, std::string values)
    {
        SKNF* sknf = new SKNF(template_variable, values);
        delete sknf;
    }
};
