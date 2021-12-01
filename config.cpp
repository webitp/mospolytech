//
//  config.cpp
//  bmp_image
//
//  Created by webitp on 29/09/2021.
//  Copyright © 2021 webitp. All rights reserved.
//

#include "modules.h"

class Config {
public:
    std::vector<int> replaced_bytes;
    
    Config(const std::string path) {
        this->_read_replaced_bytes(path);
    }
    
private:
    void _read_replaced_bytes(const std::string path) {
        std::ifstream file(path);
        if (file) {
            std::string line;
            while (getline(file, line)) {
                std::istringstream linein{ line };
                std::string key, value;
                
                while(getline(linein, value, ',') && !value.empty())
                    replaced_bytes.push_back(std::stoi(value));
            }
        }
    }
};
