#include "../../includes.h"
#include "../TrueTable.cpp"
#include "../Output.cpp"

class SDNF
{
public:
    SDNF(std::string template_variable, std::string values)
    {
        int variables_count = (int)log2(values.length());
        TrueTable table = TrueTable(variables_count, template_variable);
        
        std::vector<std::vector<std::string>> variables;
        std::vector<std::string> vars;
        std::vector<int> row;
        std::string var;
        for (int row_index = 0; row_index < (int)table.table.size(); ++row_index)
        {
            row = table.table[row_index];
            vars = {};
            if (values[row_index] == '1') {
                for (int i = 0; i < (int)row.size(); ++i)
                {
                    var = template_variable + std::to_string(i + 1);
                    if (row[i] == 0)
                        var = '!' + var;
                    vars.push_back(var);
                }
                variables.push_back(vars);
            }
        }
        
        Output::head(template_variable, variables_count);
        
        std::vector<std::string> output;
        std::string out;
        for (int i = 0; i < variables.size(); ++i)
        {
            for (std::string var : variables[i])
                output.push_back(var);
            output.push_back(" + ");
        }
        
        Output::inner(output);
    }
};
