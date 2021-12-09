#include "utilities.h"

int part1(char* path)
{
    std::vector<int> crabs;

    std::ifstream file(path);
    crabs = ParseCSV(file);

    int ans = INT_MAX;
    for (int t = 0; t < 2000; t++) {
        int cur = 0;
        for (int pos : crabs) {
            int dif = abs(pos - t);
            cur += dif;
        }
        if (cur < ans)
            ans = cur;
    }
    
    return ans;
}

int part2(char* path)
{
    std::vector<int> crabs;

    std::ifstream file(path);
    crabs = ParseCSV(file);

    int ans = INT_MAX;
    for (int t = 0; t < 2000; t++) {
        int cur = 0;
        for (int pos : crabs) {
            int dif = abs(pos - t);
            cur += dif * (dif + 1) / 2;
        }
        if (cur < ans)
            ans = cur;
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