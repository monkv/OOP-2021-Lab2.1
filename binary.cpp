#include "binary.h"
#include <iostream>
#include <string>

binary_num::binary_num(char* buf, int length) {
    memcpy(bin_num, buf, 101);
    int i = length;
    while (buf[i] != 1){
        i--;
    }
    size = i;
}
binary_num::binary_num(long n){
    bool negative = (n < 0);
    if (negative)
        n = -n;
    int i = 0;
    do{
        bin_num[i] = n % 2;
        n = n / 2;
        i++;
    } while (n > 0 & i < 100);
    if (i >= 100)
        throw std::invalid_argument("The number is too big");
    else{
        for (int j = i; size < 100; size++){
            bin_num[j] = 0;
        }
        if (negative){
            bin_num[100] = 1;
        }
        else bin_num[100] = 0;
        size = i + 2;
    }
}

binary_num::binary_num(std::string &str){
    long decimal = std::stoi(str);
    memcpy(bin_num, binary_num(decimal).bin_num, 101);
    size = binary_num(decimal).size;
}

binary_num::binary_num(binary_num &obj){
    size = obj.size;
    memcpy(bin_num, obj.bin_num, 101);
};


void* add_one(char* buf){
    int diff = 0, add = 1, i = 0;
    while (buf[i] + add + diff > 1){
        buf[i] = buf[i] + add + diff - 2;
        diff = 1;
        add = 0;
        i++;
    }
    if (i == 0)
        buf[i] = buf[i] + add + diff;
    return buf;
}

char* binary_num::get_twos_complement(char* buffer){
    buffer = new char[100];
    if (bin_num[100] == 0)
        memcpy(buffer,bin_num, size*sizeof(int));
    else{
        buffer[100] = 1;
        for (int i = 0; i < 100; i++){
            if (bin_num[i] == 0)
                buffer[i] = 1;
            else
                buffer[i] = 0;
        }
        add_one(buffer);
    }
    return buffer;
}
char* binary_num::get_2compl(){
    return get_twos_complement(bin_num);
}
binary_num subtraction(binary_num &obj1, binary_num &obj2){
    int diff = 0; //доп в десяток
    char res[101];
    char* summand1 = obj1.get_twos_complement(summand1);
    char* summand2 = obj2.get_twos_complement(summand2);
    for (int i = 0; i <= 100; i++){
        if (summand1[i] + summand2[i] + diff > 1){
            res[i] = summand1[i] + summand2[i] + diff - 2;
            diff = 1;
        }
        else{
            res[i] = summand1[i] + summand2[i] + diff;
            diff = 0;
        }
    }
    if (res[100] == 1){
        for (int i = 0; i < 100; i++){
            if (res[i] == 0)
                res[i] = 1;
            else
                res[i] = 0;
        }
        add_one(res);
    }
    int length = (obj1.size > obj2.size) ? obj1.size : obj2.size;
    binary_num obj_res (res, length);
    return obj_res;
}

char binary_num::get_sign(){
    if (size != 0)
        return bin_num[100];
    else throw std::invalid_argument("the number doesn't exist");
}


binary_num& binary_num::increment(){ //операции увеличения числа на единицу до использования числа;
    int plus = 1;
    binary_num obj (plus);
    *this = subtraction(*this, obj);
    return *this;
}

binary_num binary_num::decrement(){ //операции уменьшения числа после его использования;
    binary_num copy (*this);
    int minus = -1;
    binary_num obj (minus);
    *this = subtraction(*this, obj);
    return copy;
}

std::ostream& operator<< (std::ostream &out, const binary_num &obj){
    std::cout << obj.bin_num[100];
    for (int i = obj.size; i > 0; i--){
        std::cout << obj.bin_num[i];
    }
    return out;
}
std::istream& operator>> (std::istream& in, binary_num &obj) {
    std::string input;
    in >> input;
    obj = binary_num(input);
    return in;
}
binary_num& binary_num::operator= (const binary_num& obj){
    memcpy(this->bin_num, obj.bin_num, 101);
    this->size = obj.size;
    return *this;
}

binary_num& binary_num::operator++ (){
    int plus = 1;
    binary_num obj (plus);
    *this = subtraction(*this, obj);
    return *this;
}

const binary_num binary_num::operator-- (int){ //постфиксный декремент
    binary_num copy (*this);
    int minus = -1;
    binary_num obj (minus);
    *this = subtraction(*this, obj);
    return copy;
}

