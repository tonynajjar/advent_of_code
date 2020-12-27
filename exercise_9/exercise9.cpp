#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <tuple>

void build_program(std::vector<std::tuple<std::string, int>> &commands)
{
    std::string line;
    std::ifstream is("data.txt");
    while (std::getline(is, line))
    {
        std::string op = line.substr(0, 3);
        int param = std::stoi(line.substr(4));
        commands.push_back(std::make_tuple(op, param));
    }
}

void print(std::vector<std::tuple<std::string, int>> const &v)
{
    std::cout << "The vector elements are : " << std::endl;
    for (int i = 0; i < v.size(); i++)
        std::cout << std::get<0>(v[i]) << ' ' << std::get<1>(v[i]) << std::endl;
}

void execute_command(std::string const &op, int const &param, int &index, int &acc)
{
    //std::cout << op << ' ' << param << std::endl;

    if (op == "acc")
    {
        acc += param;
        std::cout << "accumulator: " << acc << std::endl;

        index++;
    }
    else if (op == "jmp")
    {
        index += param;
    }
    else if (op == "nop")
    {
        index++;
    }
}

std::string modify_program(std::string op)
{
    if (op == "jmp")
    {
        op = "nop";
    }
    else if (op == "nop")
    {
        op = "jmp";
    }
    return op;
}

int main()
{
    std::set<int> visited_indices;
    std::vector<std::tuple<std::string, int>> commands;
    build_program(commands);
    int acc = 0;
    int occurence_to_change = 1;
    bool program_terminated = false;
    while (!program_terminated)
    {
        visited_indices.clear();
        int occurence = 0;
        int index_of_changed_occurence = 0;
        int index = 0;
        acc = 0;
        while (visited_indices.find(index) == visited_indices.end())
        {
            visited_indices.insert(index);

            std::string op = std::get<0>(commands[index]);
            int param = std::get<1>(commands[index]);
            std::cout << index << " " << op << " " << param << std::endl;

            if (&(commands[index]) == &(commands.back()))
            {
                std::cout << op << " " << param << std::endl;

                program_terminated = true;
                break;
            }
            if (op == "jmp" || op == "nop")
            {
                occurence++;
                //std::cout << "occurence_to_change: " << occurence_to_change << " occurence: " << occurence<< std::endl;

                if (occurence == occurence_to_change)
                {
                    op = modify_program(op);
                    std::cout << "CHANGED to " << op << " " << param << std::endl;
                    index_of_changed_occurence = index;
                }
            }
            execute_command(op, param, index, acc);
        }
        std::cout << "We already went through index: " << index << std::endl;
        occurence_to_change++;
        std::cout << "occurence_to_change: " << occurence_to_change << std::endl << std::endl;
    }
    std::cout << acc << std::endl;
    return 0;
}