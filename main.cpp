#include <iostream>
using namespace std;

enum status
{
    X,
    O,
    tie
} win;
enum Player
{
    ai,
    player1,
    player2
} player;
// ai is maximising, player2 is minimising
void printboard(char board[3][3])
{
    cout << flush;
    cout << "#################\n";
    for (int i = 0; i < 3; i++)
    {
        cout << board[i][0] << "|" << board[i][1] << "|" << board[i][2] << endl;
    }
    cout << "#################\n";
}
bool check_end(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        int num = board[i][0];
        if (board[i][1] == num && board[i][2] == num && num != ' ')
        {
            if (num == 'X')
                win = X;
            else
                win = O;
            return true;
        }
        num = board[0][i];
        if (board[1][i] == num && board[2][i] == num && num != ' ')
        {
            if (num == 'X')
                win = X;
            else
                win = O;
            return true;
        }
    }
    int num = board[0][0];
    if (board[1][1] == num && board[2][2] == num && num != ' ')
    {
        if (num == 'X')
            win = X;
        else
            win = O;
        return true;
    }
    num = board[0][2];
    if (board[1][1] == num && board[2][0] == num && num != ' ')
    {
        if (num == 'X')
            win = X;
        else
            win = O;
        return true;
    }
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                flag = 1;
            }
        }
    }
    if (flag == 1)
    {
        return false;
    }
    else
    {
        win = tie;
        return true;
    }
}
int minimax(char board[3][3], bool is_maximising)
{
    if (check_end(board))
    {
        if (win == X)
        {
            return 10;
        }
        else if (win == O)
        {
            return -10;
        }
        else
        {
            return 0;
        }
        cout << "winner is : " << win << endl;
    }
    // printboard(board);
    // cout << "depth : " << depth << endl;
    if (is_maximising)
    {
        int max = -INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'X';
                    int val = minimax(board, false);
                    if (val > max)
                    {
                        max = val;
                    }
                    board[i][j] = ' ';
                }
            }
        }
        return max;
    }
    else
    {
        int min = INT_MAX;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = 'O';
                    int val = minimax(board, true);
                    if (val < min)
                    {
                        min = val;
                    }
                    board[i][j] = ' ';
                }
            }
        }
        return min;
    }
}
pair<int, int> bestmove(char board[3][3])
{
    int max = -INT_MAX;
    int row = -1, col = -1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'X';
                int val = minimax(board, false);
                if (val > max)
                {
                    max = val;
                    row = i;
                    col = j;
                }
                board[i][j] = ' ';
            }
        }
    }
    cout << row << " " << col << endl;
    return {row, col};
}

int main()
{
    char board[3][3];
    for (int i = 0; i < 3; i++)
    {
        board[i][0] = ' ';
        board[i][1] = ' ';
        board[i][2] = ' ';
    }
    printboard(board);
    cout << "Choose gameplay mode\n 0 - Player vs Player\n 1 - Player vs Bot\n";
    int mode;
    cin >> mode;
    if (mode == 0)
    {
        player = player1;
        while (!check_end(board))
        {
            if (player == player1)
            {
                cout << "player1 plays" << endl;
                int x, y;
                cin >> x >> y;
                if (x > 3 || y > 3 || x < 1 || y < 1)
                {
                    cout << "invalid input\n";
                    continue;
                }
                board[x - 1][y - 1] = 'X';
                player = ai;
            }
            else
            {
                cout << "player2 plays" << endl;
                int x, y;
                cin >> x >> y;
                if (x > 3 || y > 3 || x < 1 || y < 1)
                {
                    cout << "invalid input\n";
                    continue;
                }
                board[x - 1][y - 1] = 'O';
                player = ai;
            }
            printboard(board);
        }
        if (win == X)
            cout << "player1 wins\n";
        else if (win == O)
            cout << "player2 wins\n";
        else
            cout << "TIE\n";
        cout << "end\n";
    }
    else
    {
        player = ai;
        while (!check_end(board))
        {
            if (player == ai)
            {
                cout << "ai plays" << endl;
                pair<int, int> move;
                move = bestmove(board);
                board[move.first][move.second] = 'X';
                player = player2;
            }
            else
            {
                cout << "player2 plays" << endl;
                int x, y;
                cin >> x >> y;
                if (x > 3 || y > 3 || x < 1 || y < 1)
                {
                    cout << "invalid input\n";
                    continue;
                }
                board[x - 1][y - 1] = 'O';
                player = ai;
            }
            printboard(board);
        }
        if (win == X)
            cout << "ai wins\n";
        else if (win == O)
            cout << "human wins\n";
        else
            cout << "TIE\n";
        cout << "end\n";
    }
}