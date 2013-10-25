//Tang-En Yen

/*------------------------------------------------------------------------------

                            Snake

Started May 12, 2013. 

Up = I
Down = K
Left = J
Right = L

Game with raw mechanics finished 8:30pm Monday, May 13, 2013

------------------------------------------------------------------------------*/

#include "screen.c"

/*
The key feature to this program. This creates a matrix the same size as the
playable screen. Each location will contain a direction up, down, left, or right
OR null. This matrix will be initiated with all null values except for the
starting position. As the snake changes direction, the position of the head on
the screen will update the value according to which direction the snake presses.

Note to self: disallow the user to change direction based on the opposite of 
							where they are going, ie if snake_direction = 'r', ignore all left
							keys, and etc.

*/
	
void reset_game() {
	int i,j;

	//Generate screen boundaries and set direction matrix to all null ('n')
	for (i=0;i<HEIGHT;i++) {
		for (j=0;j<WIDTH;j++)
			if (i == 0 || i == (HEIGHT-1) ) 
				screen[i][j] = '-';
			else if (j == 0 || j == (WIDTH-1) ) 
					screen[i][j] = '|';
			else
					screen[i][j] = ' ';
		direction[i][j] = 'n';			//direction will all be set to null
	}
	
	intro();
	getch();
}	
	
int main(int argc,char* argv[])
{
	int i;
	int ch,dir;         						//ch = key input (arrow keys)
	start = time(NULL);
	while (1) {
		reset_game();	
		clear_screen();
		initialize();	//draws screen, initializes variables and default times
		
		while(gameover) {
			if (snake_length%5 == 0 && speed_flag) {	
				speedup += 2500000;
				speed_flag = 0;
			}
			for (i=0;i<DELAY-speedup;i++);	//DELAY may be altered to speed up game
			//reads all characters in buffer. direction variable is set to last pressed
			//user input. This may cause errors and if it does, implement a check on
			//every valid input such that dir does not update values on bogus input.
			//while (1) 
			//	if ( (ch = getchar()) != EOF) dir = ch;
			//	else	break;
			if (kbhit())
				dir = getch();
			
			//if direction is opposite of current snake direction, ignore and the snake
			//should proceed in its original direction. The function check_dir(dir) will
			//determine this.
			if ( check_dir(dir) )		//if it is a valid input AND valid direction
				snake_direction = dir;
			
			//Update position matrix: the location corresponding to snake head position
			//will be set to current snake direction.
			direction[posY][posX] = snake_direction;
			//moves the snake: Update snake position on screen
			move_snake();
	
		}
	}
	return 0;
}
