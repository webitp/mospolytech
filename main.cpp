#include "includes.h"

#include "classes/Input.cpp"
#include "classes/Functions.cpp"

int main()
{
    std::string template_variable;
    std::string values;
    std::string action;

    Input::get(template_variable, values, action);
    
    if (action == "1")
        Functions::zhegalkin(template_variable, values);
    if (action == "2")
        Functions::sdnf(template_variable, values);
    if (action == "3")
        Functions::sknf(template_variable, values);

    return 0;
}
