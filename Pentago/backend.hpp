#include <iostream>
#include <vector>
#include <iomanip>
#include <queue>

using namespace std;

class Backend
{
    private:
        vector < vector < int > > board;

        int amountToWin;
        int whosTurn;
        bool isDotSet;

    public:
        Backend();
    
        void setDot(int line, int row);
        void rotate(int part, int deg, bool safe = false);
        int isWin();

        void draw();

        int getBall(int line, int row);
        bool getIsDotSet();
        int getWhosTurn();
        pair < int, int > getSize();
        vector < vector < int > > getBoard();
        int getAmountToWin();
    
        ~Backend();
};
