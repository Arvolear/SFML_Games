#include "logic.h"

using namespace std;

Logic::Logic(int size_x, int size_y, int num)
{
    vector < char > temp;

    for (int i = 0; i < size_y; i++)
    {
        for (int j = 0; j < size_x; j++)
        {
            temp.push_back('*');
        }

        board.push_back(temp);
        temp.clear();
    }

    whose_turn = 1;
    amount_to_win = num;
    width = size_x;
    height = size_y;
}

Logic::~Logic(){}

void Logic::operator=(const Logic &b)
{
    whose_turn = b.whose_turn;
    amount_to_win = b.amount_to_win;

    for (int i = 0; i < b.board.size(); i++)
    {
        board.push_back(b.board[i]);
    }
}

bool Logic::sign(int lin, int col)
{
    if (lin <= 0 || lin > board.size() || col <= 0 || col > board[0].size())
    {
        cout << "Error\n";

        return 0;
    }

    if (board[lin - 1][col - 1] == '*')
    {
        if (whose_turn == 1)
            board[lin - 1][col - 1] = 'X';
        else if (whose_turn == 2)
            board[lin - 1][col - 1] = 'O';
    
        whose_turn = whose_turn % 2 + 1;

        return 1;
    }
}

void Logic::unsign(int lin, int col)
{
    if (lin <= 0 || lin > board.size() || col <= 0 || col > board[0].size())
    {
        cout << "Error\n";

        return;
    }

    board[lin - 1][col - 1] = '*';

    whose_turn = whose_turn % 2 + 1;
}

int Logic::whatcell(int lin, int col)
{
    if (board[lin - 1][col - 1] == 'X')
        return 1;
    if (board[lin - 1][col - 1] == 'O')
        return 2;

    return 0;
}

void Logic::newgame()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            board[i][j] = '*';
        }
    }

    whose_turn = 1;
}

int Logic::turn()
{
    return whose_turn;
}

pair < int, int > Logic::size()
{
    return {width, height};
}

int Logic::iswin(int lin, int col)
{
    if (lin <= 0 || lin > board.size() || col <= 0 || col > board[0].size())
    {
        cout << "Error\n";

        return -1;
    }

    for (int z = 0; z < 4; z++)
    {
        char save;

        int counter = 0;

        vector < vector < int > > used(board.size(), vector < int > (board[0].size(), 0));

        queue < pair < int, int > > qu;

        save = board[lin - 1][col - 1];

        if (save == '*')
        {
            return -1;
        }

        used[lin - 1][col - 1] = 1;
        qu.push({lin - 1, col - 1});
        counter++;


        while (!qu.empty())
        {
            int _lin = qu.front().first;
            int _col = qu.front().second;

            
            qu.pop();
            
            if (z == 0)
            {
                if (_lin - 1 >= 0)
                {
                    if (board[_lin - 1][_col] == save)
                    {
                        if (!used[_lin - 1][_col]) 
                        {
                            qu.push({_lin - 1, _col});
                            used[_lin - 1][_col] = 1;
                            counter++;
                        }
                    }
                }

    
                if (_lin + 1 < board.size())
                {
                    if (board[_lin + 1][_col] == save)
                    {
                        if (!used[_lin + 1][_col]) 
                        {
                            qu.push({_lin + 1, _col});
                            used[_lin + 1][_col] = 1;
                            counter++;
                        }
                    }
                }
            }
           


            if (z == 1)
            {
                if (_col - 1 >= 0)
                {
                    if (board[_lin][_col - 1] == save)
                    {
                        if (!used[_lin][_col - 1]) 
                        {
                            qu.push({_lin, (_col - 1)});
                            used[_lin][_col - 1] = 1;
                            counter++;
                        }
                    }
                }

                if (_col + 1 < board[0].size())
                {
                    if (board[_lin][_col + 1] == save)
                    {
                        if (!used[_lin][_col + 1]) 
                        {
                            qu.push({_lin, _col + 1});
                            used[_lin][_col + 1] = 1;
                            counter++;
                        }
                    }
                }

                /*for (int i = 0; i < board.size(); i++)
                {
                    for (int j = 0; j < board[0].size(); j++)
                    {
                        cout << used[i][j];
                    }

                    cout << endl;
                }

                cout << endl;*/
            }



            if (z == 2)
            {
                if (_lin - 1 >= 0 && _col - 1 >= 0)
                {
                    if (board[_lin - 1][_col - 1] == save)
                    {
                        if (!used[_lin - 1][_col - 1]) 
                        {
                            qu.push({_lin - 1, _col - 1});
                            used[_lin - 1][_col - 1] = 1;
                            counter++;
                        }
                    }
                }


                if (_lin + 1 < board.size() && _col + 1 < board[0].size())
                {
                    if (board[_lin + 1][_col + 1] == save)
                    {
                        if (!used[_lin + 1][_col + 1]) 
                        {
                            qu.push({_lin + 1, _col + 1});
                            used[_lin + 1][_col + 1] = 1;
                            counter++;
                        }
                    }
                }
            }



            if (z == 3)
            {
                if (_lin - 1 >= 0 && _col + 1 < board[0].size())
                {
                    if (board[_lin - 1][_col + 1] == save)
                    {
                        if (!used[_lin - 1][_col + 1]) 
                        {
                            qu.push({_lin - 1, _col + 1});
                            used[_lin - 1][_col + 1] = 1;
                            counter++;
                        }
                    }
                }

    
                if (_lin + 1 < board.size() && _col - 1 >= 0)
                {
                    if (board[_lin + 1][_col - 1] == save)
                    {
                        if (!used[_lin + 1][_col - 1]) 
                        {
                            qu.push({_lin + 1, _col - 1});
                            used[_lin + 1][_col - 1] = 1;
                            counter++;
                        }
                    }
                }
            }
        }

    
        if (counter >= amount_to_win)
        {
            if (save == 'X')
                return 1;
            else if (save == 'O')
                return 2;
        }
    }

    bool f = false;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == '*')
                f = true; 
        }
    }

    if (!f)
        return 3;

    return 0;
}

void Logic::display()
{
    for (int j = 0; j < board[0].size(); j++)
        cout << setw(4) << (j + 1);

    cout << endl;

    for (int i = 0; i < board.size(); i++)
    {

        for (int j = 0; j < board[0].size(); j++)
        {
            cout << setw(4) << board[i][j];
        
        }

        cout << setw(4) << (i + 1) << endl;
    }
}
