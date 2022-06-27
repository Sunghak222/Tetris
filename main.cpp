#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#define X_INIT_BOARD 20
#define Y_INIT_BOARD 5
#define X_FINAL_BOARD 41
#define Y_FINAL_BOARD 26
#define X_SIDE 20
#define Y_SIDE 20
#define X_TABLE 10
#define Y_TABLE 20

using namespace std;
//■□▦
const string kWall = "▦";
const string kBlock = "■";
const string kSpace = "  ";

void gotoxy(short x, short y)
{
    COORD pos{x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void CursorView(char show) 
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
enum Keys
{
    ESC = 27,
    SPACE = 32,
    LEFT = 75,
    RIGHT = 77,
    UP = 72,
    DOWN = 80
};

const int blocks[7][4][4][4] = 
    {
        {
            {
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0}
            },
            {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0}
            },
            {
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,1,0,0}
            },
            {
                {0,0,0,0},
                {0,0,0,0},
                {1,1,1,1},
                {0,0,0,0}
            }
        },
        {
            {
                {0,1,0,0},
                {0,1,1,0},
                {0,0,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,0,1,1},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,1,0,0},
                {0,1,1,0},
                {0,0,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,0,1,1},
                {0,1,1,0},
                {0,0,0,0}
            }
        },
        {
            {
                {0,0,1,0},
                {0,1,1,0},
                {0,1,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,0,1,1},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,1,1,0},
                {0,1,0,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,0,1,1},
                {0,0,0,0}
            },
        },
        {
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,0},
                {0,1,1,0},
                {0,0,0,0}
            }
        },
        {
            {
                {0,0,0,0},
                {0,0,1,0},
                {0,1,1,1},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,0,1,0},
                {0,0,1,1},
                {0,0,1,0}
            },
            {
                {0,0,0,0},
                {0,0,0,0},
                {0,1,1,1},
                {0,0,1,0}
            },
            {
                {0,0,0,0},
                {0,0,1,0},
                {0,1,1,0},
                {0,0,1,0}
            }
        },
        {
            {
                {0,0,0,0},
                {0,1,0,0},
                {0,1,1,1},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,0,1,1},
                {0,0,1,0},
                {0,0,1,0}
            },
            {
                {0,0,0,0},
                {0,1,1,1},
                {0,0,0,1},
                {0,0,0,0}
            },
            {
                {0,0,0,1},
                {0,0,0,1},
                {0,0,1,1},
                {0,0,0,0}
            }
        },
        {
            {
                {0,0,0,0},
                {0,0,0,1},
                {0,1,1,1},
                {0,0,0,0}
            },
            {
                {0,0,1,0},
                {0,0,1,0},
                {0,0,1,1},
                {0,0,0,0}
            },
            {
                {0,0,0,0},
                {0,1,1,1},
                {0,1,0,0},
                {0,0,0,0}
            },
            {
                {0,1,1,0},
                {0,0,1,0},
                {0,0,1,0},
                {0,0,0,0}
            },
        }
    };

class Block
{
protected:
    int BlockNum; //Which block? 1~7
    int RotationNum; //How many turns? 1~4
    int shape[4][4][4];
    int x_loc;
    int y_loc;
public:
    void CreateBlock()
    {
        BlockNum = (rand()%7);
        RotationNum = (rand()%4);
        x_loc = 28;
        y_loc = 6;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    shape[i][j][k] = blocks[BlockNum][i][j][k];
                }
            }
        }
    }
    void Rotate();
    void RotateReverse();
};

class Board
{
protected:
    int Table[20][10] = {0};
public:
    void PrintFrame()
    {
        for (int i = 0; i < X_SIDE+4; i+=2)
        {
            gotoxy(X_INIT_BOARD+i,Y_INIT_BOARD);
            cout << kWall;
            gotoxy(X_INIT_BOARD+i,Y_INIT_BOARD+Y_SIDE+1);
            cout << kWall;
        }
        for (int i = 0; i < Y_SIDE+2; i++)
        {
            gotoxy(X_INIT_BOARD,Y_INIT_BOARD+i);
            cout << kWall;
            gotoxy(X_INIT_BOARD+X_SIDE+2,Y_INIT_BOARD+i);
            cout << kWall;
        }
    }
};

class Score
{
    
};

