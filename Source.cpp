#include <iostream>
#include <string.h>
using namespace std;

const int BOARD_HEIGHT = 21; //rows
const int BOARD_WIDTH = 10; //columns
const int COUNT_SHIP_TYPES = 2;//показывает сколько всего различных типов кораблей есть

const char WATER = '.';
const char SHIP = '+';
const char HIT = 'X';
const char MISS = '0';
const char SPACER = ' ';
bool game_over = false;

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
void turn(char**& player_board, char**& opponent_board);
bool check_collision(char**& const board, int x, int y, int direction, ShipOptions shipOptions);

int main()
{
	initialize_ships();

	char** boardA = nullptr;
	char** boardB = nullptr;

	create_board(boardA);
	create_board(boardB);

	

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

	while (true)
	{
		turn(boardA, boardB);
		if (game_over)
		{
			cout << "Player A WIN!!" << endl;
			break;
		}

		turn(boardB, boardA);
		if (game_over)
		{
			cout << "Player B WIN!!" << endl;
			break;
		}

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
		cout << "Place -  " << shipOptions[i].name << "'s" << endl;

		for (int j = 0; j < shipOptions[i].count; j++)
		{
			int x, y;

			cout << "Place " << shipOptions[i].name << " # " << j + 1 << endl;

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

			//TODO#2: проверить коллизии x,y, direction, shipOptions[i]
			while (check_collision(board, x, y, direction, shipOptions[i]))
			{
				cout << "This part of grid is engaged. Please, choose another coordinates" << endl;

				cout << "Place " << shipOptions[i].name << " # " << j + 1 << endl;

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

				direction = -1;
				while (direction != 0 && direction != 1)
				{
					cout << "Chose direction: 0 - horizontal, 1 - vertical" << endl;
					cin >> direction;
				}
			}

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

		}
	}

}

void turn(char**& player_board, char**& opponent_board)
{
	//turn(char**& player_board, char**& opponent_board)
	//4. Ход Игрока А
	//4.1 Показываем поле другого игрока(вторую часть player_board)
	//4.2 Спрашиваем куда игрок хочет сделать выстрел (x,y)
	//4.3 Проверяем есть ли у другого игрока что-то в этой позиции
	//4.4 Если есть - проверяем если ли у игрока Б еще корабли, если нет то gameOver = true; 

	
	system("cls");

	cout << "YOUR BOARD:" << endl;
	for (int i = 0; i < (BOARD_HEIGHT-1)/2; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			cout << player_board[i][j];
		}
		cout << endl;
	}

	cout << "OPPONENT BOARD" << endl;
	for (int i = 11; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			cout << player_board[i][j];
		}
		cout << endl;
	}
	cout << "Enter (x,y)" << endl;
	int x, y;

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

	//выстрел можно произвести
	if (opponent_board[x][y] == SHIP)
	{
		//он попал
		player_board[x + 11][y] = HIT;
		opponent_board[x][y] = HIT;
		cout << "HIT" << endl;
		cout << "Press Enter for change player" << endl;
		int t;
		cin >> t;
		bool is_game_continue = false;
		for (int i = 0; i < (BOARD_HEIGHT - 1) / 2; i++)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				if (opponent_board[i][j] == SHIP)
				{
					is_game_continue = true;
					break;
				}				
			}
			if (is_game_continue)
			{
				break;
			}			
		}

		if (!is_game_continue)
		{
			game_over = true;
			return;
		}
	}
	if (opponent_board[x][y] == WATER)
	{
		//он не попал
		player_board[x + 11][y] = MISS;
		opponent_board[x][y] = MISS;
		cout << "MISS" << endl;
		cout << "Press Enter for change player" << endl;		
		char t;
		cin >> t;
		
	}

}

/// <summary>
/// Проверяет коллизии с другими кораблями при размещении.
/// </summary>
/// <param name="board">Поле игрока</param>
/// <param name="x">Координата Х </param>
/// <param name="y">Координата Y</param>
/// <param name="direction">Направление размещения</param>
/// <param name="shipOptions">Размещаемый корабль</param>
/// <returns>если новый корабль попадает в занятую клетку, либо в соседнюю с другим кораблём - true, если размещение по правилам возможно - false</returns>
bool check_collision(char**& const board, int x, int y, int direction, ShipOptions shipOptions)
{
	if (direction == 0)
	{
		for (int i = 0; i < shipOptions.length; i++)
		{
			if (board[x][y + i] == SHIP)
			{
				return true;
			}
		}
	}

	if (direction == 1)
	{
		for (int i = 0; i < shipOptions.length; i++)
		{
			if (board[x + i][y] == SHIP)
			{
				return true;
			}
		}
	}

	return false;
}

void initialize_ships()
{
	shipOptions[0].name = "CARRIER"; shipOptions[0].length = 2; shipOptions[0].count = 1;
	shipOptions[1].name = "CRUISER"; shipOptions[1].length = 3; shipOptions[1].count = 1;
	/*shipOptions[2].name = "BATTLESHIP"; shipOptions[2].length = 4; shipOptions[2].count = 2;
	shipOptions[3].name = "DESTROYER"; shipOptions[3].length = 5; shipOptions[3].count = 1;*/
}

