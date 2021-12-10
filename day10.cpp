#include "utilities.h"

int64_t isValid(const std::string& str, std::stack<char>& out)
{
    std::unordered_map<char, char>    valid = { { ')', '(' }, { ']', '[' }, { '}',  '{' }, { '>',   '<' } };
    std::unordered_map<char, int64_t> value = { { ')',   3 }, { ']',  57 }, { '}', 1197 }, { '>', 25137 } };

    for (int i = 0; i < str.size(); i++) {
        switch (str[i]) {
            case '(': case '[': case '{': case '<':
                out.push(str[i]);
                break;
            default:
                if (out.empty() || out.top() != valid[str[i]])
                    return value[str[i]];
                out.pop();
                break;
        }
    }

    return 0;
}

int64_t part1(const char* path)
{
    std::ifstream file(path);
    int64_t ans = 0;
    std::string line;
    while (file >> line) {
        std::stack<char> s;
        ans += isValid(line, s);
    }
    return ans;
}

int64_t part2(const char* path)
{
    std::ifstream file(path);
    std::vector<int64_t> ans;
    std::string line;

    std::unordered_map<char, int64_t> value = { { '(', 1}, { '[', 2 }, { '{', 3 }, { '<', 4 } };

    while (file >> line) {
        std::stack<char> s;
        if (!isValid(line, s)) {
            int64_t cur = 0;
            while (!s.empty()) {
                cur *= 5;
                cur += value[s.top()];
                s.pop();
            }
            ans.push_back(cur);
        }
    }

    std::sort(ans.begin(), ans.end());

    return ans[ans.size() / 2];
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

    printf("PART 1: %lli\n", part1(path));
    printf("PART 2: %lli\n", part2(path));

    if(argc != 2)
        delete[] path;
}