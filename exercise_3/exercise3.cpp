#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<std::string> dissectStr(std::string str, const char delimiter = ' ')
{
    // Returns first token
    char *token = strtok(&str[0], &delimiter);
    std::vector<std::string> dissected_line;
    // Keep printing tokens while one of the
    // delimiters present in str[].
    while (token != NULL)
    {
        dissected_line.push_back(token);
        token = strtok(NULL, &delimiter);
    }
    return dissected_line;
}

void print(std::vector<std::string> const &input)
{
    std::copy(input.begin(),
            input.end(),
            std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
}

void exercise1()
{
    std::string line;
    std::ifstream is("data.txt");
    unsigned long count = 0;
    while(std::getline(is, line)){
        std::vector<std::string> dissected_line = dissectStr(line);
        unsigned int char_count = std::count(dissected_line[2].begin(), dissected_line[2].end(), dissected_line[1][0]);
        auto lower_bound = dissectStr(dissected_line[0], '-').front();
        auto upper_bound = dissectStr(dissected_line[0], '-').back();
        print(dissected_line);
        std::cout << lower_bound << " " << char_count << " " << upper_bound << std::endl;
        if((stoi(lower_bound) <= char_count) && (char_count <= stoi(upper_bound))){
            count++;
        }
    }
    std::cout << count << std::endl;
}

void exercise2()
{
    std::string line;
    std::ifstream is("data.txt");
    unsigned long count = 0;
    while(std::getline(is, line)){
        std::vector<std::string> dissected_line = dissectStr(line);
        auto first_index = dissectStr(dissected_line[0], '-').front();
        auto second_index = dissectStr(dissected_line[0], '-').back();
        print(dissected_line);
        std::cout << dissected_line[1][0] << " " << dissected_line[2][stoi(first_index)-1] << " " << dissected_line[2][stoi(second_index)-1] << std::endl;

        if((dissected_line[1][0] == dissected_line[2][stoi(first_index)-1]) != (dissected_line[1][0] == dissected_line[2][stoi(second_index)-1])){
            count++;
        }
    }
    std::cout << count << std::endl;
}

int main()
{
    //exercise1();
    exercise2();
    return 0;
}