#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
constexpr void reverse(T &arr, size_t &&size)
{
    for (size_t i = 0; i < size / 2; i++)     // o(n/2)
        std::swap(arr[i], arr[size - i - 1]); // o(1)
};
int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    reverse(arr, 5);
    for (const auto &t : arr)
        std::cout << t << " ";
    std::cout << std::endl;
    std::string str[5] = {"hey", "yo", "dafg", "sdf", "mk"};
    reverse(str, 5);
    for (const auto &t : str)
        std::cout << t << " ";
    std::exit(0);
}
