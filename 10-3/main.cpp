#include <iostream>
#include <string>
#include <iterator>
#include <cstddef>

template <typename T>
class LinkedList
{
    class Node;

public:
    LinkedList() noexcept
    {
        root = nullptr;
    }
    class Iterator;

    Iterator begin()
    {
        return Iterator(root);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }
    ~LinkedList()
    {
        Node *crawler = get_root();
        Node *crawler1 = crawler;
        while (crawler)
        {
            crawler1 = crawler->next;
            delete crawler;
            crawler = crawler1;
        }
    }
    void push_back(T data);
    T operator[](size_t index);
    void pop(size_t index);
    void show();
    int search(T item);
    class Iterator
    {
    public:
        Iterator() noexcept : current(root) {}

        Iterator(const Node *pNode) noexcept : current(pNode) {}

        Iterator &operator=(Node *pNode)
        {
            this->current = pNode;
            return *this;
        }

        Iterator &operator++()
        {
            if (current)
                current = current->next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator!=(const Iterator &iterator)
        {
            return current != iterator.current;
        }

        int operator*()
        {
            return current->data;
        }

    private:
        const Node *current;
    };

private:
    class Node
    {
        T data;
        Node *next;
        friend class LinkedList;
    };

    Node *get_node(T data)
    {
        Node *new_node = new Node;
        new_node->data = data;
        new_node->next = nullptr;

        return new_node;
    }
    Node *&get_root()
    {
        return root;
    }

    static Node *root;
};

template <typename T>
typename LinkedList<T>::Node *LinkedList<T>::root = nullptr;

template <typename T>
void LinkedList<T>::push_back(T data)
{
    Node *temp = get_node(data);
    if (!get_root())
    {
        get_root() = temp;
    }
    else
    {
        Node *crawler = get_root();
        while (crawler->next)
        {
            crawler = crawler->next;
        }

        crawler->next = temp;
    }
}
template <typename T>
T LinkedList<T>::operator[](size_t index)
{
    Node *crawler = get_root();

    while (index--)
        crawler = crawler->next;
    if (crawler == nullptr)
        throw std::out_of_range("Out of LinkedList bouds");
    return crawler->data;
}
template <typename T>
void LinkedList<T>::show()
{
    Node *crawler = get_root();

    while (crawler)
    {
        std::cout << crawler->data << " ";
        crawler = crawler->next;
    }

    std::cout << std::endl;
}
template <typename T>
int LinkedList<T>::search(T item)
{
    Node *crawler = get_root();
    int index = 0;
    while (crawler)
    {
        if (crawler->data == item)
            return index;
        crawler = crawler->next;
        index++;
    }
    return -1;
}
template <typename T>

void LinkedList<T>::pop(size_t index)
{
    Node *crawler = get_root();
    Node *tmp;
    if (index)
    {
        index--;
        while (index--)
        {
            if (crawler == nullptr)
                throw std::out_of_range("Out of LinkedList bouds");
            crawler = crawler->next;
        }
        if (crawler->next == nullptr)
            delete crawler;
        else
        {
            tmp = crawler->next->next;
            delete crawler->next;
            crawler->next = tmp;
        }
    }
    else
    {

        if (root->next != nullptr)
        {
            tmp = root->next;
            delete root;
            root = tmp;
        }
        else
        {
            delete root;
            root = nullptr;
        }
    }
}
int main()
{
    LinkedList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.pop(0);
    std::cout << "Search for 3" << std::endl
              << list.search(3) << std::endl;
    std::cout << "Showing all" << std::endl;
    list.show();
    for (const auto &t : list)
    {
        std::cout << t << ' ';
    }
    std::cout << std::endl;
    for (auto iterator = list.begin();
         iterator != list.end(); iterator++)
    {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 6; i++)
    {
        std::cout << list[i] << ' ';
    }
    return 0;
}
