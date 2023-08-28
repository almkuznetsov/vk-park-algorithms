/*
Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. 
Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. 
Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO
Реализовать дек с динамическим зацикленным буфером.
Требования: Дек должен быть реализован в виде класса.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

class Deck
{
private:
    int head;
    int tail;
    int size;
    int capacity_;
    int *arr;
    void grow()
    {
        int new_capacity = capacity_ * 2;
        int *new_arr;
        new_arr = new int[new_capacity];
        for (int i = 0; i < size; i++)
        {
            new_arr[i] = arr[(head + i) % capacity_];
        }
        delete[] arr;
        capacity_ = new_capacity;
        arr = new_arr;
        head = 0;
        tail = size;
    }
public:
    Deck(int capacity) 
    {
        capacity_ = capacity;
        arr = new int[capacity_];
        size = 0;
        tail = 0;
        head = 0;
    }
    ~Deck()
    {
        delete[] arr;
    }
    void push_front(int value)
    {
        if (size == capacity_)
            grow();
        head = (capacity_ + head - 1) % capacity_;
        arr[head] = value;
        size++;
    }
    void push_back(int value)
    {
        if (size == capacity_)
            grow();
        arr[tail] = value;
        tail = (tail + 1) % capacity_;
        size++;
    }
    int pop_front()
    {
        if (size == 0)
            return -1;
        int value = arr[head];
        head = (head + 1) % capacity_;
        size--;
        return value;
    }
    int pop_back()
    {
        if (size == 0)
            return -1;
        tail = (capacity_ + tail - 1) % capacity_;
        size--;
        return arr[tail];
    }
};

int run(std::istream& input, std::ostream& output)
{
    Deck D(5);
    int n = 0;
    int cmd = 0;
    int value = 0;
    input >> n;
    for (int i = 0; i < n; i++)
    {
        input >> cmd;
        switch (cmd)
        {
        case 1:
            input >> value;
            D.push_front(value);
            break;
        case 2:
            input >> value;
            if (D.pop_front() != value)
                {
                    output << "NO";
                    return 0;
                }
            break;
        case 3:
            input >> value;
            D.push_back(value);
            break;
        case 4:
            input >> value;
            if (D.pop_back() != value)
                {
                    output << "NO";
                    return 0;
                }
            break;
        default:
            break;
        }
    }
    output << "YES";
    return 0;
}

void runtest()
{
    {
    std::stringstream input;
    std::stringstream output;
    input << "3\n";
    input << "1 44\n";
    input << "3 50\n";
    input << "2 44\n";
    run(input, output);
    assert(output.str() == "YES");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "2\n";
    input << "2 -1\n";
    input << "1 10\n";
    run(input, output);
    assert(output.str() == "YES");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "2\n";
    input << "3 44\n";
    input << "4 66\n";
    run(input, output);
    assert(output.str() == "NO");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "4\n";
    input << "1 44\n";
    input << "1 55\n";
    input << "1 66\n";
    input << "2 55\n";
    run(input, output);
    assert(output.str() == "NO");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "1\n";
    input << "2 -1\n";
    run(input, output);
    assert(output.str() == "YES");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "1\n";
    input << "4 -1\n";
    run(input, output);
    assert(output.str() == "YES");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "1\n";
    input << "4 0\n";
    run(input, output);
    assert(output.str() == "NO");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "2\n";
    input << "3 20\n";
    input << "4 20\n";
    run(input, output);
    assert(output.str() == "YES");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "2\n";
    input << "1 20\n";
    input << "2 20\n";
    run(input, output);
    assert(output.str() == "YES");
    }
    {
    std::stringstream input;
    std::stringstream output;
    input << "2\n";
    input << "3 20\n";
    input << "4 20\n";
    run(input, output);
    assert(output.str() == "YES");
    }
}

int main()
{
    runtest();
    run(std::cin, std::cout);
    return 0;
}