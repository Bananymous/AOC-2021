#include "utilities.h"

int part1(char* path)
{
    std::ifstream file(path);
    
    std::vector<int> fish;
    fish = ParseCSV(file);

    for (int i = 0; i < 80; i++) {
        int new_fish = 0;
        for (int& f : fish) {
            if (f == 0) {
                f = 6;
                new_fish++;
            } else f--;
        }
        fish.insert(fish.end(), new_fish, 8);
    }

    return fish.size();
}

uint64_t part2(char* path)
{
    std::ifstream file(path);
    
    uint64_t fish[9]{};
    std::vector<int> nums;
    nums = ParseCSV(file);

    for (int num : nums)
        fish[num]++;

    for (int i = 0; i < 256; i++) {
        uint64_t temp = fish[0];
        memmove(fish, fish + 1, 8 * sizeof(uint64_t));
        fish[6] += temp;
        fish[8] = temp;
    }

    uint64_t ans = 0;
    for (int i = 0; i < 9; i++)
        ans += fish[i];
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
    std::cout << "PART 2: " << part2(path) << std::endl;

    if(argc != 2)
        delete[] path;
}