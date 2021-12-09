#include "utilities.h"

std::pair<int, int> ParseCoordinate(const std::string& coords)
{
    int x = 0, y = 0;
    int i = 0;
    while (coords[i] != ',')
        x = (x * 10) + (coords[i++] - '0');
    i++;
    while (i < coords.size())
        y = (y * 10) + (coords[i++] - '0');
    return { x, y };
}

int part1(char* path)
{
    std::ifstream file(path);
    std::string word;

    int** grid = new int*[1000];
    for (int i = 0; i < 1000; i++) {
        grid[i] = new int[1000];
        memset(grid[i], 0, 1000 * sizeof(int));
    }

    int ans = 0;
    while (file >> word)
    {
        auto [x1, y1] = ParseCoordinate(word);
        file >> word; file >> word;
        auto [x2, y2] = ParseCoordinate(word);

        if (x1 != x2 && y1 != y2)
            continue;

        int min_x = std::min(x1, x2);
        int max_x = std::max(x1, x2);

        int min_y = std::min(y1, y2);
        int max_y = std::max(y1, y2);

        int dx = (x1 != x2);
        int dy = (y1 != y2);

        for (int x = min_x, y = min_y; x <= max_x && y <= max_y; x += dx, y += dy)
            if (grid[y][x]++ == 1)
                ans++;
    }

    for (int i = 0; i < 1000; i++)
        delete[] grid[i];
    delete[] grid;

    return ans;
}

int part2(char* path)
{
    std::ifstream file(path);
    std::string word;

    int** grid = new int*[1000];
    for (int i = 0; i < 1000; i++) {
        grid[i] = new int[1000];
        memset(grid[i], 0, 1000 * sizeof(int));
    }

    int ans = 0;
    while (file >> word)
    {
        auto [x1, y1] = ParseCoordinate(word);
        file >> word; file >> word;
        auto [x2, y2] = ParseCoordinate(word);

        int min_x = std::min(x1, x2);
        int max_x = std::max(x1, x2);

        int min_y = std::min(y1, y2);
        int max_y = std::max(y1, y2);

        int dx = x2 - x1;
        if (dx < 0) dx = -1;
        if (dx > 0) dx =  1;

        int dy = y2 - y1;
        if (dy < 0) dy = -1;
        if (dy > 0) dy =  1;

        for (int x = x1, y = y1; std::clamp(x, min_x, max_x) == x && std::clamp(y, min_y, max_y) == y; x += dx, y += dy)
            if (grid[y][x]++ == 1)
                ans++;
    }

    for (int i = 0; i < 1000; i++)
        delete[] grid[i];
    delete[] grid;

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