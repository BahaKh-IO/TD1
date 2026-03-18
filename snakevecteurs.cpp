#include<iostream>
#include<conio.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<vector>

using namespace std;

int width, height;
int x, y, fruitX, fruitY, score;
vector<int> tailX, tailY;
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
bool gameOver;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Setup()
{
    width = 20;
    height = 20;

    x = width / 2;
    y = height / 2;
    srand(time(NULL));
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    gameOver = false;

    tailX.clear();
    tailY.clear();

    dir = RIGHT;
}

void Draw()
{
    gotoxy(0, 0);

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        cout << "#";
        for (int j = 0; j < width; j++)
        {
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
            {
                bool printTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail)
                    cout << " ";
            }
        }
        cout << "#" << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        int c = _getch();
        if (c == 0 || c == 224)
        {
            int c2 = _getch();
            switch (c2)
            {
            case 75:
                if (dir != RIGHT) dir = LEFT;
                break;
            case 77:
                if (dir != LEFT) dir = RIGHT;
                break;
            case 72:
                if (dir != DOWN) dir = UP;
                break;
            case 80:
                if (dir != UP) dir = DOWN;
                break;
            }
        }
        else
        {
            char ch = tolower(c);
            switch (ch)
            {
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }
}

void Logic()
{
    if (nTail > 0)
    {
        for (int i = nTail - 1; i > 0; i--)
        {
            tailX[i] = tailX[i - 1];
            tailY[i] = tailY[i - 1];
        }

        tailX[0] = x;
        tailY[0] = y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score++;
        nTail++;
        tailX.push_back(-1);
        tailY.push_back(-1);
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(500);
    }
    return 0;
}