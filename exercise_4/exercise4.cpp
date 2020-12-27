#include <string>
#include <fstream>
#include <iostream>
#include <vector>


unsigned long traverse(int right, int down){
    std::string unit_line;
    std::string line;
    std::ifstream is("data.txt");
    int skip_lines = 1;
    int x_pos = 0;
    int trees_count = 0;
    std::getline(is, line);
    while(std::getline(is, line)){
        while(skip_lines < down){
            std::getline(is, line);
            skip_lines++;
        }
        skip_lines = 1;

        unit_line = line;
        while(x_pos+right > line.length()-1){
            line += unit_line;
        }

        x_pos += right;

        if(line[x_pos] == '#'){
            trees_count++;
        }
    }
    return trees_count;
}

int main()
{
    std::cout << traverse(1 ,1)*traverse(3,1)*traverse(5,1)*traverse(7,1)*traverse(1,2) << std::endl;
    return 0;
}