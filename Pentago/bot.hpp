#pragma once

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

struct Answer
{
    int ansLine, ansRow, ansPart, ansAngle;
};

class Bot
{
    private:
        bool firstTurn;
        int amountToWin;
        int ordNum; // 1 = white, 2 = black

        Answer answer;

        void rotate(vector < vector < int > > &localB, int part, int deg);

        Answer getRightAnswer(vector < vector < int > > localB, int line, int row, int part, int deg);
        Answer getEmptyCell(vector < vector < int > > &localB); 
        
        pair < int, int > calcMaxLength(vector < vector < int > > &board, int color, bool calcEmpty, int li, int ri, int lj, int rj);
        bool findOpened(vector < vector < int > > &board, int color, int desiredAmount);
        bool canColorWin(vector < vector < int > > &board, int color, int desiredAmount);
        bool move(vector < vector < int > > &board, int color, int desiredAmount);

    public:
        Bot(int color, int amountToWin);

        Answer getMove(vector < vector < int > > board);

        ~Bot();
};
