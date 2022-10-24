#include <iostream>
#include <string>

class Worker
{
protected:
    std::string name;
    int experience;

public:
    Worker(std::string name = "default_name", int experience = 0) : name(name), experience(experience) {}
    friend std::ostream &operator<<(std::ostream &str, Worker &a)
    {
        str << "name: " << (a.name + '\n') << "experience: " << a.experience << 'y' << std::endl;
        return str;
    }
    /*smth else*/
};

class Engineer : Worker
{
protected:
    std::string technology;

public:
    Engineer(std::string name = "default_name", int experience = 0, std::string technology = "default_tech") : Worker(name, experience), technology(technology) {}
    friend std::ostream &operator<<(std::ostream &str, const Engineer &a)
    {
        auto t = Worker(a);
        str << t << "technology: " << a.technology << std::endl;
        return str;
    }
};
class Doctor : Worker
{
protected:
    std::string type;

public:
    Doctor(std::string name = "default_name", int experience = 0, std::string type = "physisian") : Worker(name, experience), type(type) {}
    friend std::ostream &operator<<(std::ostream &str, const Doctor &a)
    {
        auto t = Worker(a);
        str << t << "type: " << a.type << std::endl;
        return str;
    }
};

class Programmer : Engineer
{
protected:
    std::string status;

public:
    Programmer(std::string name = "default_name", int experience = 0, std::string technology = "default_tech", std::string status = "junior") : Engineer(name, experience, technology), status(status) {}
    friend std::ostream &operator<<(std::ostream &str, const Programmer &a)
    {
        auto t = Engineer(a);
        str << t << "status: " << a.status << std::endl;
        return str;
    }
};
class Surgeon : Doctor
{
protected:
    int surgeon_hours;

public:
    Surgeon(std::string name = "default_name", int experience = 0, std::string type = "physisian", int surgeon_hours = 0) : Doctor(name, experience, type), surgeon_hours(surgeon_hours) {}
    friend std::ostream &operator<<(std::ostream &str, const Surgeon &a)
    {
        auto t = Doctor(a);
        str << t << "surgeon hours: " << a.surgeon_hours << std::endl;
        return str;
    }
};
class SonOfMomsFriend : virtual Programmer, virtual Surgeon
{
private:
    std::string his_third_job;

public:
    SonOfMomsFriend(std::string name = "default_name", int experience = 0, std::string technology = "default_tech", std::string status = "junior", std::string type = "physisian", int surgeon_hours = 0, std::string his_third_job = "job") : Surgeon(name, experience, type, surgeon_hours), Programmer(name, experience, technology, status), his_third_job(his_third_job) {}
    friend std::ostream &operator<<(std::ostream &str, const SonOfMomsFriend &a)
    {

        auto t1 = Surgeon(a);
        auto t2 = Programmer(a);
        str << "Surgeon info:\n"
            << t1 << "Programmer info:\n"
            << t2 << "His third job: " << a.his_third_job << std::endl;
        return str;
    }
};
int main()
{
    auto k = SonOfMomsFriend("Igor", 33, "C++", "Senior", "Cardiologist", 1280, "Plumber");
    std::cout << k;
    std::exit(0);
}
