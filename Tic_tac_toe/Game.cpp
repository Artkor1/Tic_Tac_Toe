#include "Game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <conio.h>
#include <Windows.h>

using namespace std;



Game::Game()
{
    srand(time(NULL));
    first_score=0;
    second_score=0;
    for(int i=0; i<9; i++)
        board[i]=0;
    cout<<"Welcome to the game of Tic-Tac-Toe!"<<endl;
    choose_mode();
    cout<<endl;
    choose_symbol();
    take_turns();
};

void Game::choose_mode()
{
    char mode;
    cout<<"Choose your game mode:"<<endl;
    cout<<"[1]-Player vs Computer\t[2]-Player vs Player"<<endl;
    cout<<"Choice: ";
    cin>>mode;
    if(mode=='2')
    {
        first_player="Player 1";
        second_player="Player 2";
    }
    else
    {
        first_player="Player";
        choose_diff();
    }
}

void Game::choose_diff()
{

    cout<<endl;
    char diff;
    cout<<"Choose computer difficulty:"<<endl;
    cout<<"[1]-Easy\t[2]-Medium\t[3]-Impossible"<<endl;
    cout<<"Choice: ";
    cin>>diff;
    if(diff=='2' || diff=='M' || diff=='m')
    {
        second_player="Computer(medium)";
    }
    else if(diff=='3' || diff=='I' || diff=='i')
    {
        second_player="Computer(impossible)";
    }
    else
    {
        second_player="Computer(easy)";
    }
}

void Game::choose_symbol()
{
    char symbol;
    cout<<"Choose your symbol "<<first_player<<":"<<endl;
    cout<<"[1]-X\t[2]-O\t[3]-Random"<<endl;
    cout<<"Choice: ";
    cin>>symbol;
    if(symbol=='1' || symbol=='X' || symbol=='x')       //X
    {
        first_flag=1;
        second_flag=2;
    }
    else if(symbol=='2' || symbol=='O' || symbol=='o' || symbol =='0')      //O
    {
        first_flag=2;
        second_flag=1;
    }
    else                                    //RANDOM
    {
        int random=rand()% 2;
        if(random==0)
        {
            first_flag=1;
            second_flag=2;
        }
        else
        {
            first_flag=2;
            second_flag=1;
        }
    }
};

void Game::take_turns()
{
    if(first_player=="Player")   //PVE
    {
        if(first_flag==2)
            computer_turn();
        while(1)
        {
            player_turn(true);
            if(is_over(first_flag,"Player"))
                break;
            computer_turn();
            if(is_over(second_flag,"Computer"))
                break;
        }
    }

    else            //PVP
    {
        if(first_flag==2)
            player_turn(false);
        while(1)
        {
            player_turn(true);
            if(is_over(first_flag,"Player 1"))
                break;
            player_turn(false);
            if(is_over(second_flag,"Player 2"))
                break;
        }

    }

    reset();
}

void Game::player_turn(bool first)
{
    system("CLS");
    display_board();
    display_board_help();

    if(first)
    {
        char f=(first_flag==1) ? 'X' : 'O';
        cout<<"It's your turn "<<first_player<<endl<<"Choose a tile to put your "
            << f<<" by typing a number from 1 to 9, as shown above"<<endl<<endl;
    }
    else
    {
        char f=(second_flag==1) ? 'X' : 'O';
        cout<<"It's your turn "<<second_player<<endl<<"Choose a tile to put your "
            << f<<" by typing a number from 1 to 9, as shown above"<<endl<<endl;
    }


    int tile;
    cout<<"Tile: ";
    cin>>tile;
    while(tile<1 || tile>9 || board[tile-1]!=0)
    {
        cout<<"Incorrect choice. Please choose again: ";
        cin>>tile;
    }
    if(first)
        board[tile-1]=first_flag;
    else
        board[tile-1]=second_flag;
};

void Game::computer_turn()
{
    system("CLS");
    display_board();
    display_board_help();

    cout<<"Computer is thinking...";
    Sleep(1200);



    if(second_player=="Computer(easy)")
    {
        computer_easy();
    }

    else if(second_player=="Computer(medium)")
    {
        computer_medium();


    }

    else        //impossible
    {
        computer_impossible();
    }
};

void Game::reset()
{
    turn_counter=1;
    strategy=0;
    display_scores();
    cout<<"Do you want to play again?"<<endl;
    char play;
    cout<<"[1]-PLAY AGAIN\t[2]-CHANGE GAME MODE\t[3]-EXIT"<<endl;
    cout<<"Choice: ";
    cin>>play;
    if(play=='1' || play=='Y' || play=='y' || play=='P' || play=='p')
    {
        system("CLS");
        for(int i=0; i<9; i++)
            board[i]=0;
        choose_symbol();
        take_turns();
    }
    else if(play=='2' || play=='C' || play=='c')
    {
        system("CLS");
        Game();
    }
    else
    {
        cout<<endl<<"Thanks for playing! Goodbye!";
    }
};

