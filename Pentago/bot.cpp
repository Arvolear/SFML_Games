#include "backend.hpp"
#include "bot.hpp"

Bot::Bot(int color, int amountToWin)
{
    this->ordNum = color;
    this->firstTurn = true;
    
    this->amountToWin = amountToWin;
}

void Bot::rotate(vector < vector < int > > &localB, int part, int deg)
{
    if (deg == 0)
    {
        return;
    }

    vector < vector < int > > chosenPart(localB.size() / 2, vector < int >(3));

    int lineLeft, lineRight, rowLeft, rowRight;

    switch (part)
    {
        case 1:
            {
                lineLeft = 0;
                lineRight = localB.size() / 2;

                rowLeft = 0;
                rowRight = localB.size() / 2;

                break;
            }

        case 2:
            {
                lineLeft = 0;
                lineRight = localB.size() / 2;

                rowLeft = localB.size() / 2;
                rowRight = localB.size();

                break;
            }

        case 3:
            {
                lineLeft = localB.size() / 2;
                lineRight = localB.size();

                rowLeft = 0;
                rowRight = localB.size() / 2;

                break;
            }

        case 4:
            {
                lineLeft = localB.size() / 2;
                lineRight = localB.size();

                rowLeft = localB.size() / 2;
                rowRight = localB.size();

                break;
            }
    }

    for (int i = lineLeft; i < lineRight; i++) //performing rotation
    {
        for (int j = rowLeft; j < rowRight; j++)
        {
            if (deg == 1) //clockwise
            {
                chosenPart[j - rowLeft][chosenPart[0].size() - 1 - (i - lineLeft)] = localB[i][j];
            }
            else if (deg == -1) //counterclockwise 
            {
                chosenPart[chosenPart.size() - 1 - (j - rowLeft)][i - lineLeft] = localB[i][j];
            }
        }
    }

    for (int i = 0; i < chosenPart.size(); i++) //copying the data back
    {
        for (int j = 0; j < chosenPart[0].size(); j++)
        {
            localB[i + lineLeft][j + rowLeft] = chosenPart[i][j];
        }
    }
}
        
Answer Bot::getRightAnswer(vector < vector < int > > localB, int line, int row, int part, int deg)
{
    localB[line][row] = -1;

    rotate(localB, part, -1 * deg);

    for (int i = 0; i < localB.size(); i++)
    {
        for (int j = 0; j < localB[i].size(); j++)
        {
            if (localB[i][j] == -1)
            {
                return {i, j, part, deg};
            }
        }
    }

    return {-1, -1, 0, 0};
}
        
Answer Bot::getEmptyCell(vector < vector < int > > &localB)
{
    srand(time(0));
    int firstTurnChoosen = 0;

    vector < pair < int, int > > random;

    for (int i = 0; i < localB.size(); i++)
    {
        for (int j = 0; j < localB[i].size(); j++)
        {
            if (firstTurn)
            {
                if ((i == 1 || i == 4) && (j == 1 || j == 4))
                {
                    if (localB[i][j] == 0)
                    {
                        random.push_back({i, j});
                    }
                }
            }
            else
            {
                if (localB[i][j] == 0)
                {
                    random.push_back({i, j});
                }
            }
        }
    }

    int cell = rand() % random.size();

    int choosen = firstTurn ? 1 + 2 * (random[cell].first / 3) + random[cell].second / 3 : 0;

    int part = choosen;
    while (part == choosen)
    {
        part = 1 + rand() % 4;
    }

    int deg = 0;
    
    if (int(rand()) - int(RAND_MAX / 2) <= 0)
    {
        deg = -1;
    }
    else
    {  
        deg = 1; 
    }

    firstTurn = false;
    return {random[cell].first, random[cell].second, part, deg};
}

