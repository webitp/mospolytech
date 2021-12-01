#include "../../includes.h"
#include "../TrueTable.cpp"
#include "../Output.cpp"

class Threeangel
{
public:
    std::vector<std::vector<int>> threeangel;
    
    Threeangel(std::string values)
    {
        for (int i = 0; i < values.size(); ++i)
            arr_values.push_back(values[i] - '0');
        
        threeangel.push_back(arr_values);
        
        while (threeangel[threeangel.size() - 1].size() > 0)
        {
            current_values = {};
            for (int i = 0; i < arr_values.size() - 1; ++i)
                current_values.push_back((arr_values[i] + arr_values[i + 1]) % 2);
            
            threeangel.push_back(current_values);
            arr_values = current_values;
        }
    }
private:
    std::vector<int> arr_values;
    std::vector<int> current_values;
};

class Zhegalkin
{
public:
    Zhegalkin(std::string template_variable, std::string values)
    {
        Threeangel threeangel = Threeangel(values);
        int variables_count = (int)log2(values.length());
        TrueTable table = TrueTable(variables_count, template_variable);
        
        std::vector<std::vector<std::string>> variables;
        std::vector<std::string> vars;
        for (std::vector<int> row : table.table)
        {
            vars = {};
            for (int i = 0; i < (int)row.size(); ++i)
                if (row[i] > 0)
                    vars.push_back(template_variable + std::to_string(i + 1));
            variables.push_back(vars);
        }
        
        Output::head(template_variable, variables_count);
        
        std::vector<std::string> output;
        for (int i = 0; i < table.table.size(); ++i)
        {
            if (threeangel.threeangel[i][0] > 0)
            {
                if (i == 0)
                {
                    output.push_back("1");
                    output.push_back(" + ");
                }
                else
                {
                    for (std::string variable : variables[i])
                        output.push_back(variable);
                    output.push_back(" + ");
                }
            }
        }
        
        Output::inner(output);
    }
};
