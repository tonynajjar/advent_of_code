#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>

std::map<std::string, std::multiset<std::string>> map;
std::multiset<std::string> multiset;

std::set<std::string> parents_set;
std::set<std::string> find_all_parents(const std::string &bag){
    for (auto map_it = map.begin(); map_it !=map.end(); ++map_it)
        for (auto it2 = (map_it->second).begin(); it2 !=(map_it->second).end(); ++it2)
            if(*it2 == bag){
                parents_set.insert(map_it->first);
                find_all_parents(map_it->first);
            }
    return parents_set;
}

std::multiset<std::string> children_set;
std::multiset<std::string> find_all_children(const std::string &bag){
    for(auto set_it = map[bag].begin(); set_it != map[bag].end(); ++set_it){
        children_set.insert(*set_it);
        std::cout << *set_it << std::endl << std::endl;
        find_all_children(*set_it);
    }
    return children_set;
}

void add_to_set(const std::string &bag, const int &count){
    for(int i = 0; i < count; i++){
        multiset.insert(bag);
        //std::cout << bag << std::endl;
    }
}

void eraseAllSubStr(std::string & mainStr, const std::string & toErase)
{
    size_t pos = std::string::npos;
    // Search for the substring in string in a loop untill nothing is found
    while ((pos  = mainStr.find(toErase) )!= std::string::npos)
    {
        // If found then erase it from string
        mainStr.erase(pos, toErase.length());
    }
}

int main()
{
    std::string line;
    std::ifstream is("data.txt");
    std::string container_bag;
    std::string first_inner_bag;
    std::string delimiter1 = "contain ";
    std::string delimiter2 = ", ";
    int previous_index = 0;
    size_t index = 0;
    while (std::getline(is, line))
    {
        container_bag = line.substr(0, line.find(" bag"));
        if(line.find("no other") != std::string::npos){
            map[container_bag] = multiset;
            multiset.clear();
            continue;
        }
        auto inner_bags = line.substr(line.find(delimiter1) + delimiter1.length());
        eraseAllSubStr(inner_bags, " bags");
        eraseAllSubStr(inner_bags, " bag");
        inner_bags = inner_bags.substr(0, inner_bags.size()-1);
        while ((index = inner_bags.find(delimiter2)) != std::string::npos) {
            std::string bag = inner_bags.substr(0, index);
            ///std::cout << bag << std::endl;

            add_to_set(bag.substr(2), std::stoi(bag.substr(0,1)));
            inner_bags.erase(0, index + delimiter2.length());
        }
        //std::cout << inner_bags << std::endl;

        add_to_set(inner_bags.substr(2), std::stoi(inner_bags.substr(0,1)));
        map[container_bag] = multiset;
        multiset.clear();
        //std::cout << container_bag << std::endl;

    }
    //find_all_parents("shiny gold");

    find_all_children("shiny gold");

    std::cout << children_set.size() << std::endl;

    return 0;
}