pair < int, int > Bot::calcMaxLength(vector < vector < int > > &board, int color, bool calcEmpty, int li, int ri, int lj, int rj)
{
    int MAX = -1;
    int whole = 0;

    for (int i = li; i < ri; i++) //lines
    {
        for (int j = lj; j < rj; j++) //rows
        {
            if (board[i][j] != color)
            {
                continue;
            }

            for (int k = 0; k < 4; k++)
            {
                int counter = 1;
                int mult = 1;
                bool chooseOne = true;
                bool chooseTwo = true;

                vector < vector < int > > used(board.size(), vector < int >(board[0].size(), false));

                queue < pair < int, int > > q;

                q.push({i, j});
                used[i][j] = true;

                while (!q.empty())
                {
                    bool ok = true;
                    pair < int, int > curXY;
                    curXY = q.front();
                    q.pop();

                    switch (k)
                    {
                        case 0: //row check
                            {
                                //left
                                if (ok && calcEmpty && chooseOne && curXY.second > 0 && !used[curXY.first][curXY.second - 1] && board[curXY.first][curXY.second - 1] == 0)
                                {
                                    chooseOne = false;
                                    ok = false;

                                    used[curXY.first][curXY.second - 1] = true;
                                    q.push({curXY.first, curXY.second - 1});
                                    
                                    counter += mult;
                                    mult = 1;
                                }

                                if (curXY.second > 0 && !used[curXY.first][curXY.second - 1] && board[curXY.first][curXY.second - 1] == color)
                                {
                                    used[curXY.first][curXY.second - 1] = true;
                                    q.push({curXY.first, curXY.second - 1});
                                
                                    mult *= 2;
                                }

                                //right
                                if (ok && calcEmpty && chooseTwo && curXY.second < board[0].size() - 1 && !used[curXY.first][curXY.second + 1] && board[curXY.first][curXY.second + 1] == 0)
                                {
                                    chooseTwo = false;
                                    ok = false;

                                    used[curXY.first][curXY.second + 1] = true;
                                    q.push({curXY.first, curXY.second + 1});
                                    
                                    counter += mult;
                                    mult = 1;
                                }

                                if (curXY.second < board[0].size() - 1 && !used[curXY.first][curXY.second + 1] && board[curXY.first][curXY.second + 1] == color)
                                {
                                    used[curXY.first][curXY.second + 1] = true;
                                    q.push({curXY.first, curXY.second + 1});
                                
                                    mult *= 2;
                                }

                                break;
                            }

                        case 1: //line check
                            {
                                //up
                                if (ok && calcEmpty && chooseOne && curXY.first > 0 && !used[curXY.first - 1][curXY.second] && board[curXY.first - 1][curXY.second] == 0)
                                {
                                    chooseOne = false;
                                    ok = false;

                                    used[curXY.first - 1][curXY.second] = true;
                                    q.push({curXY.first - 1, curXY.second});
                                    
                                    counter += mult;
                                    mult = 1;
                                }

                                if (curXY.first > 0 && !used[curXY.first - 1][curXY.second] && board[curXY.first - 1][curXY.second] == color)
                                {
                                    used[curXY.first - 1][curXY.second] = true;
                                    q.push({curXY.first - 1, curXY.second});
                                    
                                    mult *= 2;
                                }

                                //down
                                if (ok && calcEmpty && chooseTwo && curXY.first < board.size() - 1 && !used[curXY.first + 1][curXY.second] && board[curXY.first + 1][curXY.second] == 0)
                                {
                                    chooseTwo = false;
                                    ok = false;

                                    used[curXY.first + 1][curXY.second] = true;
                                    q.push({curXY.first + 1, curXY.second});
                                    
                                    counter += mult;
                                    mult = 1;
                                }

                                if (curXY.first < board.size() - 1 && !used[curXY.first + 1][curXY.second] && board[curXY.first + 1][curXY.second] == color)
                                {
                                    used[curXY.first + 1][curXY.second] = true;
                                    q.push({curXY.first + 1, curXY.second});
                                    
                                    mult *= 2;
                                }

                                break;
                            }

                        case 2: //main diagonal check
                            {
                                //up
                                if (ok && calcEmpty && chooseOne && curXY.first > 0 && curXY.second > 0 && !used[curXY.first - 1][curXY.second - 1] && board[curXY.first - 1][curXY.second - 1] == 0)
                                {
                                    chooseOne = false;
                                    ok = false;

                                    used[curXY.first - 1][curXY.second - 1] = true;
                                    q.push({curXY.first - 1, curXY.second - 1});
                                    counter += mult;
                                    mult = 1;
                                }

                                if (curXY.first > 0 && curXY.second > 0 && !used[curXY.first - 1][curXY.second - 1] && board[curXY.first - 1][curXY.second - 1] == color)
                                {
                                    used[curXY.first - 1][curXY.second - 1] = true;
                                    q.push({curXY.first - 1, curXY.second - 1});
                                    mult *= 2;
                                }

                                //down
                                if (ok && calcEmpty && chooseTwo && curXY.first < board.size() - 1 && curXY.second < board[0].size() - 1 && !used[curXY.first + 1][curXY.second + 1] && board[curXY.first + 1][curXY.second + 1] == 0)
                                {
                                    chooseTwo = false;
                                    ok = false;

                                    used[curXY.first + 1][curXY.second + 1] = true;
                                    q.push({curXY.first + 1, curXY.second + 1});
                                    counter += mult;
                                    mult = 1;
                                }

                                if (curXY.first < board.size() - 1 && curXY.second < board[0].size() - 1 && !used[curXY.first + 1][curXY.second + 1] && board[curXY.first + 1][curXY.second + 1] == color)
                                {
                                    used[curXY.first + 1][curXY.second + 1] = true;
                                    q.push({curXY.first + 1, curXY.second + 1});
                                    mult *= 2;
                                }

                                break;
                            }

                        case 3: //sub diagonal check
                            {
                                //up
                                if (ok && calcEmpty && chooseOne && curXY.first > 0 && curXY.second < board[0].size() - 1 && !used[curXY.first - 1][curXY.second + 1] && board[curXY.first - 1][curXY.second + 1] == color)
                                {
                                    chooseOne = false;
                                    ok = false;

                                    used[curXY.first - 1][curXY.second + 1] = true;
                                    q.push({curXY.first - 1, curXY.second + 1});
                                    counter += mult;
                                    mult = 1;
                                }

                                if (curXY.first > 0 && curXY.second < board[0].size() - 1 && !used[curXY.first - 1][curXY.second + 1] && board[curXY.first - 1][curXY.second + 1] == color)
                                {
                                    used[curXY.first - 1][curXY.second + 1] = true;
                                    q.push({curXY.first - 1, curXY.second + 1});
                                    mult *= 2;
                                }

                                //down
                                if (ok && calcEmpty && chooseTwo && curXY.first < board.size() - 1 && curXY.second > 0 && !used[curXY.first + 1][curXY.second - 1] && board[curXY.first + 1][curXY.second - 1] == color)
                                {
                                    chooseTwo = false;
                                    ok = false;

                                    used[curXY.first + 1][curXY.second - 1] = true;
                                    q.push({curXY.first + 1, curXY.second - 1});
                                    counter += mult;
                                    mult = 1;
                                }

                                if (curXY.first < board.size() - 1 && curXY.second > 0 && !used[curXY.first + 1][curXY.second - 1] && board[curXY.first + 1][curXY.second - 1] == color)
                                {
                                    used[curXY.first + 1][curXY.second - 1] = true;
                                    q.push({curXY.first + 1, curXY.second - 1});
                                    mult *= 2;
                                }

                                break;
                            }

                    }

                    whole += counter;
                    //cout << "CO " << counter << endl;
                    //counter += mult;
                    
                    if (counter > MAX)
                    {
                        /*for (int q = 0; q < used.size(); q++)
                        {
                            for (int w = 0; w < used[q].size(); w++)
                            {
                                cout << used[q][w];
                            }
                            cout << endl;
                        }
                        cout << endl;*/

                        MAX = counter;
                    }
                } 
            }
        }
    }

    return {MAX, whole};
}