bool Game::is_over(int flag, string winner)
{
    if((board[0]==flag && board[1]==flag && board[2]==flag )
            || (board[3]==flag && board[4]==flag && board[5]==flag)
            || (board[6]==flag && board[7]==flag && board[8]==flag)
            || (board[0]==flag && board[3]==flag && board[6]==flag)
            || (board[1]==flag && board[4]==flag && board[7]==flag)
            || (board[2]==flag && board[5]==flag && board[8]==flag)
            || (board[0]==flag && board[4]==flag && board[8]==flag)
            || (board[2]==flag && board[4]==flag && board[6]==flag))
    {
        system("CLS");
        display_board();
        char f=(flag==1) ? 'X' : 'O';
        cout<<f<<" win!"<<endl<<winner<<" wins!\n\n";
        if(winner=="Player" || winner=="Player 1")
            first_score++;
        else
            second_score++;
        return true;
    }
    else if(board[0]!=0 && board[1]!=0 && board[2] !=0
            && board[3]!=0 && board[4]!=0 && board[5] !=0
            && board[6]!=0 && board[7]!=0 && board[8] !=0)
    {
        system("CLS");
        display_board();
        cout<<"Draw!\n\n";
        first_score++;
        second_score++;
        return true;
    }
    return false;
};

void Game::display_board()
{
    display_flags();
    cout<<endl;
    for(int i=0; i<9; i++)
    {
        if(board[i]==1)
            cout<<"X";
        else if(board[i]==2)
            cout<<"O";
        else
            cout<<" ";

        if((i+1)%3!=0)
            cout<<" | ";
        else
            cout<<endl;
        if(i==2 || i==5)
            cout<<"---------"<<endl;
    }
    cout<<endl;
};

void Game::display_board_help()
{
    for(int i=0; i<9; i++)
    {
        cout<<i+1;
        if((i+1)%3!=0)
            cout<<" | ";
        else
            cout<<endl;
        if(i==2 || i==5)
            cout<<"---------"<<endl;
    }
    cout<<endl;
};

void Game::display_flags()
{
    if(first_flag==1)
        cout<<first_player<<": X\t"<<second_player<<": O";
    else
        cout<<first_player<<": O\t"<<second_player<<": X";
    cout<<endl;
};

void Game::display_scores()
{
    cout<<endl<<first_player<<": "<<first_score<<"\t"<< second_player<<": "<<second_score<<endl<<endl;
};


void Game::computer_easy()      //easy computer plays at random
{
    int choice=rand()%9;
    while(board[choice]!=0)
        choice=rand()%9;
    board[choice]=second_flag;
};

