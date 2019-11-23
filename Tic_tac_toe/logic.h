#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

class Logic
{
    private: 
        vector < vector < char > > board;
        int whose_turn;
        int amount_to_win;
        int width;
        int height;

    public:
        Logic(int size_x, int size_y, int num);

        bool sign(int lin, int col);

        void unsign(int lin, int col);

        void newgame();
        
        int whatcell(int lin, int col);

        int turn();

        pair < int, int > size();

        int iswin(int lin, int col);

        void operator= (const Logic &b);

        void display();

        ~Logic();
};

#endif
