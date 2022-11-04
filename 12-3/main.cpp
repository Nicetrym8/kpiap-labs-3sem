#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{
    std::string str = "abc";
    std::string buf;
    std::string word;
    size_t line_cnt = 0;
    std::ifstream i("input.txt");
    std::ofstream o("output.txt");
    while (!i.eof())
    {
        line_cnt++;
        size_t counter = 0;
        std::getline(i, buf);
        std::stringstream ss(buf);
        while (!ss.eof())
        {
            ss >> word;
            counter += (word.find(str.c_str()) != std::string::npos);
        }
        o << "line " << line_cnt << ": " << counter << std::endl;
    }
}