void Game::computer_medium()    //medium computer blocks enemy winning moves and tries to win itself
{
    if(try_win())
    {

    }
    else if(block())
    {

    }
    else if(board[0]==second_flag &&(board[1]==0 || board[2]==0 || board[3]==0 || board[4]==0 || board[6]==0 || board[8]==0))
    {
        int choice=rand()%6;
        if(choice==0 && board[1]==0)
            board[1]=second_flag;
        else if(choice==1 && board[2]==0)
            board[2]=second_flag;
        else if(choice==2 && board[3]==0)
            board[3]=second_flag;
        else if(choice==3 && board[4]==0)
            board[4]=second_flag;
        else if(choice==4 && board[6]==0)
            board[6]=second_flag;
        else if(choice==5 && board[8]==0)
            board[8]=second_flag;
        else
        {
            if(board[1]==0)
                board[1]=second_flag;
            else if(board[2]==0)
                board[2]=second_flag;
            else if(board[3]==0)
                board[3]=second_flag;
            else if(board[4]==0)
                board[4]=second_flag;
            else if(board[6]==0)
                board[6]=second_flag;
            else
                board[8]=second_flag;
        }
    }

    else if(board[1]==second_flag &&(board[0]==0 || board[2]==0 || board[4]==0 || board[7]==0))
    {
        int choice=rand()%4;
        if(choice==0 && board[0]==0)
            board[0]=second_flag;
        else if(choice==1 && board[2]==0)
            board[2]=second_flag;
        else if(choice==2 && board[4]==0)
            board[4]=second_flag;
        else if(choice==3 && board[7]==0)
            board[7]=second_flag;
        else
        {
            if(board[0]==0)
                board[0]=second_flag;
            else if(board[2]==0)
                board[2]=second_flag;
            else if(board[4]==0)
                board[4]=second_flag;
            else
                board[7]=second_flag;
        }
    }

    else if(board[2]==second_flag &&(board[0]==0 || board[1]==0 || board[4]==0 || board[5]==0 || board[6]==0 || board[8]==0))
    {
        int choice=rand()%6;
        if(choice==0 && board[0]==0)
            board[0]=second_flag;
        else if(choice==1 && board[1]==0)
            board[1]=second_flag;
        else if(choice==2 && board[4]==0)
            board[4]=second_flag;
        else if(choice==3 && board[5]==0)
            board[5]=second_flag;
        else if(choice==4 && board[6]==0)
            board[6]=second_flag;
        else if(choice==5 && board[8]==0)
            board[8]=second_flag;
        else
        {
            if(board[0]==0)
                board[0]=second_flag;
            else if(board[1]==0)
                board[1]=second_flag;
            else if(board[4]==0)
                board[4]=second_flag;
            else if(board[5]==0)
                board[5]=second_flag;
            else if(board[6]==0)
                board[6]=second_flag;
            else
                board[8]=second_flag;
        }
    }


    else if(board[3]==second_flag &&(board[0]==0 || board[4]==0 || board[5]==0 || board[6]==0))
    {
        int choice=rand()%6;
        if(choice==0 && board[0]==0)
            board[0]=second_flag;
        else if(choice==1 && board[4]==0)
            board[4]=second_flag;
        else if(choice==2 && board[5]==0)
            board[5]=second_flag;
        else if(choice==3 && board[6]==0)
            board[6]=second_flag;
        else
        {
            if(board[0]==0)
                board[0]=second_flag;
            else if(board[4]==0)
                board[4]=second_flag;
            else if(board[5]==0)
                board[5]=second_flag;
            else
                board[6]=second_flag;
        }
    }

    else if(board[4]==second_flag &&(board[0]==0 || board[1]==0 || board[2]==0 || board[3]==0 || board[4]==0 || board[5]==0 || board[6]==0 || board[7]==0 || board[8]==0))
    {
        int choice=rand()%8;
        if(choice==0 && board[0]==0)
            board[0]=second_flag;
        else if(choice==1 && board[1]==0)
            board[1]=second_flag;
        else if(choice==2 && board[2]==0)
            board[2]=second_flag;
        else if(choice==3 && board[3]==0)
            board[3]=second_flag;
        else if(choice==4 && board[5]==0)
            board[5]=second_flag;
        else if(choice==5 && board[6]==0)
            board[6]=second_flag;
        else if(choice==6 && board[7]==0)
            board[7]=second_flag;
        else if(choice==7 && board[8]==0)
            board[8]=second_flag;
        else
        {
            if(board[0]==0)
                board[0]=second_flag;
            else if(board[1]==0)
                board[1]=second_flag;
            else if(board[2]==0)
                board[2]=second_flag;
            else if(board[3]==0)
                board[3]=second_flag;
            else if(board[5]==0)
                board[5]=second_flag;
            else if(board[6]==0)
                board[6]=second_flag;
            else if(board[7]==0)
                board[7]=second_flag;
            else
                board[8]=second_flag;
        }
    }

    else if(board[5]==second_flag &&(board[2]==0 || board[3]==0 || board[4]==0 || board[8]==0))
    {
        int choice=rand()%4;
        if(choice==0 && board[2]==0)
            board[2]=second_flag;
        else if(choice==1 && board[3]==0)
            board[3]=second_flag;
        else if(choice==2 && board[4]==0)
            board[4]=second_flag;
        else if(choice==3 && board[8]==0)
            board[8]=second_flag;
        else
        {
            if(board[2]==0)
                board[2]=second_flag;
            else if(board[3]==0)
                board[3]=second_flag;
            else if(board[4]==0)
                board[4]=second_flag;
            else
                board[8]=second_flag;
        }
    }


    else if(board[6]==second_flag &&(board[0]==0 || board[2]==0 || board[3]==0 || board[4]==0 || board[7]==0 || board[8]==0))
    {
        int choice=rand()%6;
        if(choice==0 && board[0]==0)
            board[0]=second_flag;
        else if(choice==1 && board[2]==0)
            board[2]=second_flag;
        else if(choice==2 && board[3]==0)
            board[3]=second_flag;
        else if(choice==3 && board[4]==0)
            board[4]=second_flag;
        else if(choice==4 && board[7]==0)
            board[7]=second_flag;
        else if(choice==5 && board[8]==0)
            board[8]=second_flag;
        else
        {
            if(board[0]==0)
                board[0]=second_flag;
            else if(board[2]==0)
                board[2]=second_flag;
            else if(board[3]==0)
                board[3]=second_flag;
            else if(board[4]==0)
                board[4]=second_flag;
            else if(board[7]==0)
                board[7]=second_flag;
            else
                board[8]=second_flag;
        }
    }



    else if(board[7]==second_flag &&(board[1]==0 || board[4]==0 || board[6]==0 || board[8]==0))
    {
        int choice=rand()%4;
        if(choice==0 && board[1]==0)
            board[1]=second_flag;
        else if(choice==1 && board[4]==0)
            board[4]=second_flag;
        else if(choice==2 && board[6]==0)
            board[6]=second_flag;
        else if(choice==5 && board[8]==0)
            board[8]=second_flag;
        else
        {
            if(board[1]==0)
                board[1]=second_flag;
            else if(board[4]==0)
                board[4]=second_flag;
            else if(board[6]==0)
                board[6]=second_flag;
            else
                board[8]=second_flag;
        }
    }


    else if(board[8]==second_flag &&(board[0]==0 || board[2]==0 || board[4]==0 || board[5]==0 || board[6]==0 || board[7]==0))
    {
        int choice=rand()%6;
        if(choice==0 && board[0]==0)
            board[0]=second_flag;
        else if(choice==1 && board[2]==0)
            board[2]=second_flag;
        else if(choice==3 && board[4]==0)
            board[4]=second_flag;
        else if(choice==4 && board[5]==0)
            board[5]=second_flag;
        else if(choice==5 && board[7]==0)
            board[7]=second_flag;
        else
        {
            if(board[0]==0)
                board[0]=second_flag;
            else if(board[2]==0)
                board[2]=second_flag;
            else if(board[4]==0)
                board[4]=second_flag;
            else if(board[5]==0)
                board[5]=second_flag;
            else
                board[7]=second_flag;
        }
    }

    else
    {
        int choice=rand()%9;
        while(board[choice]!=0)
            choice=rand()%9;
        board[choice]=second_flag;
    }

};

