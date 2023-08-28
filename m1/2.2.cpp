/*
Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают, 
а на интервале [m, n-1] строго убывают. Найти m за O(log m). 
Требования:  Время работы O(log m). 
Внимание! В этой задаче сначала нужно определить диапазон для бинарного поиска 
размером порядка m с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

int find_m(int n, int array[])
{
    int i = 1;
    while ((array[i - 1] < array[i]) && i != n ) //экоспоненциальный поиск
    {
        i *= 2;
        if (i > n) 
        {
            i = n;
        }
    }
    int m_low = i / 2;
    int m_high = i - 1;
    int m_mid = 0;
    while (m_high - m_low >= 1) //бинарный поиск
    {
        m_mid = (m_high + m_low) / 2;
        if (array[m_mid] < array[m_mid + 1])
        {
            m_low = m_mid + 1;
        }
        else 
        {
            m_high = m_mid;
        }
    }
    return m_high;
}

int run(std::istream& input, std::ostream& output)
{
   int n;
   input >> n;
   int array[n];
   for (int i = 0; i < n; i++) 
   {
    input >> array[i];
    }
    
    output << find_m(n, array);
    return 0;
}

void runtest()
{
    {
    std::stringstream input;
    std::stringstream output;
    input << "5\n";
    input << "1 2 3 4 1\n";
    run(input, output);
    assert(output.str() == "3");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "10\n";
    input << "1 2 3 4 5 6 7 6 5 1\n";
    run(input, output);
    assert(output.str() == "6");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "6\n";
    input << "0 8 2544112 8 5 3\n";
    run(input, output);
    assert(output.str() == "2");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "5\n";
    input << "1 5 4 3 2\n";
    run(input, output);
    assert(output.str() == "1");
    }
        {
    std::stringstream input;
    std::stringstream output;
    input << "5\n";
    input << "1 2 3 4 2\n";
    run(input, output);
    assert(output.str() == "3");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "5\n";
    input << "1 2 3 2 1\n";
    run(input, output);
    assert(output.str() == "2");
    }
}

int main()
{
    runtest();
    run(std::cin, std::cout);
    return 0;
}