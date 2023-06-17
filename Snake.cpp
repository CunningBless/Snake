#include<iostream>
#include<string>
#include<conio.h>
#include<Windows.h>

 
//using namespace std;

int Score;
bool Game_Exit;
const int Width = 30;
const int Hight = 20;
int X, Y, DotX, DotY;
int tailX[100], tailY[100], ntail;

enum Dir
{
	up,down,left,right,stop = 0
};
Dir D;

void Start()
{
	Game_Exit = false;
	D = stop;
	X = (Width / 2) - 1;
	Y = (Hight / 2) - 1;
	DotX = rand() % Width;
	DotY = rand() % Hight;
}

void Field()
{
	system("cls");

	for (int i = 0; i < Width + 1; i++)
	{

		std::cout << ",";
	}
	std::cout << std::endl;

	for (int i = 0; i < Hight; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (j == 0 || j == Width - 1)
			{
				std::cout << "|";
			}
			if (i == X && j == Y)
			{
				std::cout << "O";
			}
			else if (i == DotX && j == DotY)
			{
				std::cout << "$";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						std::cout << "o";
					}
				}
				if (!print)
				{
					std::cout << " ";
				}
			}
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < Width + 1; i++)
	{
		std::cout << "`";
	}
	std::cout << "Score: " << Score << std::endl;
}


void Remote()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			D = up;
			break;
		case 'a':
			D = left;
			break;
		case 's':
			D = down;
			break;
		case 'd':
			D = right;
			break;
		case 't':
			Game_Exit = true;
			break;
			std::cout << "GAME OVER" << std::endl;
		}
	}
}

void Logic()
{
		int prevX = tailX[Width];
		int prevY = tailY[Hight];
		int prev2X, prev2Y;
		tailX[0] = X;
		tailY[0] = Y;
		for (int i = 0; i < ntail; i++)
		{
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}

		switch (D)
		{
		case up:
			X--;
			break;
		case left:
			Y--;
			break;
		case down:
			X++;
			break;
		case right:
			Y++;
			break;
		}

		/*if (X > Width || X<0 || Y>Hight || Y < 0)
		{
			Game_Exit = true;
		}*/
		if (X >= Width - 1)
		{
			X = 0;
		}
		else if (X <= 0)
		{
			X = Width - 2;
		}
		if (Y >= Hight)
		{
			Y = 0;
		}
		else if (Y <= 0)
		{
			Y = Hight;
		}

		for (int i = 0; i < ntail; i++)
		{
			if (tailX[i] == X && tailY[i] == Y)
			{
				Game_Exit = true;
			}
		}

		if (X == DotX || Y == DotY)
		{
			Score += 10;
			DotX = rand() % Width;
			DotY = rand() % Hight;
			ntail++;
		}
}

int main()
{
	setlocale(LC_ALL, "ru");

	Start();
	while (!Game_Exit) {
		Field();
		Remote();
		Logic();
		Sleep(300);
	}

	std::cout << "GAME OVER" << std::endl;

	std::cout << "Do u want restart the game?" << std::endl;
	std::cout << "1 - YES" << std::endl;
	std::cout << "0 - NO" << std::endl;

	int a;
	std::cin >> a;
	if (a == 1)
	{
		main ();
	}

	return 0;
}

