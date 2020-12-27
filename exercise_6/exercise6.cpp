#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

int binary_search(std::string line, int lower_bound, int upper_bound){
    for(char const &c: line){
        switch (c)
            {
            case 'F':
                upper_bound = upper_bound - (upper_bound - lower_bound + 1)/2;

                break;
            case 'B':
                lower_bound = lower_bound + (upper_bound - lower_bound + 1)/2;
                break;
            case 'L':
                upper_bound = upper_bound - (upper_bound - lower_bound + 1)/2;
                break;
            case 'R':
                lower_bound = lower_bound + (upper_bound - lower_bound + 1)/2;
                break;
            default:
                break;
            }
    }
    return lower_bound;
}

void print_2D_vector(const std::vector<std::vector<char>> &vect){
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect[i].size(); j++)
        {
            std::cout << vect[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::pair<int,int> find_empty_place(const std::vector<std::vector<char>> &vect){
    for (int i = 10; i < vect.size()-22; i++)
    {
        for (int j = 0; j < vect[i].size(); j++)
        {
            if (vect[i][j] == 'O')
            return std::make_pair(i,j);
        }
    }
}


int main()
{
    std::string line;
    std::ifstream is("data.txt");
    int id;
    int row;
    int column;
    std::vector<std::vector<char>> vect(128,std::vector<char> (8, 'O'));
    std::pair<int,int> pair;
    while (std::getline(is, line))
    {
        row = binary_search(line.substr(0, 7), 0, 127);
        column = binary_search(line.substr(7), 0, 7);
        vect[row][column] = 'X';
    }
    pair = find_empty_place(vect);
    std::cout << pair.first * 8 + pair.second << std::endl;
    return 0;
}