#include "utilities.h"

int part1(char* path)
{
    std::ifstream file(path);
    std::vector<int> nums;
    nums = ReadInts(file);

    int ans = 0;
    for (int i = 1; i < nums.size(); i++)
        if(nums[i - 1] < nums[i])
            ans++;

    return ans;
}

int part2(char* path)
{
    std::ifstream file(path);
    std::string word;

    constexpr int SIZE = 3;

    int window[SIZE];

    for(int i = 0; i < SIZE; i++)
    {
        file >> word;
        window[i] = atoi(word.c_str());
    }

    int ans = 0;
    while((file >> word))
    {
        int val = atoi(word.c_str());
        ans += val > window[0];
        memmove(window, window + 1, sizeof(*window) * (SIZE - 1));
        window[SIZE - 1] = val;
    }

    return ans;
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