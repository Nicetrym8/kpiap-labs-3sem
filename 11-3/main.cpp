#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace school
{
    struct Adress
    {
        std::string street;
        std::string home;

    public:
        Adress(std::string home, std::string street) : street(street), home(home) {}
        Adress() {}
        friend std::ostream &operator<<(std::ostream &str, Adress obj)
        {
            str << obj.street << ", " << obj.home << '\n';
            return str;
        }
    };
    class Person
    {
    protected:
        std::string firstname;
        std::string lastname;
        Adress adress;

    public:
        virtual void stream(std::ostream &str)
        {
            str << "Firstname: " << firstname << '\n'
                << "Lastname: " << lastname << '\n'
                << "Adress: " << adress << '\n';
        }
        Person(std::string firstname, std::string lastname, std::string street, std::string home) : firstname(firstname), lastname(lastname)
        {
            adress = Adress(home, street);
        }
        virtual ~Person() {}
        template <typename T>
        friend std::ostream &operator<<(std::ostream &str, T obj)
        {
            obj.stream(str);
            return str;
        }
        /*etc*/
    };
    class Student : public Person
    {
        std::string school;
        void stream(std::ostream &str) override
        {
            str << "\nStudent: \n";
            Person::stream(str);
            str << "School: " << school << '\n';
        }
        friend class Parent;

    public:
        Student(std::string firstname, std::string lastname, std::string street, std::string home, std::string school) : Person(firstname, lastname, street, home), school(school) {}

        /*etc*/
    };
    class Parent : public Person
    {
        Student student;

        /*etc*/
    public:
        void stream(std::ostream &str) override
        {
            str << "\nParent: \n";
            Person::stream(str);
            student.stream(str);
        }
        Parent(std::string firstname, std::string lastname, std::string street, std::string home, Student student) : Person(firstname, lastname, street, home), student(student) {}
    };

    class Curator : public Person
    {
        std::vector<Parent> journal;

    public:
        Curator(std::string firstname, std::string lastname, std::string street, std::string home) : Person(firstname, lastname, street, home) {}
        void addParent(Parent &parent)
        {
            journal.push_back(parent);
        }
        void stream(std::ostream &str) override
        {
            for (const auto &t : journal)
                str << t << '\n';
        }
        /*etc*/
    };
}

int main()
{
    auto k = school::Student("Alex", "Johnson", "St.Marc", "70/33", "School N37");
    auto f = school::Parent("Joe", "Johnson", "St.Marc", "70/32", k);
    auto j = school::Curator("Joe", "Johnson", "Efervest", "33/23A");
    for (size_t i = 0; i < 3; i++)
        j.addParent(f);
    std::cout << j << '\n';
}
