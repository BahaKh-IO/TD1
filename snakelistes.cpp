#include<iostream>
#include<conio.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<cctype>

using namespace std;

struct Node
{
    int x;
    int y;
    Node* next;
};

int width, height;
int x, y, fruitX, fruitY, score;
int nTail;
Node* tail;
bool gameOver;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void addTail()
{
    Node* newNode = new Node;
    newNode->x = -1;
    newNode->y = -1;
    newNode->next = NULL;

    if (tail == NULL)
    {
        tail = newNode;
    }
    else
    {
        Node* temp = tail;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    nTail++;
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
    tail = NULL;
    gameOver = false;
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
                Node* temp = tail;
                while (temp != NULL)
                {
                    if (temp->x == j && temp->y == i)
                    {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                    temp = temp->next;
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

void moveTail(int oldX, int oldY)
{
    Node* temp = tail;
    int prevX = oldX;
    int prevY = oldY;

    while (temp != NULL)
    {
        int currentX = temp->x;
        int currentY = temp->y;

        temp->x = prevX;
        temp->y = prevY;

        prevX = currentX;
        prevY = currentY;

        temp = temp->next;
    }
}

bool collisionTail()
{
    Node* temp = tail;
    while (temp != NULL)
    {
        if (temp->x == x && temp->y == y)
            return true;
        temp = temp->next;
    }
    return false;
}

void Logic()
{
    int oldX = x;
    int oldY = y;

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

    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;

    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    moveTail(oldX, oldY);

    if (collisionTail())
        gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        score++;
        addTail();
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

void FreeTail()
{
    Node* temp;
    while (tail != NULL)
    {
        temp = tail;
        tail = tail->next;
        delete temp;
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
    FreeTail();
    return 0;
}