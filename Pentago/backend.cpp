#include "backend.hpp"

Backend::Backend()
{
    amountToWin = 5;
    whosTurn = 1;
    isDotSet = false;

    board.resize(6);
    for (int i = 0; i < board.size(); i++)
    {
        board[i].resize(6);
    }
}

void Backend::setDot(int line, int row)
{
    if (!board[line][row] && !isDotSet)
    {
        board[line][row] = whosTurn;
        isDotSet = true;
    }
}

void Backend::rotate(int part, int deg, bool safe) //1 2  1 - clock, -1 - counterclock
{                                       //3 4
    if (isDotSet || safe)
    {
        vector < vector < int > > chosenPart(board.size() / 2, vector < int >(3));

        int lineLeft, lineRight, rowLeft, rowRight;

        switch (part)
        {
            case 1:
                {
                    lineLeft = 0;
                    lineRight = board.size() / 2;

                    rowLeft = 0;
                    rowRight = board.size() / 2;

                    break;
                }

            case 2:
                {
                    lineLeft = 0;
                    lineRight = board.size() / 2;

                    rowLeft = board.size() / 2;
                    rowRight = board.size();

                    break;
                }

            case 3:
                {
                    lineLeft = board.size() / 2;
                    lineRight = board.size();

                    rowLeft = 0;
                    rowRight = board.size() / 2;
                
                    break;
                }

            case 4:
                {
                    lineLeft = board.size() / 2;
                    lineRight = board.size();

                    rowLeft = board.size() / 2;
                    rowRight = board.size();
                
                    break;
                }
        }
                    
        for (int i = lineLeft; i < lineRight; i++) //performing rotation
        {
            for (int j = rowLeft; j < rowRight; j++)
            {
                switch (deg)
                {
                    case 0:
                        {
                            return;
                        }

                    case 1: //clockwise
                        {
                            chosenPart[j - rowLeft][chosenPart[0].size() - 1 - (i - lineLeft)] = board[i][j];

                            break;
                        }
                
                    case -1: //counterclockwise 
                        {
                            chosenPart[chosenPart.size() - 1 - (j - rowLeft)][i - lineLeft] = board[i][j];

                            break;
                        }

                    case 2:
                        {
                            chosenPart[chosenPart.size() - 1 - (i - lineLeft)][chosenPart[0].size() - 1 - (j - rowLeft)] = board[i][j];

                            break;
                        }
                    
                    case -2:
                        {
                            chosenPart[chosenPart.size() - 1 - (i - lineLeft)][chosenPart[0].size() - 1 - (j - rowLeft)] = board[i][j];

                            break;
                        }
                }
            }
        }
        
        for (int i = 0; i < chosenPart.size(); i++) //copying the data back
        {
            for (int j = 0; j < chosenPart[0].size(); j++)
            {
                board[i + lineLeft][j + rowLeft] = chosenPart[i][j];
            }
        }

        if (!safe)
        {
            whosTurn = whosTurn % 2 + 1;
            isDotSet = false;
        }
    }
}

