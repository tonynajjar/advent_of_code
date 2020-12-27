#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>


int main()
{
    std::string line;
    std::ifstream is("data.txt");
    int sum = 0;
    bool first_person = true;
    std::set<char> set;
    while (std::getline(is, line))
    {
        if (line.empty())
        {
            sum += set.size();
            set.clear();
            first_person = true;
            continue;
        }
        if(first_person){
            for(char const &letter:line)
                set.insert(letter);
        }
        else{
            for (auto it = set.begin(); it != set.end();){
                std::cout << *it << std::endl;
                if(line.find(*it) == std::string::npos){
                    it = set.erase(it);
                }
                else{
                    ++it;
                }
            }
        }
        first_person = false;

    }
    std::cout << sum << std::endl;
    return 0;
}