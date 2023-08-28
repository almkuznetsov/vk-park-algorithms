/*
Инвертируйте значение бита в числе N по его номеру K.
Формат входных данных. Число N, номер бита K.
Формат выходных данных. Число с инвертированным битом в десятичном виде.
*/
#include <iostream>

unsigned int invert_byte(unsigned int n, unsigned int k) {
   unsigned int shift = 0x1 << k;
    n = n ^ shift;
    return n;
}

int main() {
    unsigned int n = 0;
    unsigned int k = 0;
    std::cin >> n >> k;
    n = invert_byte(n, k);
    std::cout << n;
    return 0;
}