#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

class Worker
{
protected:
    std::string name;
    int experience;
    virtual std::stringstream serialize()
    {
        std::stringstream ss;
        ss << "name: " << name << std::endl
           << "experience: " << experience << std::endl;

        return ss;
    }

public:
    virtual ~Worker()
    {
        std::cout << "base destructor" << std::endl;
    };
    virtual void addExperience(int add) = 0;
};

class Engineer : Worker
{
protected:
    std::string technology;
    std::stringstream serialize() override
    {
        auto ss = Worker::serialize();
        ss << "technology: " << technology << std::endl;
        return ss;
    }

public:
    Engineer(std::string name = "default_name", int experience = 0, std::string technology = "default_tech") : technology(technology)
    {
        this->name = name;
        this->experience = experience;
    }
    ~Engineer() override
    {
        std::cout << "Eng destructor" << std::endl;
    }
    friend std::ostream &operator<<(std::ostream &str, Engineer &a)
    {
        std::cout << a.serialize().str() << std::endl;
        return str;
    }
    void addExperience(int add) override
    {
        std::cout << "Engineer's method" << std::endl;
    }
};
class Doctor : Worker
{
protected:
    std::string type;
    std::stringstream serialize() override
    {
        auto ss = Worker::serialize();
        ss << "type: " << type << std::endl;
        return ss;
    }

public:
    Doctor(std::string name = "default_name", int experience = 0, std::string type = "physisian") : type(type)
    {
        this->name = name;
        this->experience = experience;
    }
    ~Doctor()
    {
        std::cout << "Doc destructor" << std::endl;
    }
    friend std::ostream &operator<<(std::ostream &str, Doctor &a)
    {
        std::cout << a.serialize().str() << std::endl;
        return str;
    }
    void addExperience(int add) override
    {
        std::cout << "Doctor's method" << std::endl;
    }
};

class Programmer : Engineer
{
protected:
    std::string status;

public:
    Programmer(std::string name = "default_name", int experience = 0, std::string technology = "default_tech", std::string status = "junior") : Engineer(name, experience, technology), status(status) {}
    friend std::ostream &operator<<(std::ostream &str, Programmer &a)
    {
        auto t = Engineer(a);
        str << t << "status: " << a.status << std::endl;
        return str;
    }
    void addExperience(int add) override
    {
        Engineer::addExperience(add);
        std::cout << "Programmer's method" << std::endl;
    }
};
class Surgeon : Doctor
{
protected:
    int surgeon_hours;

public:
    Surgeon(std::string name = "default_name", int experience = 0, std::string type = "physisian", int surgeon_hours = 0) : Doctor(name, experience, type), surgeon_hours(surgeon_hours) {}
    friend std::ostream &operator<<(std::ostream &str, Surgeon &a)
    {
        auto t = Doctor(a);
        str << t << "surgeon hours: " << a.surgeon_hours << std::endl;
        return str;
    }
    /* ~Surgeon()
     {
         std::cout << "Surgeon destructor" << std::endl;
     } */
    void addExperience(int add) override
    {
        Doctor::addExperience(add);
        std::cout << "Surgeon's method" << std::endl;
    }
};

int main()
{
    auto arr = new Worker *[4];
    arr[0] = (Worker *)(new Engineer("Jack", 4));
    arr[1] = (Worker *)(new Programmer("Adam", 3));
    arr[2] = (Worker *)(new Doctor("Fred", 3));
    arr[3] = (Worker *)(new Surgeon("Fred", 24));
    for (int i = 0; i < 4; i++)
    {
        std::cout << "\u001b[31m" << typeid(*arr[i]).name() << "\u001b[0m" << std::endl;
        arr[i]->addExperience(2);
        std::cout << "---------------------------" << std::endl;
    }
    for (int i = 0; i < 4; i++)
        delete (arr[i]);
    delete[] arr;
    std::exit(0);
}
