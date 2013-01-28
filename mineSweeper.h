#define MAX_BOARD_DIM 		20

#define EASY_LEVEL_PERCENT	12
#define MEDIUM_LEVEL_PERCENT	16
#define HARD_LEVEL_PERCENT	21

//possible values of level argument in populateMines
enum
{
	EASY = 1,
	MEDIUM,
	HARD
};

//defines a boolean (doesn't exist natively in c) for the following functions.
typedef enum
{
	FALSE = 0,
	TRUE
} bool;

//possible keys during game
typedef enum
{	
	FLAG_TILE  	= ' ',
	CLICK_TILE 	= 'e',
	QUIT		= 'q',
	LEFT		= 'a',
	RIGHT		= 'd',
	UP			= 'w',
	DOWN		= 's'
} Command;

typedef struct
{
	bool isVisible, isMine, isFlagged;
	int numOfMines;
} Tile;

typedef struct
{
	Tile **board;
	int rows, cols, totalMines, hiddenTiles;
	bool isMineClicked;
} GameBoard;

bool initBoard(GameBoard *g, int rows, int cols, int level); //returns true upon success
void clickTile(GameBoard *g, int row, int col);
void flagTile(GameBoard *g, int row, int col);
void populateMines(GameBoard *g, int level);
void markNumbers(GameBoard *g);
void printBoard(GameBoard *g, int cursorCoords[2]);

//added signatures to avoid implicit function warning
void printInfo(GameBoard *g);
void printUncoveredBoard(GameBoard *g);
void destroyBoard(GameBoard *g);