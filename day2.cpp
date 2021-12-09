#include "utilities.h"

int part1(char* path)
{
    std::ifstream file(path);

    int x = 0;
    int y = 0;

    while (file)
    {
        std::string command;
        file >> command;

        int amount;
        file >> amount;

        if (command == "forward")
            x += amount;
        else if (command == "down")
            y += amount;
        else if (command == "up")
            y -= amount;
    }

    return x * y;
}

int part2(char* path)
{
    std::ifstream file(path);

    int x = 0;
    int y = 0;
    int aim = 0;

    while (file)
    {
        std::string command;
        file >> command;

        int amount;
        file >> amount;

        if (command == "forward")
        {
            x += amount;
            y += aim * amount;
        }
        else if (command == "down")
            aim += amount;
        else if (command == "up")
            aim -= amount;
    }

    return x * y;
}

int main(int argc, char** argv)
{
    char* path;

    if(argc != 2)
    {
        path = new char[100];
        sprintf(path, "input/%s.txt", argv[0]);
    }
    else path = argv[1];

    printf("PART 1: %i\n", part1(path));
    printf("PART 2: %i\n", part2(path));

    if(argc != 2)
        delete[] path;
}