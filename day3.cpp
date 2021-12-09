#include "utilities.h"

int part1(char* path)
{
    std::ifstream file(path);
    const auto numbers = ReadStrings(file);

    int bits = numbers.front().size();
    int mask = (1 << bits) - 1;
    int gamma = 0;

    for (int i = 0; i < bits; i++) {
        int cnt = 0;
        for (auto& num : numbers)
            cnt += num[i] - '0';
        gamma = (gamma << 1) | (cnt > numbers.size() >> 1);
    }

    return gamma * (~gamma & mask);
}

int part2(char* path)
{
    std::ifstream file(path);
    const auto numbers = ReadStrings(file);
    int bits = numbers.front().size();

    auto g = numbers;
    for (int i = 0; i < bits && g.size() > 1; i++) {
        int cnt = 0;
        for (auto& num : g)
            cnt += num[i] - '0';
        char c = '0' + (2 * cnt >= g.size());
        g.erase(std::remove_if(g.begin(), g.end(), [i, c](auto& s) { return s[i] != c; }), g.end());
    }

    auto e = numbers;
    for (int i = 0; i < bits && e.size() > 1; i++) {
        int cnt = 0;
        for (auto& num : e)
            cnt += num[i] - '0';
        char c = '0' + (2 * cnt < e.size());
        e.erase(std::remove_if(e.begin(), e.end(), [i, c](auto& s) { return s[i] != c; }), e.end());
    }

    return std::stoi(g.front(), nullptr, 2) * std::stoi(e.front(), nullptr, 2);
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