/*
Дано множество целых чисел из [0..10^9] размера n. 
Используя алгоритм поиска k-ой порядковой статистики, 
требуется найти следующие параметры множества:
10%  перцентиль
медиана
90%  перцентиль

Требования: к дополнительной памяти: O(n). 
Среднее время работы: O(n)
Должна быть отдельно выделенная функция partition. 
Рекурсия запрещена. 
Решение должно поддерживать передачу функции сравнения снаружи.

Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

*/

#include <iostream>
#include <random>

template <typename T>
struct DefaultComparator
{
    bool operator()(const T &l, const T &r) const
    {
        return l < r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T> >
int partition (T* arr, int l, int r, Comparator comp = Comparator())
{
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(l, r - 1); 

    int pivot_idx = distr(gen);
    T pivot = arr[pivot_idx];
    
    std::swap(arr[pivot_idx], arr[r - 1]);

    int i = l;
    int j = l;
    while (j != r - 1) 
    {
        if (!comp(arr[j], pivot))
        {
            j++;
        }
        else
        {
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    std::swap(arr[i], arr[r - 1]);
    return i;
}

template<typename T, typename Comparator = DefaultComparator<T> >
int kth_element(T* arr, int size, int k, Comparator comp = Comparator())
{
    int l = 0;
    int r = size;
    while (l < r)
    {
        int m = partition(arr, l, r, comp);
        if (m == k) 
        {
            return arr[k];
        }
        else if (m < k) 
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }
}

int main()
{
    int n = 0;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    int p10 = n / 10;
    int mid = n / 2;
    int p90 = n * 0.9;
    std::cout << kth_element(arr, n, p10) << std::endl;
    std::cout << kth_element(arr, n, mid) << std::endl;
    std::cout << kth_element(arr, n, p90) << std::endl;
    delete[] arr;
    return 0;
}

