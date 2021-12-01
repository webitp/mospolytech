//
//  main.cpp
//  SHA1
//
//  Created by webitp on 10.11.2021.
//

#include <iostream>
#include <string>
#include <vector>
#include <bitset>

//class SHA1
//{
//public:
//    SHA1(std::string message)
//    {
//        for (std::size_t i = 0; i < message.size(); ++i)
//        {
//            std::cout << std::bitset<8>(message.c_str()[i]) << std::endl;
//            _message.push_back(std::bitset<8>(message.c_str()[i]));
//        }
//
//        this->additional_message();
//        /*
//        _message = message;
//        std::cout << sizeof(_message) << std::endl;
//        additional_message();
//        std::cout << sizeof(_message) << std::endl;
//        std::cout << _message << std::endl;
//         */
//    }
//private:
//    std::vector<std::bitset<8>> _message;
//
//    void additional_message()
//    {
//        unsigned int l = sizeof(_message);
//        unsigned int k = 448 - (l + 1);
//
//        std::bitset<8> temp_batch;
//        temp_batch[7] = 1;
//        _message.push_back(temp_batch);
//        for (int i = 0; i < ((k + 1) / 8) - 1; ++i)
//            _message.push_back(std::bitset<8>(0));
//
//        std::bitset<64> bitset_of_size(l);
//
//        for (int i = 63; i >= 0; i -= 8)
//        {
//            temp_batch.reset();
//            for (int j = 8; j > 0; --j)
//                temp_batch[j] = bitset_of_size[i - j];
//            _message.push_back(temp_batch);
//        }
//
//
//    }
//};
//
//
//int main(int argc, const char * argv[])
//{
//    std::string message;
//    std::cin >> message;
//
//    new SHA1(message);
//
//    return 0;
//}

bool fullAdder(bool b1, bool b2, bool& carry)
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}

std::bitset<32> bitsetAdd(std::bitset<32>& x, std::bitset<32>& y)
{
    bool carry = false;
    std::bitset<32> ans;
    for (int i = 0; i < 32; i++) {
        ans[i] = fullAdder(x[i], y[i], carry);
    }
    return ans;
}

int main()
{
    std::string msg;
    std::vector<std::bitset<8>> message;

    std::cin >> msg;

    for (char symbol : msg)
        message.push_back(std::bitset<8>(symbol));

    std::cout << sizeof(message)  << std::endl;

    unsigned int l = sizeof(message);
    unsigned int k = 448 - (l + 1);

    std::bitset<8> temp_batch;
    temp_batch[7] = 1;
    message.push_back(temp_batch);
    for (int i = 0; i < ((k + 1) / 8) - 1; ++i)
        message.push_back(std::bitset<8>(0));

    std::bitset<64> bitset_of_size(l);

    for (int i = 63; i >= 0; i -= 8)
    {
        temp_batch.reset();
        for (int j = 8; j > 0; --j)
            temp_batch[j] = bitset_of_size[i - j];
        message.push_back(temp_batch);
    }

    std::vector<std::bitset<32>> batched_message;
    std::bitset<32> temp_batched_message;
    for (int i = 0; i < message.size(); i += 4)
    {
        for (int step = 0; step < 4; ++step) {
            for (int j = 0; j < 8; ++j) {
                temp_batched_message[j * step] = message[i + step][j];
            }
        }
        batched_message.push_back(temp_batched_message);
    }

    for (int i = 16; i < 80; ++i)
    {
        batched_message.push_back((batched_message[i - 3] ^ batched_message[i - 8] ^ batched_message[i - 14] ^ batched_message[i - 16]) << 1);
    }

    std::bitset<32> h0(0x67452301);
    std::bitset<32> h1(0xEFCDAB89);
    std::bitset<32> h2(0x98BADCFE);
    std::bitset<32> h3(0x10325476);
    std::bitset<32> h4(0xC3D2E1F0);

    std::bitset<32> a = h0;
    std::bitset<32> b = h1;
    std::bitset<32> c = h2;
    std::bitset<32> d = h3;
    std::bitset<32> e = h4;

    std::bitset<32> function;
    std::bitset<32> constant;
    std::bitset<32> temp;
    for (int i = 0; i < 80; ++i)
    {
        if (0 <= i && i <= 19)
        {
            function = (b & c) | (b.flip() & d);
            constant = std::bitset<32>(0x5A827999);
        }
        else if (20 <= i && i <= 39)
        {
            function = b ^ c ^ d;
            constant = std::bitset<32>(0x6ED9EBA1);
        }
        else if (40 <= i && i <= 59)
        {
            function = (b & c) | (b & d) | (c & d);
            constant = std::bitset<32>(0x8F1BBCDC);
        }
        else if (60 <= i && i <= 79)
        {
            function = b ^ c ^ d;
            constant = std::bitset<32>(0xCA62C1D6);
        }

        std::bitset<32> rotated_a = a << 5;
        temp = bitsetAdd(rotated_a, function);
        temp = bitsetAdd(temp, e);
        temp = bitsetAdd(temp, constant);
        temp = bitsetAdd(temp, batched_message[i]);

        e = d;
        d = c;
        c = b << 30;
        b = a;
        a = temp;
    }

    std::string result;

    h0 = bitsetAdd(h0, a);
    h1 = bitsetAdd(h1, b);
    h2 = bitsetAdd(h2, c);
    h3 = bitsetAdd(h3, d);
    h4 = bitsetAdd(h4, e);


    result += h0.to_string() + " ";
    result += h1.to_string() + " ";
    result += h2.to_string() + " ";
    result += h3.to_string() + " ";
    result += h4.to_string();

    std::bitset<4> char_batch;
    for (int j = 0; j < 8; ++j)
    {
        char_batch.reset();
        for (int i = 0; i < 4; ++i)
            char_batch[i] = h0[8 * j + i];

        std::cout << static_cast<char>(std::bitset<4>(char_batch).to_ulong() + 64);
    }

    return 0;
}