bool Bot::findOpened(vector < vector < int > > &board, int color, int desiredAmount)
{
    vector < vector < int > > tmpB;

    for (int p = 1; p < 5; p++) //parts
    {
        for (int l = -1; l <= 1; l++) //degs
        {
            tmpB = board;

            if (desiredAmount < amountToWin)
            {
                if (l == 0)
                {
                    l++;
                }
            }

            rotate(tmpB, p, l);

            for (int i = 0; i < tmpB.size(); i++) //lines
            {
                for (int j = 0; j < tmpB[0].size(); j++) //rows
                {   
                    if (tmpB[i][j] != color)
                    {
                        continue;
                    }

                    for (int k = 0; k < 4; k++)
                    {
                        int counter = 1;
                        bool chooseOne = true;
                        bool chooseTwo = true;

                        vector < vector < int > > used(tmpB.size(), vector < int >(tmpB[0].size(), false));

                        queue < pair < int, int > > q;

                        q.push({i, j});
                        used[i][j] = true;

                        while (!q.empty())
                        {
                            pair < int, int > curXY;
                            bool ok = true;
                            curXY = q.front();
                            q.pop();

                            switch (k)
                            {
                                case 0: //row check
                                    {
                                        //left
                                        if (ok && chooseOne && curXY.second > 0 && !used[curXY.first][curXY.second - 1] && tmpB[curXY.first][curXY.second - 1] == 0)
                                        {
                                            chooseOne = false;
                                            ok = false;

                                            used[curXY.first][curXY.second - 1] = true;
                                            q.push({curXY.first, curXY.second - 1});
                                            answer = getRightAnswer(tmpB, curXY.first, curXY.second - 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.second > 0 && !used[curXY.first][curXY.second - 1] && tmpB[curXY.first][curXY.second - 1] == color)
                                        {
                                            used[curXY.first][curXY.second - 1] = true;
                                            q.push({curXY.first, curXY.second - 1});
                                            counter++;
                                        }

                                        //right
                                        if (ok && chooseTwo && curXY.second < tmpB[0].size() - 1 && !used[curXY.first][curXY.second + 1] && tmpB[curXY.first][curXY.second + 1] == 0)
                                        {
                                            chooseTwo = false;
                                            ok = false;

                                            used[curXY.first][curXY.second + 1] = true;
                                            q.push({curXY.first, curXY.second + 1});
                                            answer = getRightAnswer(tmpB, curXY.first, curXY.second + 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.second < tmpB[0].size() - 1 && !used[curXY.first][curXY.second + 1] && tmpB[curXY.first][curXY.second + 1] == color)
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
                                        if (ok && chooseOne && curXY.first > 0 && !used[curXY.first - 1][curXY.second] && tmpB[curXY.first - 1][curXY.second] == 0)
                                        {
                                            chooseOne = false;
                                            ok = false;

                                            used[curXY.first - 1][curXY.second] = true;
                                            q.push({curXY.first - 1, curXY.second});
                                            answer = getRightAnswer(tmpB, curXY.first - 1, curXY.second, p, l);
                                            counter++;
                                        }

                                        if (curXY.first > 0 && !used[curXY.first - 1][curXY.second] && tmpB[curXY.first - 1][curXY.second] == color)
                                        {
                                            used[curXY.first - 1][curXY.second] = true;
                                            q.push({curXY.first - 1, curXY.second});
                                            counter++;
                                        }

                                        //down
                                        if (ok && chooseTwo && curXY.first < tmpB.size() - 1 && !used[curXY.first + 1][curXY.second] && tmpB[curXY.first + 1][curXY.second] == 0)
                                        {
                                            chooseTwo = false;
                                            ok = false;

                                            used[curXY.first + 1][curXY.second] = true;
                                            q.push({curXY.first + 1, curXY.second});
                                            answer = getRightAnswer(tmpB, curXY.first + 1, curXY.second, p, l);
                                            counter++;
                                        }

                                        if (curXY.first < tmpB.size() - 1 && !used[curXY.first + 1][curXY.second] && tmpB[curXY.first + 1][curXY.second] == color)
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
                                        if (ok && chooseOne && curXY.first > 0 && curXY.second > 0 && !used[curXY.first - 1][curXY.second - 1] && tmpB[curXY.first - 1][curXY.second - 1] == 0)
                                        {
                                            chooseOne = false;
                                            ok = false;

                                            used[curXY.first - 1][curXY.second - 1] = true;
                                            q.push({curXY.first - 1, curXY.second - 1});
                                            answer = getRightAnswer(tmpB, curXY.first - 1, curXY.second - 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.first > 0 && curXY.second > 0 && !used[curXY.first - 1][curXY.second - 1] && tmpB[curXY.first - 1][curXY.second - 1] == color)
                                        {
                                            used[curXY.first - 1][curXY.second - 1] = true;
                                            q.push({curXY.first - 1, curXY.second - 1});
                                            counter++;
                                        }

                                        //down
                                        if (ok && chooseTwo && curXY.first < tmpB.size() - 1 && curXY.second < tmpB[0].size() - 1 && !used[curXY.first + 1][curXY.second + 1] && tmpB[curXY.first + 1][curXY.second + 1] == 0)
                                        {
                                            chooseTwo = false;
                                            ok = false;

                                            used[curXY.first + 1][curXY.second + 1] = true;
                                            q.push({curXY.first + 1, curXY.second + 1});
                                            answer = getRightAnswer(tmpB, curXY.first + 1, curXY.second + 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.first < tmpB.size() - 1 && curXY.second < tmpB[0].size() - 1 && !used[curXY.first + 1][curXY.second + 1] && tmpB[curXY.first + 1][curXY.second + 1] == color)
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
                                        if (ok && chooseOne && curXY.first > 0 && curXY.second < tmpB[0].size() - 1 && !used[curXY.first - 1][curXY.second + 1] && tmpB[curXY.first - 1][curXY.second + 1] == 0)
                                        {
                                            chooseOne = false;
                                            ok = false;

                                            used[curXY.first - 1][curXY.second + 1] = true;
                                            q.push({curXY.first - 1, curXY.second + 1});
                                            answer = getRightAnswer(tmpB, curXY.first - 1, curXY.second + 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.first > 0 && curXY.second < tmpB[0].size() - 1 && !used[curXY.first - 1][curXY.second + 1] && tmpB[curXY.first - 1][curXY.second + 1] == color)
                                        {
                                            used[curXY.first - 1][curXY.second + 1] = true;
                                            q.push({curXY.first - 1, curXY.second + 1});
                                            counter++;
                                        }

                                        //down
                                        if (ok && chooseTwo && curXY.first < tmpB.size() - 1 && curXY.second > 0 && !used[curXY.first + 1][curXY.second - 1] && tmpB[curXY.first + 1][curXY.second - 1] == 0)
                                        {
                                            chooseTwo = false;
                                            ok = false;

                                            used[curXY.first + 1][curXY.second - 1] = true;
                                            q.push({curXY.first + 1, curXY.second - 1});
                                            answer = getRightAnswer(tmpB, curXY.first + 1, curXY.second - 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.first < tmpB.size() - 1 && curXY.second > 0 && !used[curXY.first + 1][curXY.second - 1] && tmpB[curXY.first + 1][curXY.second - 1] == color)
                                        {
                                            used[curXY.first + 1][curXY.second - 1] = true;
                                            q.push({curXY.first + 1, curXY.second - 1});
                                            counter++;
                                        }

                                        break;
                                    }
                            }

                            //cout << "CO " << counter << endl << p << ' ' << l << ' ' << i << ' ' << j << endl;

                            if (counter > desiredAmount)
                            {
                                return true;
                            }
                        } 
                    }
                }
            }
        }
    }

    return false;
}

bool Bot::canColorWin(vector < vector < int > > &board, int color, int desiredAmount)
{
    vector < vector < int > > tmpB;

    for (int p = 1; p < 5; p++) //parts
    {
        for (int l = -1; l <= 1; l++) //degs
        {
            tmpB = board;

            if (desiredAmount < amountToWin)
            {
                if (l == 0)
                {
                    l++;
                }
            }

            rotate(tmpB, p, l);

            for (int i = 0; i < tmpB.size(); i++) //lines
            {
                for (int j = 0; j < tmpB[0].size(); j++) //rows
                {
                    if (tmpB[i][j] == 0 || tmpB[i][j] != color)
                    {
                        continue;
                    }

                    for (int k = 0; k < 4; k++)
                    {
                        int counter = 1;
                        bool chooseEmpty = true;

                        vector < vector < char > > used(tmpB.size(), vector < char >(tmpB[0].size(), false));

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
                                        if (chooseEmpty && curXY.second > 0 && !used[curXY.first][curXY.second - 1] && tmpB[curXY.first][curXY.second - 1] == 0)
                                        {
                                            chooseEmpty = false;
                                            used[curXY.first][curXY.second - 1] = true;
                                            q.push({curXY.first, curXY.second - 1});
                                            answer = getRightAnswer(tmpB, curXY.first, curXY.second - 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.second > 0 && !used[curXY.first][curXY.second - 1] && tmpB[curXY.first][curXY.second - 1] == color)
                                        {
                                            used[curXY.first][curXY.second - 1] = true;
                                            q.push({curXY.first, curXY.second - 1});
                                            counter++;
                                        }

                                        //right
                                        if (chooseEmpty && curXY.second < tmpB[0].size() - 1 && !used[curXY.first][curXY.second + 1] && tmpB[curXY.first][curXY.second + 1] == 0)
                                        {
                                            chooseEmpty = false;
                                            used[curXY.first][curXY.second + 1] = true;
                                            q.push({curXY.first, curXY.second + 1});
                                            answer = getRightAnswer(tmpB, curXY.first, curXY.second + 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.second < tmpB[0].size() - 1 && !used[curXY.first][curXY.second + 1] && tmpB[curXY.first][curXY.second + 1] == color)
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
                                        if (chooseEmpty && curXY.first > 0 && !used[curXY.first - 1][curXY.second] && tmpB[curXY.first - 1][curXY.second] == 0)
                                        {
                                            chooseEmpty = false;
                                            used[curXY.first - 1][curXY.second] = true;
                                            q.push({curXY.first - 1, curXY.second});
                                            answer = getRightAnswer(tmpB, curXY.first - 1, curXY.second, p, l);
                                            counter++;
                                        }

                                        if (curXY.first > 0 && !used[curXY.first - 1][curXY.second] && tmpB[curXY.first - 1][curXY.second] == color)
                                        {
                                            used[curXY.first - 1][curXY.second] = true;
                                            q.push({curXY.first - 1, curXY.second});
                                            counter++;
                                        }

                                        //down
                                        if (chooseEmpty && curXY.first < tmpB.size() - 1 && !used[curXY.first + 1][curXY.second] && tmpB[curXY.first + 1][curXY.second] == 0)
                                        {
                                            chooseEmpty = false;
                                            used[curXY.first + 1][curXY.second] = true;
                                            q.push({curXY.first + 1, curXY.second});
                                            answer = getRightAnswer(tmpB, curXY.first + 1, curXY.second, p, l);
                                            counter++;
                                        }

                                        if (curXY.first < tmpB.size() - 1 && !used[curXY.first + 1][curXY.second] && tmpB[curXY.first + 1][curXY.second] == color)
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
                                        if (chooseEmpty && curXY.first > 0 && curXY.second > 0 && !used[curXY.first - 1][curXY.second - 1] && tmpB[curXY.first - 1][curXY.second - 1] == 0)
                                        {
                                            chooseEmpty = false;
                                            used[curXY.first - 1][curXY.second - 1] = true;
                                            q.push({curXY.first - 1, curXY.second - 1});
                                            answer = getRightAnswer(tmpB, curXY.first - 1, curXY.second - 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.first > 0 && curXY.second > 0 && !used[curXY.first - 1][curXY.second - 1] && tmpB[curXY.first - 1][curXY.second - 1] == color)
                                        {
                                            used[curXY.first - 1][curXY.second - 1] = true;
                                            q.push({curXY.first - 1, curXY.second - 1});
                                            counter++;
                                        }

                                        //down
                                        if (chooseEmpty && curXY.first < tmpB.size() - 1 && curXY.second < tmpB[0].size() - 1 && !used[curXY.first + 1][curXY.second + 1] && tmpB[curXY.first + 1][curXY.second + 1] == 0)
                                        {
                                            chooseEmpty = false;
                                            used[curXY.first + 1][curXY.second + 1] = true;
                                            q.push({curXY.first + 1, curXY.second + 1});
                                            answer = getRightAnswer(tmpB, curXY.first + 1, curXY.second + 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.first < tmpB.size() - 1 && curXY.second < tmpB[0].size() - 1 && !used[curXY.first + 1][curXY.second + 1] && tmpB[curXY.first + 1][curXY.second + 1] == color)
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
                                        if (chooseEmpty && curXY.first > 0 && curXY.second < tmpB[0].size() - 1 && !used[curXY.first - 1][curXY.second + 1] && tmpB[curXY.first - 1][curXY.second + 1] == 0)
                                        {
                                            chooseEmpty = false;
                                            used[curXY.first - 1][curXY.second + 1] = true;
                                            q.push({curXY.first - 1, curXY.second + 1});
                                            answer = getRightAnswer(tmpB, curXY.first - 1, curXY.second + 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.first > 0 && curXY.second < tmpB[0].size() - 1 && !used[curXY.first - 1][curXY.second + 1] && tmpB[curXY.first - 1][curXY.second + 1] == color)
                                        {
                                            used[curXY.first - 1][curXY.second + 1] = true;
                                            q.push({curXY.first - 1, curXY.second + 1});
                                            counter++;
                                        }

                                        //down
                                        if (chooseEmpty && curXY.first < tmpB.size() - 1 && curXY.second < 0 && !used[curXY.first + 1][curXY.second - 1] && tmpB[curXY.first + 1][curXY.second - 1] == 0)
                                        {
                                            chooseEmpty = false;
                                            used[curXY.first + 1][curXY.second - 1] = true;
                                            q.push({curXY.first + 1, curXY.second - 1});
                                            answer = getRightAnswer(tmpB, curXY.first + 1, curXY.second - 1, p, l);
                                            counter++;
                                        }

                                        if (curXY.first < tmpB.size() - 1 && curXY.second > 0 && !used[curXY.first + 1][curXY.second - 1] && tmpB[curXY.first + 1][curXY.second - 1] == color)
                                        {
                                            used[curXY.first + 1][curXY.second - 1] = true;
                                            q.push({curXY.first + 1, curXY.second - 1});
                                            counter++;
                                        }

                                        break;
                                    }
                            }

                            //cout << "CO " << counter << endl << p << ' ' << l << ' ' << i << ' ' << j << endl;

                            if (counter >= desiredAmount)
                            {
                                return true;
                            }
                        } 
                    }
                }
            }
        }
    }

    return false;
}

bool Bot::move(vector < vector < int > > &board, int color, int desiredAmount)
{
    if (canColorWin(board, color, amountToWin))
    {
        return true;
    }

    vector < vector < int > > tmpB;
    vector < Answer > bestAnswer;
    vector < Answer > secondBestAnswer;

    for (int i = 0; i < board.size(); i++) //lines
    {
        for (int j = 0; j < board[0].size(); j++) //rows
        {
            if (board[i][j] != 0)
            {
                continue;
            }

            for (int p = 1; p < 5; p++) //parts
            {
                for (int l = -1; l <= 1; l += 2) //degs
                {
                    tmpB = board;
                    tmpB[i][j] = color;
                    rotate(tmpB, p, l);

                    if (!canColorWin(tmpB, (color % 2) + 1, desiredAmount))
                    {
                        secondBestAnswer.push_back({i, j, p, l});

                        if (!findOpened(tmpB, (color % 2) + 1, desiredAmount - 1) || canColorWin(tmpB, color, desiredAmount))
                        {
                            bestAnswer.push_back({i, j, p, l});
                        }
                    }
                }
            }
        }
    }

    if (bestAnswer.empty())
    {
        bestAnswer = secondBestAnswer;
    }

    if (bestAnswer.empty())
    {
        return false;
    }

    int MAX = -1;
    int MAXW = -1;
    int index = -1;

    for (int i = 0; i < bestAnswer.size(); i++)
    {
        tmpB = board;
        tmpB[bestAnswer[i].ansLine][bestAnswer[i].ansRow] = color;
        rotate(tmpB, bestAnswer[i].ansPart, bestAnswer[i].ansAngle);

        pair < int, int > M = calcMaxLength(tmpB, color, true, 0, tmpB.size(), 0, tmpB[0].size());
        
        //cout << "M " << M.first << ' ' << M.second << endl;
        //cout << "ANS " << bestAnswer[i].ansLine << ' ' << bestAnswer[i].ansRow << ' ' << bestAnswer[i].ansPart << ' ' << bestAnswer[i].ansAngle << endl;

        if (findOpened(tmpB, (color % 2) + 1, desiredAmount - 2))
        {
            M.first--;
        }

        if (M.first > MAX || (M.first == MAX && M.second > MAXW))
        {
            MAX = M.first;
            MAXW = M.second;
            index = i;
        }
    }
    //cout << endl;

    answer = bestAnswer[index];
    return true;
}

Answer Bot::getMove(vector < vector < int > > board)
{
    if (!firstTurn)
    {
        if (move(board, ordNum, amountToWin))
        {
            //cout << "Moved\n";
            return answer;
        }
    }

    //cout << "RANDOM\n";
    return getEmptyCell(board);
}

Bot::~Bot(){}
