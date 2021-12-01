#include "../includes.h"

#pragma once

class TrueTable
{
public:
    std::vector<std::vector<int>> table;
    
    TrueTable(int n, const std::string template_variable)
    {
        _template_variable = template_variable;
        
        s_current_values.resize(n, '0');
        const std::string result_string(n, '1');
        std::vector<int> tmp;
        
        while (s_current_values != result_string) {
            for (int i = 0; i < s_current_values.length(); ++i)
                tmp.push_back(s_current_values[i] - '0');
            table.push_back(tmp);
            tmp = {};
            s_current_values = bin_sum(s_current_values, "1");
        }
        
        for (int i = 0; i < s_current_values.length(); ++i)
            tmp.push_back(result_string[i] - '0');
        table.push_back(tmp);
    }
private:
    std::string s_current_values;
    std::string _template_variable;
    
    std::string bin_sum(const std::string s1, const std::string s2) {
        int len1 = (int)s1.size();
        int len2 = (int)s2.size();

        std::string ls1 = len1<len2 ? s1 : s2;
        std::string ls2 = len1<len2 ? s2 : s1;
        for (int i = (int)ls1.size(); i < ls2.size(); ++i) ls1 = '0' + ls1;

        std::string result;
        int carry = 0;
        for (int i = (int)(ls2.size() - 1); i >= 0; --i) {
        int bit1 = ls1.at(i) - '0';
        int bit2 = ls2.at(i) - '0';
        char sum = (bit1 ^ bit2 ^ carry) + '0';
            result = sum + result;
            carry = (bit1&carry)|(bit2&carry)|(bit1&bit2);
        }
        if (carry) result = '1' + result;
        return result;
    }
};
