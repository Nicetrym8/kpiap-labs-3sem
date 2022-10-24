#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Tourist
{
    std::string name;
    std::string surname;
    std::string origin_country;

public:
    Tourist() {}
    Tourist(std::string name, std::string surname, std::string origin_country) : name(name), surname(surname), origin_country(origin_country) {}
    friend std::ostream &operator<<(std::ostream &str, Tourist &obj)
    {
        str << obj.name << ' ' << obj.surname << ' ' << obj.origin_country << '\n';
        return str;
    }
    friend std::istream &operator>>(std::istream &str, Tourist &obj)
    {
        str >> obj.name >> obj.surname >> obj.origin_country;
        return str;
    }

    void binary_read(std::ifstream &str)
    {

        auto read = [](std::ifstream &str)
        {
            size_t len;
            char *buf;
            str.read(reinterpret_cast<char *>(&len), sizeof(size_t));
            buf = new char[len];
            str.read(buf, len);
            std::string output(buf);
            delete[] buf;
            return output;
        };
        name = read(str);
        surname = read(str);
        origin_country = read(str);
    }
    static void del_item_binary(std::string querry, std::string filename)
    {
        {
            std::ifstream str(filename);
            std::ofstream ostr(filename + ".temp");

            Tourist o;
            while (true)
            {
                try
                {
                    std::stringstream ss;
                    o.binary_read(str);
                    ss << o;
                    if (ss.str().find(querry.c_str()) == std::string::npos)
                    {
                        o.binary_write(ostr);
                    }
                }
                catch (std::exception &e)
                {
                    break;
                }
            }
        }
        std::remove(filename.c_str());
        std::rename((filename + ".temp").c_str(), filename.c_str());
    }
    void binary_write(std::ofstream &ofs)
    {

        auto write = [](std::string &str, std::ofstream &ofs)
        {
            size_t len = str.length();
            ofs.write(reinterpret_cast<char *>(&len), sizeof(size_t));
            ofs.write(str.c_str(), len);
        };
        write(name, ofs);
        write(surname, ofs);
        write(origin_country, ofs);
    }
};

int main()
{
    {
        std::ofstream str("123.bin", std::ios::binary);
        std::ofstream text("123.txt");
        Tourist o;
        for (const auto &s : {
                 "sdfs",
                 "ghjfhj",
                 "kkkfkf",
             })
        {
            o = Tourist(s, "jsfghsf", "gdhjdghj");
            text << o;
            o.binary_write(str);
            std::cout << "Write: " << o;
        }
    }
    std::cout << std::endl;
    {
        std::ifstream str("123.bin", std::ios::binary);
        std::ifstream text("123.txt");
        auto o = Tourist();
        for (int i = 0; i < 3; i++)
        {
            o.binary_read(str);
            std::cout << "Read: ";
            std::cout << o;
            text >> o;
            std::cout << o;
        }
        Tourist::del_item_binary("sdfs", "123.bin");
        Tourist::del_item_binary("sdsf", "dfsgdfg");
    }
}
