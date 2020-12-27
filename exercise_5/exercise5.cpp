#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

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

void print_map(std::map<std::string, std::string> const &input)
{
    for (auto elem : input)
    {
        std::cout << elem.first << " " << elem.second << std::endl;
    }
}

bool is_valid_passport(std::map<std::string, std::string> passport)
{
    if (!(passport.count("byr") > 0 && std::stoi(passport["byr"]) >= 1920 && std::stoi(passport["byr"]) <= 2002))
    {
        //print_map(passport);
        //std::cout << " byr invalid" << std::endl;
        return false;
    }
    if (!(passport.count("iyr") > 0 && std::stoi(passport["iyr"]) >= 2010 && std::stoi(passport["iyr"]) <= 2020))
    {
        //print_map(passport);
        //std::cout << " iyr invalid" << std::endl;
        return false;
    }
    if (!(passport.count("eyr") > 0 && std::stoi(passport["eyr"]) >= 2020 && std::stoi(passport["eyr"]) <= 2030))
    {
        //print_map(passport);
        //std::cout << " eyr invalid" << std::endl;
        return false;
    }
    if (passport.count("hgt") > 0)
    {
        auto in_index = passport["hgt"].find("in");
        auto cm_index = passport["hgt"].find("cm");
        auto hgt = std::stoi(passport["hgt"].substr(0, 3));
        if (in_index != std::string::npos)
            if (!(hgt >= 59 && hgt <= 76))
            {
                print_map(passport);
                std::cout << " hgt in invalid" << std::endl;
                return false;
            }
            else if (cm_index != std::string::npos)
                if (!(hgt >= 150 && hgt <= 193))
                {
                    print_map(passport);
                    std::cout << " hgt cm invalid" << std::endl;
                    return false;
                }
    }
    else
    {
        //print_map(passport);
        std::cout << " hgt invalid" << std::endl;
        return false;
    }
    if (passport.count("hcl") > 0)
    {
        if (!(passport["hcl"][0] == '#' && passport["hcl"].length() - 1 == 6))
        {
            print_map(passport);
            std::cout << " hcl invalid" << std::endl;
            return false;
        }
    }
    else
    {
        //print_map(passport);
        std::cout << " hcl invalid" << std::endl;
        return false;
    }
    std::vector<std::string> colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    if (!(passport.count("ecl") > 0 && (std::find(colors.begin(), colors.end(), passport["ecl"]) != colors.end())))
    {
        print_map(passport);
        std::cout << " ecl invalid" << std::endl;
        return false;
    }
    if (!(passport.count("pid") > 0 && passport["pid"].length() == 9))
    {
        print_map(passport);
        std::cout << " pid invalid" << std::endl;
        return false;
    }

    return true;
}

int main()
{
    std::map<std::string, std::string> passport;
    std::string line;
    std::vector<std::string> dissected_line;
    std::vector<std::map<std::string, std::string>> passports;
    std::ifstream is("data.txt");
    while (std::getline(is, line))
    {
        if (line.empty())
        {
            passports.push_back(passport);
            passport.clear();
            continue;
        }
        dissected_line = dissectStr(line);
        for (auto const &pair : dissected_line)
        {
            auto tmp = dissectStr(pair, ':');
            passport[tmp.front()] = tmp.back();
        }
    }
    int count = 0;
    for (auto &passport : passports)
    {
        if (is_valid_passport(passport))
        {
            count++;
            //std::cout << "valid" << std::endl;
        }
        else
        {
            //std::cout << "not valid" << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << count << std::endl;

    return 0;
}