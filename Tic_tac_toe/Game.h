#include <iostream>

//#ifndef Game.h
//#define Game.h
//#endif // Game.h

using namespace std;

class Game
{
    string first_player;
    string second_player;
    int first_flag;    //1-X  2-O
    int second_flag;  //1-X  2-O
    int board[9];   //0-NaN   1-X     2-O
    int first_score;
    int second_score;
    int turn_counter=1;
    int strategy=0;       //impossible: 0-win for sure, 1-try to win (middle O)
    /*
    0|1|2
    3|4|5
    6|7|8
    */

public:
    Game();
    void choose_mode();
    void choose_symbol();
    void choose_diff();
    void take_turns();
    void player_turn(bool first);
    void computer_turn();
    void computer_easy();
    void computer_medium();
    void computer_impossible();
    bool block();
    bool try_win();
    void reset();
    bool is_over(int flag, string winner);
    void display_board();
    void display_board_help();
    void display_flags();
    void display_scores();
    //bool empty();
};
