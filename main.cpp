//
//  main.cpp
//  hash-prog
//
//  Created by webitp on 22/09/2021.
//  Copyright © 2021 webitp. All rights reserved.
//

#include <iostream>
#include <openssl/sha.h>


int main(int argc, const char * argv[]) {
//    SHA_CTX context;
//    SHA1_Init(&context);
    
    unsigned char input[512];
    unsigned char result[SHA_DIGEST_LENGTH];
    
    std::cin >> input;
    
//    SHA1_Update(&context, input, sizeof(input));
//    SHA1_Final(result, &context);
    SHA1(input, sizeof(input), result);
    
    std::cout << result;
    
    return 0;
}
