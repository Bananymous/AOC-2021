#include "utilities.h"

int ParseFile(const std::string& path, std::vector<std::vector<std::string>>* out_signals, std::vector<std::vector<std::string>>* out_outputs)
{
    std::ifstream file(path);
    std::string line;
    int count = 0;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string word;

        // Get signals
        if (out_signals != nullptr) {
            out_signals->push_back(std::vector<std::string>());
            for (int i = 0; i < 10; i++) {
                ss >> word;
                std::sort(word.begin(), word.end());
                out_signals->back().push_back(word);
            }
        } else for (int i = 0; i < 10; i++) ss >> word;

        // Skip delimiter
        ss >> word;

        // Get outputs
        if (out_outputs != nullptr) {
            out_outputs->push_back(std::vector<std::string>());
            std::vector<std::string> output;
            for (int i = 0; i < 4; i++) {
                ss >> word;
                std::sort(word.begin(), word.end());
                out_outputs->back().push_back(word);
            }
        } else for (int i = 0; i < 4; i++) ss >> word;

        count++;
    }

    return count;
}

bool contains_all(const std::string& str, const std::string& val) {
    for (int i = 0; i < val.size(); i++)
        if (str.find(val[i]) == std::string::npos)
            return false;
    return true;
}

int part1(char* path)
{
    std::vector<std::vector<std::string>> outputs;
    ParseFile(path, nullptr, &outputs);

    int ans = 0;
    for (auto& output : outputs)
        for (auto& digit : output)
            ans += !(digit.size() == 5 || digit.size() == 6);

    return ans;
}

int part2(char* path)
{
    std::vector<std::vector<std::string>> all_signals;
    std::vector<std::vector<std::string>> all_outputs;
    int count = ParseFile(path, &all_signals, &all_outputs);

    int ans = 0;
    for (int i = 0; i < count; i++)
    {
        const auto& signals = all_signals[i];
        const auto& output = all_outputs[i];

        std::unordered_set<std::string> done;
        std::unordered_map<std::string, int> value;
        std::unordered_map<int, std::string> bases;

        // Get 1, 4, 7 and 8 by their string size
        std::vector<std::pair<int, int>> basic({ { 2, 1 }, { 4, 4 }, { 3, 7 }, { 7, 8 } });
        for (const auto& signal : signals) {
            if (done.find(signal) != done.end())
                continue;
            for (const auto& p : basic) {
                if(signal.size() == p.first) {
                    value[signal] = p.second;
                    bases[p.second] = signal;
                    done.insert(signal);
                    break;
                }
            }
        }

        // Assing lambdas for 0, 2, 3, 5, 6, 9
        std::vector<std::pair<int, std::function<bool(const std::string&)>>> checks;
        checks.push_back({ 9, [&](const std::string& str) { return str.size() == 6 && contains_all(str, bases[4]); }});
        checks.push_back({ 0, [&](const std::string& str) { return str.size() == 6 && contains_all(str, bases[7]); }});
        checks.push_back({ 6, [&](const std::string& str) { return str.size() == 6;                                }});
        checks.push_back({ 3, [&](const std::string& str) { return str.size() == 5 && contains_all(str, bases[7]); }});
        checks.push_back({ 5, [&](const std::string& str) { return str.size() == 5 && contains_all(bases[9], str); }});
        checks.push_back({ 2, [&](const std::string& str) { return true;                                           }});

        // Map rest of the signals to their values
        for (const auto& check : checks) {
            for (const auto& signal : signals) {
                if (done.find(signal) != done.end())
                    continue;
                if (!check.second(signal))
                    continue;
                value[signal] = check.first;
                bases[check.first] = signal;
                done.insert(signal);
                break;
            }
        }

        // Calculate the output
        int cur = 0;
        for (const auto& digit : output)
            cur = (cur * 10) + value[digit];
        ans += cur;
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