class Rules : public Block, public Board, public Score
{
public:
    void DrawTable();
    void DrawBlock();
    void EraseBlock();
    void StoreBlock();

    int CheckLeft(int which_case);
    int CheckRight(int which_case);
    int CheckBelow(int which_case);

    void MoveDown();
    void HardDrop();
    void MoveBlockByKey(int key);

    int CheckCompleteLine(int y);
    void ClearLine();
    void OrganizeTable(int y);
};

class Tetris
{
private:
    int key;
    int time_start;
    int time_end;
    int time;
    Block *object;
    Rules rl;
public:
    ~Tetris()
    {
        delete[] object;
    }
    void MainMenu();
    void GamePlay();
    void experiment(Rules rl);//to be deleted.
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Block::Rotate()
{
    RotationNum++;
    RotationNum = (RotationNum > 3) ? RotationNum-4 : RotationNum;
}
inline void Block::RotateReverse()
{
    RotationNum--;
    RotationNum = (RotationNum < 0) ? RotationNum+4 : RotationNum;
}
inline void Rules::MoveDown()
{
    y_loc++;
}

void Rules::DrawTable()
{
    for (int i = 0; i < Y_TABLE; i++)
    {
        for (int j = 0; j < X_TABLE; j++)
        {
            if (Table[i][j])
            {
                gotoxy(X_INIT_BOARD+2+j*2,Y_INIT_BOARD+1+i);
                cout << kBlock;
            }
        }
    }
}
void Rules::DrawBlock()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shape[RotationNum][i][j])
            {
                gotoxy(x_loc+j*2,y_loc+i);
                cout << kBlock;
            }
        }
    }
}
void Rules::EraseBlock()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shape[RotationNum][i][j])
            {
                gotoxy(x_loc+j*2,y_loc+i);
                cout << kSpace;
            }
        }
    }
}
void Rules::StoreBlock()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shape[RotationNum][i][j])
            {
                Table[y_loc-Y_INIT_BOARD-1+i][((x_loc-X_INIT_BOARD)/2)-1+j] = 1;
            }
        }
    }
}

