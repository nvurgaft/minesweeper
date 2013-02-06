/**
*	
*	Minesweeper for CLI-UNIX interfaces
*	- game.c
*
*	original author: eli
*	maintainer: nick	
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <mineSweeper.h>
#include <getch.h>

// toggle on/off debug mode
const bool DEBUG_MODE = FALSE;

int main ()
{
    int cursorCoords[2]; 
    cursorCoords[0]=0;	// vertical coordiante
    cursorCoords[1]=0;	// horizontal coordinate
    int row ,col,level;
    
    printf("\nplease enter a row number [4-20]: ");
    scanf("%d" ,&row);
    printf("\nplease enter a col number [4-20]: ");
    scanf("%d" ,&col);
    printf("\nplease enter level [1-Easy, 2-Medium, 3-Hard]: ");
    scanf("%d" ,&level);
     
    GameBoard g;

    if (initBoard(&g, row, col, level)==1) return 1;
	Command cmd = 'z'; //some worthless default value to replace possible unwanted garbage value
	
	system("clear"); //"clears" the screen
	while (cmd!=QUIT)
	{                                                   
		system("clear"); //"clears" the screen
		printf("\nMiNESWEEPER.\n\n");

		printBoard(&g, cursorCoords);
		printInfo(&g);
		
		if (g.isMineClicked==1) {
			printf("\nYou just hit a mine, you lost!\n p~x___x#~q\n\n");
			break;
		}
		if (g.hiddenTiles == g.totalMines) {
			printf("\nYou have uncovered all the mines, CONGRATULATIONS!!!\n :D :D :D\n");
			break;
		}
		
		if (DEBUG_MODE) printUncoveredBoard(&g); /* DEBUG CODE */
		printf("your move : ");
		cmd = getche();

		if (DEBUG_MODE) {putchar(cmd); printf("user clicked \n");} /* DEBUG CODE */
		    
		switch (cmd)
		{
			case FLAG_TILE:
			    	flagTile(&g, cursorCoords[0], cursorCoords[1]);
			    	break;
			case CLICK_TILE:
			    	clickTile(&g, cursorCoords[0], cursorCoords[1]);
				   	break;
			case UP:
				   	if(cursorCoords[0]>0)
					cursorCoords[0]--;
				   	break;
			case DOWN:
				   	if (cursorCoords[0] < g.rows-1)
				   	cursorCoords[0]++; 
					break;
			case LEFT:
				    if(cursorCoords[1]>0)
					cursorCoords[1]--;
				   	break;
			case RIGHT:
				   	if(cursorCoords[1]< g.cols-1)
					cursorCoords[1]++;
				   	break;
			case QUIT:
				   	printf("thanks for playing...\tgoodbye!\n");
				   	destroyBoard(&g);
				   	return 0;
				   	break;
			default:
					printf("invalid input, retype command.. \n");
					break;
		}	
	}
    return 0;
}
