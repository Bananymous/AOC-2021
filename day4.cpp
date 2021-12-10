#include "utilities.h"

struct Board
{
    int cells[5][5]{};

    Board(std::ifstream& stream)
    {
        std::string word;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (!(stream >> word)) {
                    cells[0][0] = -1;
                    return;
                }
                cells[i][j] = std::stoi(word);
            }
        }
    }

    bool Wins()
    {
        for (int i = 0; i < 5; i++) {
            bool h = true;
            bool v = true;
            for (int j = 0; j < 5; j++) {
                if (cells[i][j] != -1)
                    h = false;
                if (cells[j][i] != -1)
                    v = false;
            }
            if (h || v) return true;
        }
        return false;
    }

    void Draw(int val)
    {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (cells[i][j] == val)
                    cells[i][j] = -1;
    }

    int GetSum()
    {
        int sum = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                if (cells[i][j] != -1)
                    sum += cells[i][j];
        return sum;
    }

};

std::vector<Board> LoadBoards(std::ifstream& stream)
{
    std::vector<Board> boards;
    while(true)
    {
        Board board(stream);
        if(board.cells[0][0] == -1)
            break;
        boards.push_back(board);
    }
    return boards;
}

int part1(char* path)
{
    std::vector<int> draws;
    std::vector<Board> boards;

    {
        std::ifstream file(path);
        draws = ParseCSV(file);
        boards = LoadBoards(file);
    }
    
    for (int num : draws) {
        for (Board& board : boards) {
            board.Draw(num);
            if (board.Wins())
                return board.GetSum() * num;
        }
    }
    
    return -1;
}

int part2(char* path)
{
    std::vector<int> draws;
    std::vector<Board> boards;

    {
        std::ifstream file(path);
        draws = ParseCSV(file);
        boards = LoadBoards(file);
    }

    for (int num : draws) {
        for (auto it = boards.begin(); it != boards.end();) {
            it->Draw(num);
            if (it->Wins()) {
                if (boards.size() == 1)
                    return it->GetSum() * num;
                it = boards.erase(it);
            } else it++;
        }
    }

    return -1;
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