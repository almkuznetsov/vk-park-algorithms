#include <iostream>

int find_k(int n, int array[], int k)
{
    int k_low = 0;
    int k_high = n-1;
    int k_mid = 0;
    while (k_high - k_low > 1) //бинарный поиск
    {
        k_mid = (k_high + k_low) / 2;
        if (array[k_mid] < k)
        {
            k_low = k_mid + 1;
        }
        else 
        {
            k_high = k_mid;
        }
    }
    if (array[k_low] == k) 
    {
        return k_low;
    }
    if (array[k_high] == k)
    {
        return k_high;
    }
    if (array[k_low] < k && array[k_high] < k) 
    {
        return k_high + 1;
    }    
    if (array[k_low] < k)
    {
        return k_high;
    }
    else
    {
        return k_low;
    }

}

int main(){
int n;
std::cin >> n;
int array[n];
for (int i = 0; i < n; i++) 
{
    std::cin >> array[i];
}
int k;
std::cin >> k;
std::cout << find_k(n, array, k) << std::endl;
}

