/*
Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
Топ K пользователей из лога
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости. Количество заходов и идентификаторы пользователей не повторяются.
Требования: время работы O(N * logK), где N - кол-во пользователей. Ограничение на размер кучи O(K).
Формат входных данных: Сначала вводятся N и K, затем пары (Идентификатор пользователя, посещаемость сайта).
Формат выходных данных: Идентификаторы пользователей в порядке возрастания посещаемости
*/
#include <iostream>

template <typename T>
struct DefaultComparator
{
    bool operator()(const T &l, const T &r) const
    {
        return l > r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class Heap
{
public:
    Heap(Comparator comp = Comparator())
    {
        buf = new T[5];
        buf_size = 5;
        heap_size = 0;
        comp = comp;
    }
    Heap(const T &arr, size_t arr_size, Comparator comp = Comparator())
    {
        comp = comp;
        buf = new T[arr_size];
        for (size_t i = 0; i < arr_size; i++)
        {
            buf[i] = arr[i];
        }
        heap_size = arr_size;
        buf_size = arr_size;
    }
    ~Heap()
    {
        delete[] buf;
    };

    Heap(const Heap &) = delete; // no copy operations
    Heap &operator=(const Heap &) = delete;

    Heap(Heap &&) = delete; // no move operations
    Heap &operator=(Heap &&) = delete;

    const T &top()
    {
        return buf[0];
    };
    void pop()
    {
        if (heap_size <= 0)
            return;
        heap_size--;
        buf[0] = buf[heap_size];
        heapify();
    };
    void push(const T &val)
    {
        heap_size++;
        if (heap_size >= buf_size)
            grow();
        buf[heap_size - 1] = val;
        sift_up(heap_size - 1);
    };

    bool is_empty() const { return heap_size == 0; }
    size_t size() const { return heap_size; }

private:
    void heapify()
    {
        if (heap_size <= 1)
            return;
        for (int i = (heap_size / 2) - 1; i >= 0; i--)
        {
            sift_down(i);
        }
    };
    void sift_up(size_t index)
    {
        while (index > 0)
        {
            size_t parent = (index - 1) / 2;
            if (comp(buf[index], buf[parent]))
                return;
            std::swap(buf[index], buf[parent]);
            index = parent;
        }
    };
    void sift_down(size_t i)
    {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t largest = i;
        if (left < heap_size && comp(buf[i], buf[left]))
            largest = left;
        if (right < heap_size && comp(buf[largest], buf[right]))
            largest = right;
        if (largest != i)
        {
            std::swap(buf[i], buf[largest]);
            sift_down(largest);
        }
    };
    void grow()
    {
        buf_size *= 2;
        T *new_buf = new T[buf_size];
        for (size_t i = 0; i < heap_size; i++)
            new_buf[i] = buf[i];
        delete[] buf;
        buf = new_buf;
    };

    Comparator comp;

    T *buf;
    size_t buf_size;
    size_t heap_size;
};

struct User
{
public:
    int id;
    int visits;
    bool operator<(const User &r) const
    {
        return visits < r.visits;
    }
    bool operator>(const User &r) const
    {
        return visits > r.visits;
    }
};

int main()
{
    int n = 0;
    int k = 0;
    std::cin >> n >> k;

    User *users = new User[n];
    for (size_t i = 0; i < n; i++)
        std::cin >> users[i].id >> users[i].visits;
    Heap<User> *heap = new Heap<User>();
    for (size_t i = 0; i < n; i++)
    {
        if (i >= k)
        {
            heap->push(users[i]);
            heap->pop();
        }
        else
        {
            heap->push(users[i]);
        }
    }
    for (size_t i = 0; i < k; i++)
    {
        std::cout << heap->top().id << " ";
        heap->pop();
    }
    delete[] users;
    delete heap;
    return 0;
}