int Rules::CheckLeft(int which_case) //case = 1 => to move left, case = 2 => to rotate.
{
    /*If the block collides when LEFT button is hitted, return 1.*/
    if (which_case == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[RotationNum][i][j] && x_loc+j*2 <= X_INIT_BOARD+2)
                {
                    return 1;
                }
                if (shape[RotationNum][i][j] && Table[y_loc-Y_INIT_BOARD+1-1][((x_loc-X_INIT_BOARD)/2)+j-2])
                {
                    return 1;
                }
            }
        }
    }
    else if (which_case == 2)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[RotationNum][i][j] && x_loc+j*2 <= X_INIT_BOARD)
                {
                    return 1;
                }
                if (shape[RotationNum][i][j] && Table[y_loc+i-Y_INIT_BOARD-1][((x_loc-X_INIT_BOARD)/2)+j-2])
                {
                    return 1;
                }
            }
        }
    }
}
int Rules::CheckRight(int which_case)
{
    /*If the block collides when RIGHT button is hitted, return 1.*/
    if (which_case == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[RotationNum][i][j] && x_loc+j*2 >= X_FINAL_BOARD-2)
                {
                    return 1;
                }
                if (shape[RotationNum][i][j] && Table[y_loc-Y_INIT_BOARD+i-1][((x_loc-X_INIT_BOARD)/2)+j])
                {
                    return 1;
                }
            }
        }
    }
    else if (which_case == 2)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[RotationNum][i][j] && x_loc+j*2 >= X_FINAL_BOARD)
                {
                    return 1;
                }
                if (shape[RotationNum][i][j] && Table[y_loc-Y_INIT_BOARD+i-1][((x_loc-X_INIT_BOARD)/2)+j])
                {
                    return 1;
                }
            }
        }
    }
}
int Rules::CheckBelow(int which_case) //to be fixed.
{
    /*If the block collides when it goes down, return 1.*/
    if (which_case == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[RotationNum][i][j] && y_loc+i >= Y_FINAL_BOARD-1)
                {
                    return 1;
                }
                if (shape[RotationNum][i][j] && Table[y_loc-Y_INIT_BOARD+i][((x_loc-X_INIT_BOARD)/2)+j-1])
                {
                    return 1;
                }
            }
        }
    }
    else if (which_case == 2)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[RotationNum][i][j] && y_loc+i >= Y_FINAL_BOARD)
                {
                    return 1;
                }
                if (shape[RotationNum][i][j] && Table[y_loc-Y_INIT_BOARD+i][((x_loc-X_INIT_BOARD)/2)+j-1])
                {
                    return 1;
                }
            }
        }
    }
}
void Rules::HardDrop()
{

}
void Rules::MoveBlockByKey(int key)
{
    if (key == 227)
    {
        key = _getch();
    }
    switch (key)
    {
        case RIGHT:
            if (!CheckRight(1))
                x_loc+=2;
            break;
        case LEFT:
            if (!CheckLeft(1))
                x_loc-=2;
            break;
        case DOWN:
            if (!CheckBelow(1))
                y_loc++;
            break;
        case UP:
            //HardDrop();
            break;
        case SPACE:
            Rotate();
            if (CheckRight(2) || CheckLeft(2) || CheckBelow(2))
                RotateReverse();
            break;
        case ESC:
            //Pause();
            break;
        default:
            break;  
    }
}
int Rules::CheckCompleteLine(int y)
{
    /*If yth line is completely piled, return 1.*/
    for (int i = 0; i < X_TABLE; i++)
    {
        if (!Table[y][i])
        {
            return 0;
        }
    }
    return 1;
}
void Rules::ClearLine()
{
    /*After deleting lines, move down the piled blocks to the empty spaces.*/
    for (int i = 0; i < Y_TABLE; i++)
    {
        if (CheckCompleteLine(i))
        {
            for (int j = 0; j < X_TABLE; j++)
            {
                Table[i][j] = 0;
                gotoxy(X_INIT_BOARD+j*2+2, Y_INIT_BOARD+i+1);
                cout << kSpace;
            }
            OrganizeTable(i);
        }
    }


}
void Rules::OrganizeTable(int y) //Not yet completed.
{
    /*After deleting line, move down the piled blocks to the empty spaces.*/
    for (int i = y-1; i > -1; i--)
    {
        for (int j = 0; j < X_TABLE; j++)
        {
            if ((Table[i][j]) && !(Table[i+1][j]))
            {
                Table[i][j] = 0;
                Table[i+1][j] = 1;
                gotoxy(X_INIT_BOARD+j*2+2, Y_INIT_BOARD+i+1);
                cout << kSpace;
                gotoxy(X_INIT_BOARD+j*2+2, Y_INIT_BOARD+i+2);
                cout << kBlock;
            }
        }
    }
}

void Tetris::MainMenu()
{
    cout << "\n\n\n\n";
    cout << "\t\t"; cout << "@@@@@@@@@@@@  @@@@@@@@@   @@@@@@@@@@@  @@@@@@@@   @   @@@@@@@@@@@\n";
    cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
    cout << "\t\t"; cout << "      @       @                @       @      @   @   @          \n";
    cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @     @    @   @@@@@@@@@@@\n";
    cout << "\t\t"; cout << "      @       @                @       @ @ @      @             @\n";
    cout << "\t\t"; cout << "      @       @                @       @     @    @             @\n";
    cout << "\t\t"; cout << "      @       @@@@@@@@@        @       @      @   @   @@@@@@@@@@@\n\n\n\n\n";
    cout << "\t\t"; cout << "                Press any key to start.\n\n\n\n\n\n\n";
}
void Tetris::GamePlay()
{
    MainMenu();
    while (true)
    {
        if (_kbhit())
        {
            system("cls");
            break;
        }
    }

    rl.PrintFrame();
    time_start = clock();
    rl.CreateBlock();

    while (true)
    {
        rl.DrawBlock();
        rl.DrawTable();
        if (_kbhit())
        {
            key = _getch();
            if (key == ESC)
                break;
            rl.EraseBlock();
            rl.MoveBlockByKey(key);
        }
        time_end = clock();
        time = ((float)(time_end - time_start) / CLOCKS_PER_SEC);
        if (time >= 1.0)
        {
            if (!rl.CheckBelow(1))
            {
                rl.EraseBlock();
                rl.MoveDown();
            }
            else
            {
                rl.StoreBlock();
                rl.ClearLine();
                rl.CreateBlock();
            }
            time_start = clock();
        }
    }
}

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    CursorView(false);
    srand(time(NULL));
    system("cls");

    Tetris tt;
    tt.GamePlay();
}
