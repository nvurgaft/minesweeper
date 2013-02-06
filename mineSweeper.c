/**
*	
*	Minesweeper for CLI-UNIX interfaces
*	- mineSweeper.c
*
*	original author: eli
*	maintainer: nick	
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <mineSweeper.h>
#include <colorPrint.h>
#include <time.h>

int flags=0;

bool initBoard(GameBoard *g, int rows, int cols, int level) {
   	if (rows<4 || cols<4 || rows>MAX_BOARD_DIM || cols>MAX_BOARD_DIM) {
   		printf("ERROR: invalid board size.\nSize should be at least 4 by 4 up to 20 by 20!\n");
   		return 1;
	}

   	if (level<1 || level>3) {
   		printf("ERROR: invalid level! should be a value between 1 to 3\n");
   		return 1;
   	}
   	g->rows=rows;
   	g->cols=cols;
   
   //dynamically allocate the board tiles
   	g->board = (Tile **) malloc(rows*sizeof(Tile *));
   	int i, j;
   	for (i=0; i<rows; i++)
   	{
    	g->board[i] = (Tile *) malloc(cols*sizeof(Tile));
   	}
   	
   	//zero the values
	for (i=0; i<rows; i++) {
   		for (j=0; j<cols; j++) {
   			g->board[i][j].numOfMines = 0;
   			g->board[i][j].isMine = 0;
   			g->board[i][j].isVisible = 0;
   		}
   	}
   	g->totalMines=0;
   	g->isMineClicked=0;
   	g->hiddenTiles = rows*cols; // if hidden tiles == #mines then victory condition

   	if (level==1) populateMines(g, EASY_LEVEL_PERCENT);
   	if (level==2) populateMines(g, MEDIUM_LEVEL_PERCENT);
   	if (level==3) populateMines(g, HARD_LEVEL_PERCENT);

   	markNumbers (g);
   	
   	return 0;
}

void populateMines(GameBoard *g , int percent) {
    int mine_count = (((g->rows*g->cols)*percent)/100); //defines the amount of mines
    
    srand(time(NULL));
    int mc; // mine count
    for (mc=0; mc<mine_count; mc++) //generating random indexes ij
    {
		int i = rand() % g->rows;
		int j = rand() % g->cols;
		
		if (g->board[i][j].isMine==1) //evoiding alrady populated fields
		    mc--;
		else {
			g->board[i][j].isMine = 1;
			g->board[i][j].numOfMines = -1;
			g->totalMines++;
		}
    }
}

void markNumbers(GameBoard *g) {
    int i , j ;
    
    for (j=0; j < g->cols; j++) 
    {
		for(i=0; i < g->rows; i++)
		{    
		    if (g->board[i][j].isMine==1)  //if the title hides a mine
		    {
				if(i < g->cols-1) // go right
					g->board[i+1][j].numOfMines++;

				if(i > 0) //go left
					g->board[i-1][j].numOfMines++;

				if(j < g->rows-1) //go down
					g->board[i][j+1].numOfMines++;

				if(j > 0) //go up
					g->board[i][j-1].numOfMines++;

				if(i < g->cols-1 && j<g->rows-1)// go right down
					g->board[i+1][j+1].numOfMines++;

				if(i < g->cols-1 && j>0 ) //go rigt and up
					g->board[i+1][j-1].numOfMines++;

				if(i > 0 && j>0 ) // go left and up
					g->board[i-1][j-1].numOfMines++;

				if(i > 0 && j<g->rows-1 ) //go left and down 
					g->board[i-1][j+1].numOfMines++;				
		    }
		}
	}
}

void clickTile(GameBoard *g, int row, int col) {
    
	// if the tile has no neighbouring mines AND is covered (0 value)..
    if ( g->board[row][col].numOfMines==0 && g->board[row][col].isVisible==FALSE)
    {
		if (row < g->rows-1 && g->board[row][col].numOfMines==0 && g->board[row+1][col].numOfMines>=0 && g->board[row+1][col].isVisible<=0) { //can go right
			g->board[row][col].isVisible=1;
			clickTile(g, row+1, col);
		}
		if (col < g->cols-1 && g->board[row][col].numOfMines==0 && g->board[row][col+1].numOfMines>=0 && g->board[row][col+1].isVisible==0) { //can go down
			g->board[row][col].isVisible=1;
			clickTile(g, row, col+1);
		}
		if (row > 0 && g->board[row][col].numOfMines==0 && g->board[row-1][col].numOfMines>=0 && g->board[row-1][col].isVisible<=0) { //can go left
			g->board[row][col].isVisible=1;
			clickTile(g, row-1, col);
		}
		if (col > 0 && g->board[row][col].numOfMines==0 && g->board[row][col-1].numOfMines>=0 && g->board[row][col-1].isVisible<=0) { //can go up
			g->board[row][col].isVisible=1;
			clickTile(g, row, col-1);
		}

		g->board[row][col].isVisible=TRUE;
    }

    // if the tile neighbours a mine and is covered (0 < value)..
	if ( g->board[row][col].numOfMines>0 && g->board[row][col].isVisible==FALSE)
	{
		g->board[row][col].isVisible=TRUE;
	}

	// if the tile is uncovered then don't do anything
    if (g->board[row][col].isVisible==TRUE) return;
    // if the tile is flagged then it shouldn't be uncovered
    else if (g->board[row][col].isFlagged==TRUE) return;
    // if the tile is a mine, set the losing condition
    else if (g->board[row][col].isMine==TRUE) {
    	g->board[row][col].isVisible = 1;
    	g->isMineClicked = 1;
    }
    // uncover the tile
    else {
    	g->board[row][col].isVisible=1;
    	g->board[row][col].isFlagged=0;
    } 
}

void flagTile(GameBoard *g, int row, int col) {
   
   // if the tile is covered
   if(g->board[row][col].isVisible==FALSE)
   {
   		// if the tile is flagged
		if(g->board[row][col].isFlagged==FALSE) {
	    	g->board[row][col].isFlagged=TRUE;
	    	flags++;
	    }
		else {
	    	g->board[row][col].isFlagged=FALSE;
	    	flags--;
	    }
   }
}

void printBoard(GameBoard *g, int cursorCoords[2]) {
    int i , j ;
    char format[3];
    format[0]=' ';
    format[1]=' ';
    format[2]='\0';
    
    for (i=0; i<g->cols; i++) {
		for(j=0; j<g->rows; j++) {
		   	if (i==cursorCoords[0] && j==cursorCoords[1] && g->isMineClicked==FALSE) // if user and a mine isn't clicked
		    {
				format[0]=' ';
				format[1]='*';
				format[2]='\0';
		    
				colorPrint(FG_Black, BG_Yellow, ATT_Def, (char*) &format);
		    }

		    else if (g->board[i][j].isFlagged==TRUE) // flag
		    {
				format[0]=' ';
				format[1]='F';
				format[2]='\0';
		    
				colorPrint(FG_Black, BG_Green, ATT_Def, (char*) &format);
		    } 
		    else if (g->board[i][j].isMine==1 && g->board[i][j].isVisible==1) // mine hit
		    {
				format[0]=' ';
				format[1]='M';
				format[2]='\0';
				g->isMineClicked=1;
		    
				colorPrint(FG_Black, BG_Red, ATT_Def, (char*) &format);
		    } 
		    else if (g->board[i][j].isVisible==0) // covered tile
		    {
				format[0]=' ';
				format[1]=' ';
				format[2]='\0';
		    
				colorPrint(FG_White, BG_White, ATT_Def, (char*) &format);
		    }
		    else if (g->board[i][j].isMine==0 && g->board[i][j].isVisible==1) // uncovered numbered tile
		    {
				format[0]=' ';
				format[1]= (char)(((int)'0')+g->board[i][j].numOfMines); //(a safer) int to char casting
				format[2]='\0';
		    
				colorPrint(FG_Black, BG_White, ATT_Def, (char*) &format);
		    }
		}
		printf("\n");
	}  
}

void printInfo(GameBoard *g) {
	g->hiddenTiles = 0;
	int i,j;

	for (i = 0; i < g->rows; i++) {
		for (j = 0; j < g->cols; j++) {
			if (g->board[i][j].isVisible==0) g->hiddenTiles++;
		}
	}

	printf("\n# mines %d, # flags %d, # hidden tiles %d\n", g->totalMines, flags, g->hiddenTiles);
}

void printUncoveredBoard(GameBoard *g) {
    int i , j ;

    printf("\nThis is the board when fully uncovered\nUse for debugging purposes only\n");
    printf("\n\tM - mine\n\t# - the amount of mines surrounding the tile\n\n");
    
    for (i=0; i<g->cols; i++) {
		for(j=0; j<g->rows; j++) { //left table
		   	
		   	if (g->board[i][j].isMine==0) printf("_ ");
		   	else printf("M ");
		}
		printf("\t");

		for(j=0; j<g->rows; j++) {	//right table
		   	
		   	if (g->board[i][j].isMine==0) printf("%d ", g->board[i][j].numOfMines);
		   	else printf("- ");
		}

		printf("\n");
	} 

	printf("Total mines: %d\n",g->totalMines);
}

void destroyBoard(GameBoard *g) {
	int ii;
	for (ii=0; ii < g->rows; ii++) {
		free(g->board[ii]);
	}
	free(g->board);
}
