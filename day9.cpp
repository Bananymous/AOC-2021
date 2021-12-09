#include "utilities.h"


void ParseFile(const char* path, std::vector<std::vector<int>>& out)
{
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        out.push_back({});
        for (char c : line)
            out.back().push_back(c - '0');
    }
}


int part1(char* path)
{
    std::vector<std::vector<int>> heights;
    ParseFile(path, heights);

    int w = heights[0].size();
    int h = heights.size();

    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            bool isLow = true;
            if (i > 0 && heights[i][j] >= heights[i - 1][j])
                isLow = false;
            if (j > 0 && heights[i][j] >= heights[i][j - 1])
                isLow = false;
            if (i < h - 1 && heights[i][j] >= heights[i + 1][j])
                isLow = false;
            if (j < w - 1 && heights[i][j] >= heights[i][j + 1])
                isLow = false;
            if (isLow)
                ans += heights[i][j] + 1;
        }
    }

    return ans;
}

uint64_t hash(int a, int b) { return (uint64_t)a << 32 | b; }

inline bool hasChecked(const std::unordered_set<uint64_t>& set, int a, int b) 
{
    return set.find(hash(a, b)) != set.end();
}

int part2(char* path)
{
    std::vector<std::vector<int>> heights;
    ParseFile(path, heights);

    int w = heights[0].size();
    int h = heights.size();

    int basins[3]{ 0, 0, 0 };

    std::unordered_set<uint64_t> checked;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (heights[i][j] != 9 && !hasChecked(checked, i, j)) {
                std::unordered_set<uint64_t> basin;
                basin.insert(hash(i, j));
                checked.insert(hash(i, j));

                std::stack<std::pair<int, int>> toCheck;
                toCheck.push({i - 1, j});
                toCheck.push({i, j - 1});
                toCheck.push({i + 1, j});
                toCheck.push({i, j + 1});

                while (!toCheck.empty())
                {
                    auto[x, y] = toCheck.top();
                    toCheck.pop();
                    if (x < 0 || x >= w || y < 0 ||y >= h)
                        continue;
                    if (heights[x][y] == 9)
                        continue;
                    if(!hasChecked(checked, x, y))
                    {
                        checked.insert(hash(x, y));
                        basin.insert(hash(x, y));
                        toCheck.push({x - 1, y    });
                        toCheck.push({x,     y - 1});
                        toCheck.push({x + 1, y    });
                        toCheck.push({x,     y + 1});
                    }
                }

                if (basin.size() > basins[0]) {
                    basins[0] = basin.size();
                    if (basins[0] > basins[1])
                        std::swap(basins[0], basins[1]);
                    if (basins[1] > basins[2])
                        std::swap(basins[1], basins[2]);
                }
            }
        }
    }

    return basins[0] * basins[1] * basins[2];
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