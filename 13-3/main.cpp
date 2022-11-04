#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
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
    Worker(std::string name = "default_name", int experience = 0)
    {
        this->name = name;
        this->experience = experience;
    }
    virtual ~Worker()
    {
        std::cout << "base destructor" << std::endl;
    };
    virtual void add_experience(int add)
    {
        std::cout << "Worker's method" << std::endl;
    }
    template <typename T>
    friend std::ostream &operator<<(std::ostream &str, Worker a)
    {
        std::cout << a.serialize().str() << std::endl;
        return str;
    }
};

class Engineer : public Worker
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
    Engineer(std::string name = "default_name", int experience = 0, std::string technology = "default_tech") : Worker(name, experience), technology(technology) {}
    ~Engineer() override
    {
        std::cout << "Eng destructor" << std::endl;
    }
    void add_experience(int add) override
    {
        std::cout << "Engineer's method" << std::endl;
    }
    void engs_unique_method()
    {
        std::cout << "Engineer's unique" << std::endl;
    }
};
class Doctor : public Worker
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
    Doctor(std::string name = "default_name", int experience = 0, std::string type = "physisian") : Worker(name, experience), type(type) {}
    ~Doctor()
    {
        std::cout << "Doc destructor" << std::endl;
    }
    void add_experience(int add) override
    {
        std::cout << "Doctor's method" << std::endl;
    }
    void docs_unique_method()
    {
        std::cout << "Doctors's unique" << std::endl;
    }
};

class Builder : public Worker
{

    std::string worker_object;

public:
    Builder(std::string name = "default_name", int experience = 0, std::string worker_object = "worker_object") : Worker(name, experience), worker_object(worker_object) {}
    ~Builder()
    {
        std::cout << "Builder destructor" << std::endl;
    }
    void bldr_unique_method()
    {
        std::cout << "Builder's unique" << std::endl;
    }
    void add_experience(int add) override
    {
        std::cout << "Builder's method" << std::endl;
    }
};

int main()
{
    auto arr = new Worker *[4];
    arr[0] = new Worker("Jack", 4);
    arr[1] = (Worker *)(new Engineer("Adam", 3));
    arr[2] = (Worker *)(new Doctor("Fred", 3));
    arr[3] = (Worker *)(new Builder("Fred", 24));
    for (size_t i = 0; i < 4; i++)
    {
        arr[i]->add_experience(10);
        if (auto *p = dynamic_cast<Engineer *>(arr[i]))
            p->engs_unique_method();
        if (auto *p = dynamic_cast<Doctor *>(arr[i]))
            p->docs_unique_method();
        if (auto *p = dynamic_cast<Builder *>(arr[i]))
            p->bldr_unique_method();
    }
    std::cout << std::endl;
    for (int i = 0; i < 4; i++)
        delete (arr[i]);
    delete[] arr;
}