void Game::computer_impossible()    //impossible computer never loses. It will win or draw if opponent plays right
{
    if(second_flag==1)  //X
    {
        if(turn_counter==1)         //turn 1
        {
            int choice_corner=rand()%4;
            switch(choice_corner)
            {
            case 0:                 //top left
                board[0]=second_flag;
                break;
            case 1:                 //top right
                board[2]=second_flag;
                break;
            case 2:                 //bottom left
                board[6]=second_flag;
                break;
            case 3:                 //bottom right
                board[8]=second_flag;
                break;
            }
            turn_counter++;
        }
        else if(turn_counter==2)        //turn 2
        {
            if(board[4]==first_flag)   //player played middle
            {
                strategy=1;
                if(board[0]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[8]=second_flag;
                    else if(choice==1)
                    {
                        int choice=rand()%2;
                        if (choice==0)
                            board[5]=second_flag;
                        else
                            board[7]=second_flag;
                    }
                }
                else if(board[2]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[6]=second_flag;
                    else if(choice==1)
                    {
                        int choice=rand()%2;
                        if (choice==0)
                            board[3]=second_flag;
                        else
                            board[7]=second_flag;
                    }
                }
                else if(board[6]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[2]=second_flag;
                    else if(choice==1)
                    {
                        int choice=rand()%2;
                        if (choice==0)
                            board[1]=second_flag;
                        else
                            board[5]=second_flag;
                    }

                }
                else
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[0]=second_flag;
                    else if(choice==1)
                    {
                        int choice=rand()%2;
                        if (choice==0)
                            board[1]=second_flag;
                        else
                            board[3]=second_flag;
                    }
                }
            }

            else if(board[0]==first_flag || board[2]==first_flag || board[6]==first_flag || board[8]==first_flag) //player played corner
            {
                strategy=0;
                int choice_corner=rand()% 2;
                if(board[0]==second_flag)
                {
                    if (choice_corner==0 && board[2]==0)
                        board[2]=second_flag;
                    else if(board[6]==0)
                        board[6]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[2]==second_flag)
                {
                    if (choice_corner==0 && board[0]==0)
                        board[0]=second_flag;
                    else if(board[6]==0)
                        board[6]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[6]==second_flag)
                {
                    if (choice_corner==0 && board[0]==0)
                        board[0]=second_flag;
                    else if(board[2]==0)
                        board[2]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else
                {
                    if (choice_corner==0 && board[0]==0)
                        board[0]=second_flag;
                    else if(board[2]==0)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }
            }

            else if(board[1]==first_flag)
            {
                if(board[0]==second_flag)
                    board[6]=second_flag;
                else if(board[2]==second_flag)
                    board[8]=second_flag;
                else if(board[6]==second_flag)
                {
                    int choice_corner=rand()%2;
                    if(choice_corner==0)
                        board[0]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else
                {
                    int choice_corner=rand()%2;
                    if(choice_corner==0)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }
            }

            else if(board[3]==first_flag)
            {
                if(board[0]==second_flag)
                    board[2]=second_flag;
                else if(board[6]==second_flag)
                    board[8]=second_flag;
                else if(board[2]==second_flag)
                {
                    int choice_corner=rand()%2;
                    if(choice_corner==0)
                        board[0]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else
                {
                    int choice_corner=rand()%2;
                    if(choice_corner==0)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }
            }

            else if(board[5]==first_flag)
            {
                if(board[2]==second_flag)
                    board[0]=second_flag;
                else if(board[8]==second_flag)
                    board[6]=second_flag;
                else if(board[0]==second_flag)
                {
                    int choice_corner=rand()%2;
                    if(choice_corner==0)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }
                else
                {
                    int choice_corner=rand()%2;
                    if(choice_corner==0)
                        board[2]=second_flag;
                    else
                        board[8]=second_flag;
                }
            }

            else
            {
                if(board[6]==second_flag)
                    board[0]=second_flag;
                else if(board[8]==second_flag)
                    board[2]=second_flag;
                else if(board[0]==second_flag)
                {
                    int choice_corner=rand()%2;
                    if(choice_corner==0)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }
                else
                {
                    int choice_corner=rand()%2;
                    if(choice_corner==0)
                        board[0]=second_flag;
                    else
                        board[8]=second_flag;
                }
            }
            turn_counter++;
        }

        else if(turn_counter==3)   //turn 3
        {
            if(strategy==1)    //player played middle at the start
            {
                if(board[0]==first_flag && board[8]==0)
                {
                    board[8]=second_flag;
                }
                else if(board[1]==first_flag && board[7]==0)
                {
                    board[7]=second_flag;
                }
                else if(board[2]==first_flag && board[6]==0)
                {
                    board[6]=second_flag;
                }
                else if(board[3]==first_flag && board[5]==0)
                {
                    board[5]=second_flag;
                }
                else if(board[5]==first_flag && board[3]==0)
                {
                    board[3]=second_flag;
                }
                else if(board[6]==first_flag && board[2]==0)
                {
                    board[2]=second_flag;
                }
                else if(board[7]==first_flag && board[1]==0)
                {
                    board[1]=second_flag;
                }
                else if(board[8]==first_flag && board[0]==0)
                {
                    board[0]=second_flag;
                }

                else if(board[0]==second_flag && board[5]==second_flag)
                {
                    if(board[3]==first_flag)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }
                else if(board[0]==second_flag && board[7]==second_flag)
                {
                    if(board[1]==first_flag)
                        board[6]=second_flag;
                    else
                        board[2]=second_flag;
                }

                else if(board[2]==second_flag && board[3]==second_flag)
                {
                    if(board[5]==first_flag)
                        board[0]=second_flag;
                    else
                        board[8]=second_flag;

                }

                else if(board[2]==second_flag && board[7]==second_flag)
                {
                    if(board[1]==first_flag)
                        board[8]=second_flag;
                    else
                        board[0]=second_flag;

                }

                else if(board[6]==second_flag && board[1]==second_flag)
                {
                    if(board[7]==first_flag)
                        board[0]=second_flag;
                    else
                        board[8]=second_flag;
                }

                else if(board[6]==second_flag && board[5]==second_flag)
                {
                    if(board[2]==first_flag)
                        board[0]=second_flag;
                    else
                        board[8]=second_flag;
                }

                else if(board[8]==second_flag && board[1]==second_flag)
                {
                    if(board[0]==first_flag)
                        board[6]=second_flag;
                    else
                        board[2]=second_flag;

                }
                else if(board[8]==second_flag && board[3]==second_flag)
                {
                    if(board[0]==first_flag)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }
            }
            else
            {
                if(board[0]==second_flag && board[2]==second_flag)
                {
                    if(board[1]==0)
                        board[1]=second_flag;
                    else if(board[3]==first_flag || board[5]==first_flag || board[7]==first_flag)
                        board[4]=second_flag;
                    else if(board[8]==first_flag)
                        board[6]=second_flag;
                    else if(board[6]==first_flag)
                        board[8]=second_flag;

                }
                else if(board[0]==second_flag && board[6]==second_flag)
                {
                    if(board[3]==0)
                        board[3]=second_flag;
                    else if(board[1]==first_flag || board[7]==first_flag || board[5]==first_flag)
                        board[4]=second_flag;
                    else if(board[2]==first_flag)
                        board[8]=second_flag;
                    else if(board[8]==first_flag)
                        board[2]=second_flag;

                }
                else if(board[0]==second_flag && board[8]==second_flag)
                {
                    if(board[4]==0)
                        board[4]=second_flag;
                    else if(board[2]==first_flag)
                        board[6]=second_flag;
                    else if(board[6]==first_flag)
                        board[2]=second_flag;
                }

                else if(board[2]==second_flag && board[6]==second_flag)
                {
                    if(board[4]==0)
                        board[4]=second_flag;
                    else if(board[0]==first_flag)
                        board[8]=second_flag;
                    else if(board[8]==first_flag)
                        board[0]=second_flag;
                }
                else if(board[2]==second_flag && board[8]==second_flag)
                {
                    if(board[5]==0)
                        board[5]=second_flag;
                    else if(board[1]==first_flag || board[7]==first_flag || board[3]==first_flag)
                        board[4]=second_flag;
                    else if(board[0]==first_flag)
                        board[6]=second_flag;
                    else if(board[6]==first_flag)
                        board[0]=second_flag;
                }

                else if(board[6]==second_flag && board[8]==second_flag)
                {
                    if(board[7]==0)
                        board[7]=second_flag;
                    else if(board[3]==first_flag || board[1]==first_flag || board[5]==first_flag)
                        board[4]=second_flag;
                    else if(board[0]==first_flag)
                        board[2]=second_flag;
                    else if(board[2]==first_flag)
                        board[0]=second_flag;
                }
            }

            turn_counter++;
        }

        else if(turn_counter==4)        //turn 4
        {
            if (strategy==1)   //player played middle at the start
            {
                if(try_win())
                {

                }
                else if(board[0]==first_flag && board[8]==0)
                {
                    board[8]=second_flag;
                }
                else if(board[2]==first_flag && board[6]==0)
                {
                    board[6]=second_flag;
                }
                else if(board[6]==first_flag && board[2]==0)
                {
                    board[2]=second_flag;
                }
                else if(board[8]==first_flag && board[0]==0)
                {
                    board[0]=second_flag;
                }

                else if(board[0]==second_flag && board[1]==0 && board[2]==0)
                {
                    board[1]=second_flag;
                }
                else if(board[0]==second_flag && board[3]==0 && board[6]==0)
                {
                    board[3]=second_flag;
                }
                else if(board[2]==second_flag && board[1]==0 && board[0]==0)
                {
                    board[1]=second_flag;
                }
                else if(board[2]==second_flag && board[5]==0 && board[8]==0)
                {
                    board[5]=second_flag;
                }
                else if(board[6]==second_flag && board[3]==0 && board[0]==0)
                {
                    board[3]=second_flag;
                }
                else if(board[6]==second_flag && board[7]==0 && board[8]==0)
                {
                    board[7]=second_flag;
                }
                else if(board[8]==second_flag && board[7]==0 && board[6]==0)
                {
                    board[7]=second_flag;
                }
                else if(board[8]==second_flag && board[5]==0 && board[2]==0)
                {
                    board[5]=second_flag;
                }

            }
            else
            {
                if(board[0]==second_flag && board[2]==second_flag && (board[3]==0 || board[4]==0 || board[6]!=second_flag))
                {
                    if(board[4]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[6]==0)
                            board[6]=second_flag;
                        else if(board[8]==0)
                            board[8]=second_flag;
                        else
                            board[6]=second_flag;
                    }
                    else if(board[6]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[3]==0)
                            board[3]=second_flag;
                        else if(board[4]==0)
                            board[4]=second_flag;
                        else
                            board[3]=second_flag;
                    }
                    else
                    {
                        int choice =rand()%2;
                        if(choice==0 && board[4]==0)
                            board[4]=second_flag;
                        else if(board[5]==0)
                            board[5]=second_flag;
                        else
                            board[4]=second_flag;
                    }

                }
                else if(board[0]==second_flag && board[6]==second_flag && (board[1]==0 || board[4]==0 || board[2]!=second_flag))
                {
                    if(board[4]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[2]==0)
                            board[2]=second_flag;
                        else if(board[8]==0)
                            board[8]=second_flag;
                        else
                            board[2]=second_flag;
                    }
                    else if(board[2]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[1]==0)
                            board[1]=second_flag;
                        else if(board[4]==0)
                            board[4]=second_flag;
                        else
                            board[4]=second_flag;
                    }
                    else
                    {
                        int choice =rand()%2;
                        if(choice==0 && board[4]==0)
                            board[4]=second_flag;
                        else if(board[7]==0)
                            board[7]=second_flag;
                        else
                            board[1]=second_flag;
                    }

                }
                else if(board[0]==second_flag && board[8]==second_flag)
                {
                    if(board[2]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[3]==0)
                            board[3]=second_flag;
                        else if(board[7]==0)
                            board[7]=second_flag;
                        else
                            board[3]=second_flag;
                    }
                    else
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[1]==0)
                            board[1]=second_flag;
                        else if(board[5]==0)
                            board[5]=second_flag;
                        else
                            board[1]=second_flag;
                    }
                }

                else if(board[2]==second_flag && board[6]==second_flag)
                {
                    if(board[0]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[1]==0)
                            board[1]=second_flag;
                        else if(board[3]==0)
                            board[3]=second_flag;
                        else
                            board[1]=second_flag;
                    }
                    else
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[5]==0)
                            board[5]=second_flag;
                        else if(board[7]==0)
                            board[7]=second_flag;
                        else
                            board[5]=second_flag;
                    }

                }
                else if(board[2]==second_flag && board[8]==second_flag && (board[1]==0 || board[4]==0 || board[0]!=second_flag))
                {
                    if(board[4]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[0]==0)
                            board[0]=second_flag;
                        else if(board[6]==0)
                            board[6]=second_flag;
                        else
                            board[0]=second_flag;
                    }
                    else if(board[0]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[1]==0)
                            board[1]=second_flag;
                        else if(board[4]==0)
                            board[4]=second_flag;
                        else
                            board[1]=second_flag;
                    }
                    else
                    {
                        int choice =rand()%2;
                        if(choice==0 && board[4]==0)
                            board[4]=second_flag;
                        else if(board[7]==0)
                            board[7]=second_flag;
                        else
                            board[4]=second_flag;
                    }

                }

                else if(board[6]==second_flag && board[8]==second_flag)
                {
                    if(board[4]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[0]==0)
                            board[0]=second_flag;
                        else if(board[2]==0)
                            board[2]=second_flag;
                        else
                            board[0]=second_flag;
                    }
                    else if(board[0]==second_flag)
                    {
                        int choice=rand()%2;
                        if(choice==0 && board[3]==0)
                            board[3]=second_flag;
                        else if(board[4]==0)
                            board[4]=second_flag;
                        else
                            board[3]=second_flag;
                    }
                    else
                    {
                        int choice =rand()%2;
                        if(choice==0 && board[4]==0)
                            board[4]=second_flag;
                        else if(board[5]==0)
                            board[5]=second_flag;
                        else
                            board[4]=second_flag;
                    }
                }
            }

            turn_counter++;      //player played corner
        }
        else if(turn_counter==5) //tura 5
        {
            for(int i=0; i<9; i++)
            {
                if(board[i]==0)
                    board[i]=second_flag;
            }
        }
    }


    else    //O
    {
        if(turn_counter==1) //turn 1
        {
            if(board[0]==first_flag || board[2]==first_flag || board[6]==first_flag || board[8]==first_flag)      //player played corner
            {
                board[4]=second_flag;
                strategy=0;
            }
            else if(board[4]==first_flag)   //player played middle
            {
                int choice=rand()%4;
                if(choice==0)
                    board[0]=second_flag;
                else if(choice==1)
                    board[2]=second_flag;
                else if(choice==2)
                    board[6]=second_flag;
                else
                    board[8]=second_flag;
                strategy=1;
            }
            else            //player played edge
            {
                board[4]=second_flag;
                strategy=2;
            }
            turn_counter++;
        }


        else if(turn_counter==2) //turn 2
        {
            if(strategy==0)
            {
                if(block())
                {
                }
                else
                {
                    int choice=rand()%4;
                    if(choice==0 && board[1]==0 && board[7]==0)
                        board[1]=second_flag;
                    else if(choice==1 && board[3]==0 && board[5]==0)
                        board[3]=second_flag;
                    else if(choice==2 && board[7]==0 && board[1]==0)
                        board[7]=second_flag;
                    else if(board[5]==0 && board[3]==0)
                        board[5]=second_flag;
                    else
                        board[1]=second_flag;
                }
            }

            else if(strategy==1)
            {
                if(board[0]!=0 && board[8]!=0)
                {
                    int choice=rand()%2;
                    if (choice==0)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }
                else if(board[2]!=0 && board[6]!=0)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[0]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[0]==first_flag)
                {
                    board[0]=second_flag;
                }
                else if(board[1]==first_flag)
                {
                    board[7]=second_flag;
                }
                else if(board[2]==first_flag)
                {
                    board[6]=second_flag;
                }
                else if(board[3]==first_flag)
                {
                    board[5]=second_flag;
                }
                else if(board[5]==first_flag)
                {
                    board[3]=second_flag;
                }
                else if(board[6]==first_flag)
                {
                    board[2]=second_flag;
                }
                else if(board[7]==first_flag)
                {
                    board[1]=second_flag;
                }
                else if(board[8]==first_flag)
                {
                    board[0]=second_flag;
                }
            }

            else
            {
                if(block())
                {

                }
                else if((board[1]==first_flag && board[7]==first_flag) || (board[3]==first_flag && board[5]==first_flag))
                {
                    int choice=rand()% 4;
                    if(choice==0)
                        board[0]=second_flag;
                    else if(choice==1)
                        board[2]=second_flag;
                    else if(choice==2)
                        board[6]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[1]==first_flag && board[3]==first_flag)
                {
                    int choice=rand()%3;
                    if(choice==0)
                        board[0]=second_flag;
                    else if(choice==1)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }

                else if(board[1]==first_flag && board[5]==first_flag)
                {
                    int choice=rand()%3;
                    if(choice==0)
                        board[0]=second_flag;
                    else if(choice==1)
                        board[2]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[5]==first_flag && board[7]==first_flag)
                {
                    int choice=rand()%3;
                    if(choice==0)
                        board[2]=second_flag;
                    else if(choice==1)
                        board[6]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[3]==first_flag && board[7]==first_flag)
                {
                    int choice=rand()%3;
                    if(choice==0)
                        board[0]=second_flag;
                    else if(choice==1)
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }

            }


            turn_counter++;
        }
        else if(turn_counter==3) //turn 3
        {
            if(try_win())
            {

            }
            else if(block())
            {

            }

            else if(strategy==0)
            {

                if(board[1]==first_flag && board[3]==first_flag)
                {
                    board[2]=second_flag;
                }
                else if(board[1]==first_flag && board[5]==first_flag)
                {
                    board[0]=second_flag;
                }
                else if(board[5]==first_flag && board[7]==first_flag)
                {
                    board[6]=second_flag;
                }
                else if(board[3]==first_flag && board[7]==first_flag)
                {
                    board[8]=second_flag;
                }
                else
                {
                    int choice=rand()%9;
                    while(board[choice]!=0)
                        choice=rand()%9;
                    board[choice]=second_flag;
                }
            }

            else if(strategy==1)
            {

                if(board[0]==first_flag && board[3]==second_flag && board[8]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[6]=second_flag;
                    else
                        board[7]=second_flag;
                }
                else if(board[0]==first_flag && board[1]==second_flag && board[8]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[2]=second_flag;
                    else
                        board[5]=second_flag;
                }
                else if(board[2]==first_flag && board[5]==second_flag && board[6]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[7]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[2]==first_flag && board[1]==second_flag && board[6]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[0]=second_flag;
                    else
                        board[3]=second_flag;
                }
                else if(board[8]==first_flag && board[0]==second_flag && board[7]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[3]=second_flag;
                    else
                        board[6]=second_flag;
                }
                else if(board[8]==first_flag && board[0]==second_flag && board[5]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[1]=second_flag;
                    else
                        board[2]=second_flag;
                }
                else if(board[6]==first_flag && board[2]==second_flag && board[7]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[5]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[6]==first_flag && board[2]==second_flag && board[3]==second_flag)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[0]=second_flag;
                    else
                        board[1]=second_flag;
                }

            }

            else
            {
                if(board[0]==0 && board[8]==0)
                {
                    int choice=rand()%2;
                    if(choice==0)
                        board[0]=second_flag;
                    else
                        board[8]=second_flag;
                }
                else if(board[2]==0 && board[6]==0)
                {
                    int choice=rand()%2;
                    if (choice==0 )
                        board[2]=second_flag;
                    else
                        board[6]=second_flag;
                }



            }


            turn_counter++;
        }

        else            //turn 4
        {
            if(try_win())
            {

            }
            else if(block())
            {

            }
            else
            {
                int choice=rand()%9;
                while(board[choice]!=0)
                    choice=rand()%9;
                board[choice]=second_flag;
            }
        }
    }

};

