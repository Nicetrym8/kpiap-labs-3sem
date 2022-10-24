#include <iostream>
#include <string>
#define arr_cap 7
class StackException
{
private:
    std::string message = "Stack exception";

public:
    StackException(std::string &&message) : message(message) {}
    const char *what() const noexcept
    {
        return message.c_str();
    }
    /*smth else*/
};
template <typename T>
class Stack
{
private:
    T arr[arr_cap];
    int size = 0;

public:
    void push(const T &el)
    {
        arr[size] = el;
        size++;
        if (size > arr_cap)
            throw StackException("Stack overflow");
    }
    void pop()
    {
        size--;
        if (size < 0)
            throw StackException("Negative stack size");
    }
    size_t search(T &&value)
    {
        for (const auto &t : arr)
            if (t == value)
                return &t - &arr[0];
        throw StackException("Cannot find value");
    }
    const T &at(size_t index)
    {
        return arr[index];
    }
    const T &peek()
    {
        return arr[size];
    }

    bool operator==(const Stack &obj)
    {
        return this->size == obj.size;
    }
    bool operator<(const Stack &obj)
    {
        return this->size < obj.size;
    }
    bool operator>(const Stack &obj)
    {
        return this->size > obj.size;
    }
    /*etc*/
};
int main()
{
    try
    {
        auto stack = Stack<int>();
        for (int i = 0; i < 10; i++)
        {
            stack.push(i);
        }
        stack.search(5);
        for (int i = 0; i < 10; i++)
        {
            std::cout << stack.peek() << std::endl;
            stack.pop();
        }
    }
    catch (const StackException &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::exit(0);
}
