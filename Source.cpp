#include <iostream>
#include <string.h>
using namespace std;

const int BOARD_HEIGHT = 21; //rows
const int BOARD_WIDTH = 10; //columns
const int COUNT_SHIP_TYPES = 4;//показывает сколько всего различных типов кораблей есть

const char WATER = '.';
const char SHIP = '+';
const char HIT = 'X';
const char MISS = '0';
const char SPACER = ' ';

bool clear;

//все структуры, списки, которые позже нужно вынести в заголовочный файл
struct ShipOptions
{
	string name;
	int length;
	int count;
} shipOptions[COUNT_SHIP_TYPES];

void greeting();
void initialize_ships();
void create_board(char**& board);
void print_board(char** board);
void dispose(char**& board);

void place_all_ships(char**& board);

int main()
{
	initialize_ships();

	char** boardA = nullptr;
	char** boardB = nullptr;

	create_board(boardA);
	create_board(boardB);

	bool game_over = false;

	//1. Приветствие
	//2. Кто первый ходит? Игрок А
	//3. Игрок А размещает свои корабли
	greeting();

	cout << "Player A place ships: " << endl;
	place_all_ships(boardA);
	cout << "Player B place ships: " << endl;
	place_all_ships(boardB);

	print_board(boardA);
	print_board(boardB);

	while (!game_over)
	{
		//основной игровой цикл
		//turn(char**& player_board, char**& opponent_board)
		//4. Ход Игрока А
		//4.1 Показываем поле другого игрока(вторую часть boardA)
		//4.2 Спрашиваем куда игрок хочет сделать выстрел (x,y)
		//4.3 Проверяем есть ли у другого игрока что-то в этой позиции
		//4.4 Если есть - проверяем если ли у игрока Б еще корабли, если нет то gameOver = true; - повторяем ход, иначе передаем другому игроку


	}

	dispose(boardA);
	dispose(boardB);
	return 0;
}


void greeting()
{
	cout << "        INSTRUCTION        \n";
	//some instruction
}


void create_board(char**& board)
{
	board = new char* [BOARD_HEIGHT];

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		board[i] = new char[BOARD_WIDTH];
	}

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		if (i == 10)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				board[i][j] = SPACER;
			}
		}
		else
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				board[i][j] = WATER;
			}
		}
	}
}

void print_board(char** board)
{


	for (int i = 0; i < (BOARD_HEIGHT); i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << "  " << endl;
	cout << "  " << endl;
}

void dispose(char**& board)
{	
	for (int i = 0; i < (BOARD_HEIGHT); i++)
	{
		if (board[i] != nullptr)
		{
			delete[] board[i];
		}

	}

	if (board != nullptr)
	{
		delete[] board;
	}
}

void place_all_ships(char**& board)
{
	for (int i = 0; i < COUNT_SHIP_TYPES; i++)
	{
		is_clear(board);
		cout << "Place -  " << shipOptions[i].name << "'s" << endl;

		for (int j = 0; j < shipOptions[i].count; j++)
		{
			int x, y;

			cout << "Place " << shipOptions[i].name << " # " << j + 1 << endl;

			//TODO#1: проверять вводимые значения координат
			cout << "Enter position X: " << endl;
			cin >> x;
			while (x < 0 || x > 9)
			{
				cout << "Wrong number! Please, enter number from 0 to 9" << endl;
				cin >> x;
			};

			cout << "Enter position Y: " << endl;
			cin >> y;
			while (y < 0 || y > 9)
			{
				cout << "Wrong number! Please, enter number from 0 to 9" << endl;
				cin >> y;
			};

			int direction = -1;
			while (direction != 0 && direction != 1)
			{
				cout << "Chose direction: 0 - horizontal, 1 - vertical" << endl;
				cin >> direction;
			}

			//TODO#2: проверить коллизии

			if (direction == 0)
			{
				for (int k = 0; k < shipOptions[i].length; k++)
				{

					if ((x + shipOptions[i].length) > 10)
					{
						cout << "the ship is too long and goes beyond the field, please specify a different coordinate X: \n";
						cin >> x;
						board[y][x + k] = SHIP;
					}
					else
					{
						board[y][x + k] = SHIP;
					}
				}
			}
			if (direction == 1)
			{
				for (int k = 0; k < shipOptions[i].length; k++)
				{
					if ((y + shipOptions[i].length) > 10)
					{
						cout << "the ship is too long and goes beyond the field, please specify a different coordinate Y: \n";
						cin >> y;
						board[y + k][x] = SHIP;
					}
					else
					{
						board[y + k][x] = SHIP;
					}
				}
			}
			is_clear(board);
		}
	}

}

void initialize_ships()
{
	shipOptions[0].name = "CARRIER"; shipOptions[0].length = 2; shipOptions[0].count = 4;
	shipOptions[1].name = "CRUISER"; shipOptions[1].length = 3; shipOptions[1].count = 3;
	shipOptions[2].name = "BATTLESHIP"; shipOptions[2].length = 4; shipOptions[2].count = 2;
	shipOptions[3].name = "DESTROYER"; shipOptions[3].length = 5; shipOptions[3].count = 1;
}

//проверяет занята ли ячейка в массиве
bool is_clear(char**& board)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (board[i][j] != WATER)
			{
				cout << "This part of grid is engaged. Please, choose another coordinates" << endl;
				clear = false;
				return false;
			}
		}
	}
}
//проверяет есть ли отступ в одну клетку рядом с кораблем
bool is_clear_near_ship(char**& board)
{
	if (clear = false)
	{

	}

}

//если стреляет игрок А то мы передаем в функции доску игрока В с 11 строчки
void shoot(char**& board)
{
	int x, y;
	cout << "Enter position X: ";
	cin >> x;
	cout << "Enter position Y: ";
	cin >> y;
	for (int i = 11; i <= BOARD_WIDTH; i++)
	{
		for (int j = 0; j <= BOARD_HEIGHT; j++)
		{
			if (board[i][j] != WATER)
			{
				board[i][j] == HIT;
			}
			else
			{
				board[i][j] == MISS;
			}
		}
	}
}