bool Game::try_win()
{
    if(board[0]==second_flag && board[2]==second_flag && board[1]==0)
    {
        board[1]=second_flag;
    }
    else if(board[0]==second_flag && board[6]==second_flag && board[3]==0)
    {
        board[3]=second_flag;
    }
    else if(board[2]==second_flag && board[8]==second_flag && board[5]==0)
    {
        board[5]=second_flag;
    }
    else if(board[6]==second_flag && board[8]==second_flag && board[7]==0)
    {
        board[7]=second_flag;
    }


    else if(board[0]==second_flag && board[1]==second_flag && board[2]==0)
    {
        board[2]=second_flag;
    }
    else if(board[0]==second_flag && board[3]==second_flag && board[6]==0)
    {
        board[6]=second_flag;
    }
    else if(board[2]==second_flag && board[1]==second_flag && board[0]==0)
    {
        board[0]=second_flag;
    }
    else if(board[2]==second_flag && board[5]==second_flag && board[8]==0)
    {
        board[8]=second_flag;
    }
    else if(board[6]==second_flag && board[3]==second_flag && board[0]==0)
    {
        board[0]=second_flag;
    }
    else if(board[6]==second_flag && board[7]==second_flag && board[8]==0)
    {
        board[8]=second_flag;
    }
    else if(board[8]==second_flag && board[7]==second_flag && board[6]==0)
    {
        board[6]=second_flag;
    }
    else if(board[8]==second_flag && board[5]==second_flag && board[2]==0)
    {
        board[2]=second_flag;
    }

    else if(board[0]==second_flag && board[4]==second_flag && board[8]==0)
    {
        board[8]=second_flag;
    }
    else if(board[2]==second_flag && board[4]==second_flag && board[6]==0)
    {
        board[6]=second_flag;
    }
    else if(board[6]==second_flag && board[4]==second_flag && board[2]==0)
    {
        board[2]=second_flag;
    }
    else if(board[8]==second_flag && board[4]==second_flag && board[0]==0)
    {
        board[8]=second_flag;
    }

    else if(board[0]==second_flag && board[8]==second_flag && board[4]==0)
    {
        board[4]=second_flag;
    }
    else if(board[2]==second_flag && board[6]==second_flag && board[4]==0)
    {
        board[4]=second_flag;
    }

    else if(board[1]==second_flag && board[4]==second_flag && board[7]==0)
    {
        board[7]=second_flag;
    }
    else if(board[3]==second_flag && board[4]==second_flag && board[5]==0)
    {
        board[5]=second_flag;
    }
    else if(board[7]==second_flag && board[4]==second_flag && board[1]==0)
    {
        board[1]=second_flag;
    }
    else if(board[5]==second_flag && board[4]==second_flag && board[3]==0)
    {
        board[3]=second_flag;
    }
    else if(board[1]==second_flag && board[7]==second_flag && board[4]==0)
    {
        board[4]=second_flag;
    }
    else if(board[3]==second_flag && board[5]==second_flag && board[4]==0)
    {
        board[4]=second_flag;
    }
    else
    {
        return false;
    }

    return true;
};


