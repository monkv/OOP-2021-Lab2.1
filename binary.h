#pragma once

#include <iostream>
#include <vector>

class binary_num{
private:
    int size;
    char* bin_num[100];
public:
    binary_num();
    binary_num(long num);
    binary_num(std::string &str);
    binary_num(int number); //???????
    bool turn_into_binary(char* result, int a, int &k);

    void* add_one(char* buf, int k);
    void* del_one(char* buf, int k);

    char* get_sign();
    char* get_twos_complement(); //+
    char* substraction(char *slog1, int size1, char *slog2, int size2); //???
    char* increment();
    char* decrement();
};