#include <iostream>
#include <string.h>
using namespace std;

const int BOARD_HEIGHT = 21; //rows
const int BOARD_WIDTH = 10; //columns
const int SHIP_TYPES = 4;

const char WATER = '.';
const char SHIP = ' +';
const char HIT = 'X';
const char MISS = '0';
const char SPACER = ' ';

//âñå ñòðóêòóðû, ñïèñêè, êîòîðûå ïîçæå íóæíî âûíåñòè â çàãîëîâî÷íûé ôàéë
struct ship
{
	string name;
	int length;
	int count;
}ship[SHIP_TYPES];

enum class POSITION
{
	horizontal = 0,
	vertical = 1
};



//4444
//ïðåäâàðèòåëüíîå îáúÿâëåíèå âñåõ ôóíêöèé
void greeting();
void initialize_ships();
void create_board(char**& board, char BOARD_HEIGHT, char BOARD_WIDTH);
void print_board(char** board, char BOARD_HEIGHT, char BOARD_WIDTH);
void dispose(char**& board, char BOARD_HEIGHT, char BOARD_WIDTH);
void place_ship_on_board(char** board, char BOARD_HEIGHT, char BOARD_BOARDWIDTH, struct ship, int h, int w, POSITION position, int shipType, char SHIP_TYPES);






int main()
{
	char** boardA = nullptr;
	greeting();
	create_board(boardA, BOARD_HEIGHT, BOARD_WIDTH);
	void place_ship_on_board(char** board, char BOARD_HEIGHT, char BOARD_BOARDWIDTH, struct ship, int h, int w, POSITION position, int shipType, char SHIP_TYPES);
	print_board(boardA, BOARD_HEIGHT, BOARD_WIDTH);

	bool game_over = false;
	while (!game_over)
	{
		//îñíîâíîé èãðîâîé öèêë
		//1. Ïðèâåòñòâèå. 
		//2. Ðàçìåùåíèå êîðàáëåé
		//3. Êòî ïåðâûé õîäèò?
		//4. Õîä èãðîêà
		//4.1 ....
	}
	dispose(boardA, BOARD_HEIGHT, BOARD_WIDTH);
	return 0;
}






//ÔÓÍÊÖÈÈ

//ôóíêöèè êàñàþùèåñÿ äîñêè
void greeting()
{
	cout << "        INSTRUCTION        \n";
	//some instruction
}

// âûäåëÿåì ïàìÿòü - âûçîâè dispose
void create_board(char**& board, char BOARD_HEIGHT, char BOARD_WIDTH)
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

void print_board(char** board, char BOARD_HEIGHT, char BOARD_WIDTH)
{


	for (int i = 0; i < (BOARD_HEIGHT); i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

void dispose(char**& board, char BOARD_HEIGHT, char BOARD_WIDTH)
{
	//îñâîáîæäåíèå ðåñóðñîâ
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


//ôóíêöèè êàñàþùèåñÿ êîðàáëåé
void initialize_ships()
{
	ship[0].name = "CARRIER"; ship[0].length = 2; ship[0].count = 4;
	ship[1].name = "CRUISER"; ship[1].length = 3; ship[1].count = 3;
	ship[2].name = "BATTLESHIP"; ship[2].length = 4; ship[2].count = 2;
	ship[3].name = "DESTROYER"; ship[3].length = 5; ship[3].count = 1;
}

void place_ship_on_board(char** board, char BOARD_HEIGHT, char BOARD_BOARDWIDTH, struct ship, int h, int w, POSITION position, int shipType, char SHIP_TYPES)
{
	//âûáèðàåì êîðàáëü, êîòîðûé õîòèì óñòàíîâèòü
	//êàê ñäåëàòü äâà ñâÿçàííûõ ñâèò÷à, ÷òîá ñíà÷àëà âûáðàòü êîðàáëü, à ïîòîì íàïðàâëåíèå (êàê ñîêðàòèòü êîä?)
	while (SHIP_TYPES > 0)
	{
		cout << "Enter the number of ship: 0 \n  0 for CARRIER \n 1 for CRUISER \n 2 for BATTLESHIP \n 3 for DESTROYER \n" << endl;
		cin >> shipType;
		--SHIP_TYPES;
		switch (shipType)
		{
		case 0:
			if (position == POSITION::horizontal)
			{
				for (int i = 0; i < ship[0].length; i++)
				{
					board[h][w + i] = SHIP;
				}
			}
			if (position == POSITION::vertical)
			{
				for (int i = 0; i < ship[0].length; i++)
				{
					board[h + i][w] = SHIP;
				}
			}
		case 1:
			if (position == POSITION::horizontal)
			{
				for (int i = 0; i < ship[1].length; i++)
				{
					board[h][w + i] = SHIP;
				}
			}
			if (position == POSITION::vertical)
			{
				for (int i = 0; i < ship[1].length; i++)
				{
					board[h + i][w] = SHIP;
				}
			}
		case 2:
			if (position == POSITION::horizontal)
			{
				for (int i = 0; i < ship[2].length; i++)
				{
					board[h][w + i] = SHIP;
				}
			}
			if (position == POSITION::vertical)
			{
				for (int i = 0; i < ship[2].length; i++)
				{
					board[h + i][w] = SHIP;
				}
			}
		case 4:
			if (position == POSITION::horizontal)
			{
				for (int i = 0; i < ship[3].length; i++)
				{
					board[h][w + i] = SHIP;
				}
			}
			if (position == POSITION::vertical)
			{
				for (int i = 0; i < ship[3].length; i++)
				{
					board[h + i][w] = SHIP;
				}
			}
		}
	}
}