bool Game::block()
{

    if(board[0]==first_flag && board[2]==first_flag && board[1]==0)
    {
        board[1]=second_flag;
    }
    else if(board[0]==first_flag && board[6]==first_flag && board[3]==0)
    {
        board[3]=second_flag;
    }
    else if(board[2]==first_flag && board[8]==first_flag && board[5]==0)
    {
        board[5]=second_flag;
    }
    else if(board[6]==first_flag && board[8]==first_flag && board[7]==0)
    {
        board[7]=second_flag;
    }


    else if(board[0]==first_flag && board[1]==first_flag && board[2]==0)
    {
        board[2]=second_flag;
    }
    else if(board[0]==first_flag && board[3]==first_flag && board[6]==0)
    {
        board[6]=second_flag;
    }
    else if(board[2]==first_flag && board[1]==first_flag && board[0]==0)
    {
        board[0]=second_flag;
    }
    else if(board[2]==first_flag && board[5]==first_flag && board[8]==0)
    {
        board[8]=second_flag;
    }
    else if(board[6]==first_flag && board[3]==first_flag && board[0]==0)
    {
        board[0]=second_flag;
    }
    else if(board[6]==first_flag && board[7]==first_flag && board[8]==0)
    {
        board[8]=second_flag;
    }
    else if(board[8]==first_flag && board[7]==first_flag && board[6]==0)
    {
        board[6]=second_flag;
    }
    else if(board[8]==first_flag && board[5]==first_flag && board[2]==0)
    {
        board[2]=second_flag;
    }

    else if(board[0]==first_flag && board[4]==first_flag && board[8]==0)
    {
        board[8]=second_flag;
    }
    else if(board[2]==first_flag && board[4]==first_flag && board[6]==0)
    {
        board[6]=second_flag;
    }
    else if(board[6]==first_flag && board[4]==first_flag && board[2]==0)
    {
        board[2]=second_flag;
    }
    else if(board[8]==first_flag && board[4]==first_flag && board[0]==0)
    {
        board[0]=second_flag;
    }

    else if(board[0]==first_flag && board[8]==first_flag && board[4]==0)
    {
        board[4]=second_flag;
    }
    else if(board[2]==first_flag && board[6]==first_flag && board[4]==0)
    {
        board[4]=second_flag;
    }

    else if(board[1]==first_flag && board[4]==first_flag && board[7]==0)
    {
        board[7]=second_flag;
    }
    else if(board[3]==first_flag && board[4]==first_flag && board[5]==0)
    {
        board[5]=second_flag;
    }
    else if(board[7]==first_flag && board[4]==first_flag && board[1]==0)
    {
        board[1]=second_flag;
    }
    else if(board[5]==first_flag && board[4]==first_flag && board[3]==0)
    {
        board[3]=second_flag;
    }
    else if(board[1]==first_flag && board[7]==first_flag && board[4]==0)
    {
        board[4]=second_flag;
    }
    else if(board[3]==first_flag && board[5]==first_flag && board[4]==0)
    {
        board[4]=second_flag;
    }
    else
    {
        return false;
    }

    return true;



};



