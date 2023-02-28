#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>

using namespace std;

const int width = 20;
const int height = 20;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
bool gameOver;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls"); // clear console
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == foodY && j == foodX)
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }


            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
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
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (_getch())
    {
    case 'a':
        x--;
        break;
    case 'd':
        x++;
        break;
    case 'w':
        y--;
        break;
    case 's':
        y++;
        break;
    case 'x':
        gameOver = true;
        break;
    }

    // if the snake hits the wall or itself, the game is over
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // if the snake eats the food, generate new food and increase the score
    if (x == foodX && y == foodY)
    {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}

int main()
{
    srand(time(0));
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10); // control the speed of the game
    }
    return 0;
}
