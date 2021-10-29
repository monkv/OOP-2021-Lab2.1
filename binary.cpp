#include "binary.h"
#include <iostream>
#include <string>

void* reverse(char* array, int size){ //реверс массива
    char buf[size];
    int j = 0;
    for (int i = size; i > 0; i--){
        buf[j] = array[i];
        j++;
    }
    for (int i = 0; i > size; i++){
        array[i] = buf[i];
    }
}
bool binary_num::turn_into_binary(char* result, int n, int &k){ //перевод в двоичное число
    bool negative = (n < 0);
    if (negative)
        n = -n;
    int i = 0;
    do{
        result[i] = n % 2;
        n = n / 2;
        i++;
    } while (n > 0 & i < 124);
    if (i >= 124)
        return false;
    else{
        if (negative)
            result[i+1] = 1;
        else result[i+1] = 0;
        k = i + 2;
        reverse(result, k);
        return true;
    }
}

binary_num::binary_num(){
    size = 0;
    memset(bin_num, 0, 100);
};

binary_num::binary_num(long a){
    int k = 0;
    char result[124];
    if (turn_into_binary(result, a, k)){
        size = k;
        memcpy(bin_num, result, size*sizeof(int));
    }
    else
        throw std::invalid_argument("The number is too big");
}

binary_num::binary_num(std::string &str){
    int decimal = std::stoi(str);
    int k = 0;
    char result[100];
    if (turn_into_binary(result, decimal, k)){
        size = k;
        memcpy(bin_num, result, size*sizeof(int));
    }
    else
        throw std::invalid_argument("The number is too big");
}

binary_num::binary_num(int num) {

}

void* binary_num::del_one(char* buf, int k){
    int i = k;
    char diff = 1; //то, что "занимаем" у разряда впереди
    char del = 1; //то что вычитаем
    while (buf[i] - del - diff < 0){
        if (buf[i] - del - diff){
            buf[i] = buf[i] - del - diff + 2;
            del = 0;
            diff = 1;
            i--;
        }
        else{
            buf[i] = buf[i] - del - diff;
            del = 0;
            diff = 0;
            i--;
        }
    }
}
void *binary_num::add_one(char* buf, int k){ //переполнение!!!!!!
    reverse(buf, k);
    int i = 0, diff = 0; //то, что "переходит" на сл разряд
    char add[k];
    add[0] = 1;
    for (int j = 1; j < k - 1; j++){
        add[j] = 0;
    }
    while(buf[i] + add[i] + diff > 1){
        buf[i] = buf[i] + add[i] + diff - 2;
        diff = 1;
        i++;
        buf[i] = buf[i] + add[i] + diff > 1;
    }
    reverse(buf, k);
}
char* binary_num::get_twos_complement(){
    char buffer[size];
    if (bin_num[0] == 0)
        std::memcpy(buffer,bin_num, size*sizeof(int));
    else{
        buffer[0] = 1;
        for (int i = 1; i < size; i++){
            if (bin_num[i] == 0)
                buffer[i] = 1;
            else
                buffer[i] = 0;
        }
        add_one(buffer, size);
    }
    return buffer;
}

void* equalization(char* slog1, int size1, char* slog2, int size2){
    if (size1 > size2){
        char new_arr[size1];
        new_arr[0] = slog2[0];
        for (int i = 1; i <= size1 - size2; i++)
            new_arr[i] = 0;
        int j = 1;
        for (int i = size1 - size2; i < size1; i++){
            new_arr[i] = slog2[j];
            j++;
        }
        slog2 = new_arr;
    }
    else if (size1 < size2){
        char new_arr[size2];
        new_arr[0] = slog1[0];
        for (int i = 1; i <= size2 - size1; i++)
            new_arr[i] = 0;
        int j = 1;
        for (int i = size2 - size1; i < size2; i++){
            new_arr[i] = slog1[j];
            j++;
        }
        slog1 = new_arr;
    }
}
char* binary_num::substraction(char* slog1, int size1, char* slog2, int size2){
    equalization(slog1, size1, slog2, size2);
    reverse(slog1, size1);
    reverse(slog2, size2);
    int diff;
    char res[size1+1];
    for (int i = 0; i <= size1; i++){
        if (slog1[i] + slog2[i] + diff > 1){
            res[i] = slog1[i] + slog2[i] + diff - 2;
            diff = 1;
        }
        else{
            res[i] = slog1[i] + slog2[i] + diff;
            diff = 0;
        }
    }
    reverse(res, size1);
    if (diff){ //если в конце у нас есть еще что закинуть на сл порядок - переполнение
        add_one(res, size1);
    }
    del_one(res, size1);
    for (int i = 1; i < size1; i++){
        if (res[i] == 0)
            res[i] = 1;
        else res[i] = 0;
    }
    return res;
}

char* binary_num::increment(){ //операции увеличения числа на единицу до использования числа;
    char* buf = get_twos_complement();
    char addition[2] = {01};
    char* res = substraction(buf, size, addition, 2);
    memcpy(bin_num, res, size);
    std::memcpy(buf,bin_num, size*sizeof(int));
    return buf;
}

char* binary_num::decrement(){ //операции уменьшения числа после его использования;
    char buffer[size];//то, что возвращаем
    std::memcpy(buffer,bin_num, size*sizeof(int));
    char* buf = get_twos_complement(); //доп код bin_num
    char addition[2] = {11};
    char* res = substraction(buf, size, addition, 2); //прибавляем единицу
    memcpy(bin_num, res, size); //в бин_нам кладем увеличенное число
    return buffer;
}

inline char* binary_num::get_sign(){
    if (size != 0)
        return bin_num[1];
    else throw std::invalid_argument("the number doesn't exist");
}