/*
Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции.
Решение должно поддерживать передачу функции сравнения снаружи.
Общее время работы алгоритма O(n log n).
5_1. Реклама.
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа).
Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени.
Покупатель может видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно.
Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
*/

#include <iostream>
#include <algorithm>

template <typename T>
struct DefaultComparator
{
    bool operator()(const T &l, const T &r) const
    {
        return l <= r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T> >
void Merge(T *arrFirst, size_t sizeFirst, T *arrSecond, size_t sizeSecond, T *newArr, Comparator comp = Comparator())
{
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < sizeFirst && j < sizeSecond)
    {
        if (comp(arrFirst[i], arrSecond[j]))
        {
            newArr[k] = arrFirst[i];
            i++;
        }
        else
        {
            newArr[k] = arrSecond[j];
            j++;
        }
        k++;
    }
    while (i < sizeFirst)
    {
        newArr[k] = arrFirst[i];
        i++;
        k++;
    }
    while (j < sizeSecond)
    {
        newArr[k] = arrSecond[j];
        j++;
        k++;
    }
};

template <typename T, typename Comparator = DefaultComparator<T> >
void MergeSort(T *arr, size_t size, Comparator comp = Comparator())
{
    if (size <= 1)
        return;

    size_t firstSize = size / 2;
    size_t secondSize = size - firstSize;
    MergeSort(arr, firstSize);
    MergeSort(arr + firstSize, secondSize);
    T *newArr = new T[size];
    Merge(arr, firstSize, arr + firstSize, secondSize, newArr);
    // std::memcpy(arr, newArr, (sizeof(T) * size)
    for (int i = 0; i < size; i++)
    {
        arr[i] = newArr[i];
    }
    delete[] newArr;
};

struct User
{
public:
    int begin;
    int end;

    bool operator<=(const User &r) const
    {
        if (r.end == end)
        {
            return (begin <= r.begin);
        }
        else
        {
            return (end <= r.end);
        }
    }
};

int main()
{
    int n;
    std::cin >> n;
    User *users = new User[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> users[i].begin >> users[i].end;
    }
    MergeSort(users, n);
    int count = 0;
    int time0 = -1;
    int time1 = -1;
    for (int i = 0; i < n; i++)
    {
        if (users[i].begin > time1)
        {
            time0 = users[i].end - 1;
            time1 = users[i].end;
            count += 2;
        }
        else
        {
            if (users[i].begin == time1 || (users[i].begin > time0 && users[i].end > time1))
            {
                time0 = time1;
                time1 = users[i].end;
                count++;
            }
            else
            {
                if (users[i].begin > time0 && users[i].begin < time1)
                {
                    time0 = users[i].end;
                    count++;
                }
            }
        }
    }
    std::cout << count;
    delete[] users;
    return 0;
}

