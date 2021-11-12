#pragma once

#include <iostream>
#include <vector>

class binary_num{
private:
    int size = 0;
    char bin_num[101];
public:
    binary_num() = default;
    explicit binary_num(long num);
    explicit binary_num(std::string &str);
    explicit binary_num(char* buf, int length);
    binary_num(binary_num &obj);

    char* get_twos_complement(char* buf); //+
    char* get_2compl();
    friend binary_num subtraction(binary_num &obj1, binary_num &obj2);
    binary_num &increment();
    binary_num decrement();
    char get_sign();

    friend std::ostream& operator<< (std::ostream &out, const binary_num &obj);
    friend std::istream& operator>> (std::istream& in, binary_num& obj);

    binary_num& operator= (const binary_num& obj);
    binary_num& operator++();
    const binary_num operator-- (int);
};

void* add_one(char* buf);