int Backend::isWin()
{
    bool draw = true;
    bool first = false;
    bool second = false;

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (!board[i][j])
            {
                draw = false;
            }
        }
    }

    if (draw)
    {
        return 4;
    }

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == 0)
            {
                continue;
            }

            for (int k = 0; k < 4; k++)
            {
                int counter = 1;
                int firstElement = board[i][j];

                vector < vector < char > > used(board.size(), vector < char >(board[0].size(), false));

                queue < pair < int, int > > q;

                q.push({i, j});
                used[i][j] = true;

                while (!q.empty())
                {
                    pair < int, int > curXY;
                    curXY = q.front();
                    q.pop();

                    switch (k)
                    {
                        case 0: //row check
                            {
                                //left
                                if (curXY.second > 0 && !used[curXY.first][curXY.second - 1] && board[curXY.first][curXY.second - 1] == firstElement)
                                {
                                    used[curXY.first][curXY.second - 1] = true;
                                    q.push({curXY.first, curXY.second - 1});
                                    counter++;
                                }

                                //right
                                if (curXY.second < board[0].size() - 1 && !used[curXY.first][curXY.second + 1] && board[curXY.first][curXY.second + 1] == firstElement)
                                {
                                    used[curXY.first][curXY.second + 1] = true;
                                    q.push({curXY.first, curXY.second + 1});
                                    counter++;
                                }

                                break;
                            }

                        case 1: //line check
                            {
                                //up
                                if (curXY.first > 0 && !used[curXY.first - 1][curXY.second] && board[curXY.first - 1][curXY.second] == firstElement)
                                {
                                    used[curXY.first - 1][curXY.second] = true;
                                    q.push({curXY.first - 1, curXY.second});
                                    counter++;
                                }

                                //down
                                if (curXY.first < board.size() - 1 && !used[curXY.first + 1][curXY.second] && board[curXY.first + 1][curXY.second] == firstElement)
                                {
                                    used[curXY.first + 1][curXY.second] = true;
                                    q.push({curXY.first + 1, curXY.second});
                                    counter++;
                                }

                                break;
                            }

                        case 2: //main diagonal check
                            {
                                //up
                                if (curXY.first > 0 && curXY.second > 0 && !used[curXY.first - 1][curXY.second - 1] && board[curXY.first - 1][curXY.second - 1] == firstElement)
                                {
                                    used[curXY.first - 1][curXY.second - 1] = true;
                                    q.push({curXY.first - 1, curXY.second - 1});
                                    counter++;
                                }

                                //down
                                if (curXY.first < board.size() - 1 && curXY.second < board[0].size() - 1 && !used[curXY.first + 1][curXY.second + 1] && board[curXY.first + 1][curXY.second + 1] == firstElement)
                                {
                                    used[curXY.first + 1][curXY.second + 1] = true;
                                    q.push({curXY.first + 1, curXY.second + 1});
                                    counter++;
                                }

                                break;
                            }

                        case 3: //sub diagonal check
                            {
                                //up
                                if (curXY.first > 0 && curXY.second < board[0].size() - 1 && !used[curXY.first - 1][curXY.second + 1] && board[curXY.first - 1][curXY.second + 1] == firstElement)
                                {
                                    used[curXY.first - 1][curXY.second + 1] = true;
                                    q.push({curXY.first - 1, curXY.second + 1});
                                    counter++;
                                }

                                //down
                                if (curXY.first < board.size() - 1 && curXY.second > 0 && !used[curXY.first + 1][curXY.second - 1] && board[curXY.first + 1][curXY.second - 1] == firstElement)
                                {
                                    used[curXY.first + 1][curXY.second - 1] = true;
                                    q.push({curXY.first + 1, curXY.second - 1});
                                    counter++;
                                }

                                break;
                            }
                    }
                }

                if (counter >= amountToWin)
                {
                     if (firstElement == 1)
                     {
                        first = true;
                     }
                     else if (firstElement == 2)
                     {
                        second = true;
                     }
                }
            }
        }
    }

    if (first && second)
    {
        return 4;
    }
    else if (first)
    {
        return 1;
    }
    else if (second)
    {
        return 2;
    }

    return 0;
}

void Backend::draw()
{
    cout << setw(8);

    for (int j = 0; j < board[0].size(); j++)
    {
        cout << j << setw(4);
    }

    cout << endl << setw(4);

    for (int j = 0; j < board[0].size() * 4 + 1; j++)
    {
        cout << '-';
    }

    cout << setw(4);

    for (int i = 0; i < board.size(); i++)
    {
        cout << endl << i << setw(3) << "| ";

        for (int j = 0; j < board[0].size(); j++)
        {
            cout << board[i][j] << setw(4);            
        }

        if (i < board.size() - 1)
        {
            cout << endl << setw(6) << '|' << setw(4);
        }
        else
        {
            cout << endl;
        }
    }

    cout << endl;
}

int Backend::getBall(int line, int row)
{
    return board[line][row];
}

bool Backend::getIsDotSet()
{
    return isDotSet;
}

int Backend::getWhosTurn()
{
    return whosTurn;
}

pair < int, int > Backend::getSize()
{
    return {board.size(), board[0].size()};
}

vector < vector < int > > Backend::getBoard()
{
    return board;
}
        
int Backend::getAmountToWin()
{
    return amountToWin;
}

Backend::~Backend(){}
