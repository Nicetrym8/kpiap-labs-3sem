#include <iostream>
#include <string>
class Employee
{
private:
    static int counter;
    int id;
    std::string name;
    double salary;

public:
    Employee(std::string name = "name", double salary = 10)
    {
        this->id = counter;
        this->name = name;
        this->salary = salary;
        counter++;
    }
    ~Employee()
    {
        std::cout << "Destructor called!" << std::endl;
    }
    const void show()
    {
        std::cout << "Id: " << id << " name: " << name << " salary: " << salary << std::endl;
    }

    friend class Accounter;
};
class Accounter
{
private:
    /*private field etc*/
public:
    void changeSalary(Employee &a, double salary)
    {
        if (salary <= 0)
            return;
        a.salary = salary;
    }
};
int Employee::counter = 0;
int main()
{
    auto accounter = Accounter();
    auto employee1 = Employee("Vasya", 10.5);
    auto employee2 = Employee("Bob", 22.3);

    Employee arr[3] = {Employee(),
                       Employee("Alice", 333),
                       Employee("Fred", 23.7)};
    for (auto &t : arr)
        t.show();

    accounter.changeSalary(arr[1], 20);
    std::cout << std::endl;
    for (auto &t : arr)
        t.show();
}
