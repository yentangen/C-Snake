//Tang-En Yen
//screen.c
#include "screen.h"

void calculate_new_tail() {
	//based on the direction matrix, use that to determine the location of the
	//next tail.
	switch (direction[tailY][tailX]) {
		case 'i':	//up
			tailY--;
			break;
		case 'k':	//down
			tailY++;
			break;
		case 'j':	//left
			tailX--;
			break;
		case 'l':	//right
			tailX++;
			break;
		default:
			return;
	}
	
}

int check_dir(char dir_input) {
	if ( (char)dir_input == snake_direction )	return 0;
	
	switch ((char)dir_input) {
		case 'i':	//up
			if (snake_direction == 'k')	return 0;
			else return 1;
			break;
		case 'k':	//down
			if (snake_direction == 'i')	return 0;
			else return 1;
			break;
		case 'j':	//left
			if (snake_direction == 'l')	return 0;
			else return 1;
			break;
		case 'l':	//right
			if (snake_direction == 'j')	return 0;
			else return 1;
			break;
		default:
			return 0;
	}
	
	return 0;
}

void clear_screen ( ){
  DWORD n;                         /* Number of characters written */
  DWORD size;                      /* number of visible characters */
  COORD coord = {0};               /* Top left screen position */
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  /* Get a handle to the console */
  HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

  GetConsoleScreenBufferInfo ( h, &csbi );

  /* Find the number of characters to overwrite */
  size = csbi.dwSize.X * csbi.dwSize.Y;

  /* Overwrite the screen buffer with whitespace */
  FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
  GetConsoleScreenBufferInfo ( h, &csbi );
  FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

  /* Reset the cursor to the top left position */
  SetConsoleCursorPosition ( h, coord );
}


void draw_screen() {
	int i,j;
	//output window to console screen
	for (i=0;i<HEIGHT;i++)
		for (j=0;j<WIDTH;j++) {
			printf("%c",screen[i][j]);
		}
}

void elongate_flag() {
	//The snake has just eaten a unit of food. Wait until rest of body moves over
	//that position before adding an extra '*' to that position. Possibly set a
	//flag and then continuously check until screen becomes ' ' and then call the
	//actual function, elongate_commit()??
	snake_length++;
	speed_flag = 1;
}

void generate_food( ) {
	int x_pos = posX,y_pos = posY;
	while ( (x_pos == posX && y_pos == posY) ||
					(screen[y_pos][x_pos] == '*') 			) {
		x_pos = random(WIDTH);
		y_pos = random(HEIGHT);
	}
	gotoxy(x_pos,y_pos);
	printf("%c", '~');
	screen[y_pos][x_pos]='~';
	gotoxy(posX,posY);
}

//Defines gotoxy() for ANSI C compilers.
void gotoxy(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void initialize( ) {
	draw_screen();													//draws borders
	posX = WIDTH/2;
	posY = HEIGHT/2;
	gotoxy(posX,posY);
	screen[posY][posX]='*';								
	printf("*");														//prints start of snake at center
	direction[posY][posX]='l';							//sets starting position direction
	snake_length = 1;												//snake is 1 unit long
	snake_direction = 'l';									//snake is initially travelling right
	tailX = posX;														//x position of tail
	tailY = posY;														//y position of tail
	speedup = 0;														//no speedup initially
	generate_food();
	flag = 0;																//snake has not eaten yet
	speed_flag=0;
	gameover = 1;
	score = 0;
}

void move_snake() {
	//The program essentially moves the snake by removing the tail and adding it
	//to the head. This reduces overhead required by moving the whole snake a
	//unit in its proper direction.
	//does boundary checks based on direction
	switch (snake_direction) {
		case 'j':	//left
			if ( posX-1 == 0  ||
					 screen[posY][posX-1] == '*' ) { game_over(); return; }
			gotoxy(--posX,posY);
			break;
		case 'l':	//right
			if ( posX+1 == (WIDTH-1) ||
					 screen[posY][posX+1] == '*' ) { game_over(); return; }
			gotoxy(++posX,posY);
			break;
		case 'i':	//up
			if ( posY-1 == 0 ||
					 screen[posY-1][posX] == '*' ) { game_over(); return; }
			gotoxy(posX,--posY);
			break;
		case 'k':	//down
			if ( posY+1 == (HEIGHT-1) ||
					 screen[posY+1][posX-1] == '*' ) { game_over(); return; }
			gotoxy(posX,++posY);
			break;
		default:
			return;
	}
	
	if (screen[posY][posX]=='~')	{ //snake eats food. Keep tail as is
		elongate_flag();
		generate_food();
		score += 5;
	}
	else {													//Erase tail
		gotoxy(tailX,tailY);
		printf(" ");
		screen[tailY][tailX]=' ';
		calculate_new_tail();
		gotoxy(posX,posY);
	}
	
	//prints head to next position
	printf("*");
	screen[posY][posX]='*';
}


void game_over() {
	int i;
	char trash;
	clear_screen();
	gotoxy((WIDTH/2) - 16,HEIGHT/2);
	printf("GAME OVER           Score: %d\n",score);
	gotoxy((WIDTH/2) - 24,HEIGHT/2+2);
	for (i=0;i<1000000000;i++);
	while (kbhit())
		trash = getch();
	printf("Press 'q' to quit game, or any key to return to menu.");
	trash = getch();
	if (trash == 'q')
		exit(0);
	clear_screen();
	gameover = 0;
}

void intro() {
	gotoxy(20,HEIGHT/2-3);
	printf("Welcome to Snake v1.1!               **********");
	gotoxy(20,HEIGHT/2-2);
	printf("I = up                        ****   *        *");
	gotoxy(20,HEIGHT/2-1);
	printf("K = down                         *****        *");
	gotoxy(20,HEIGHT/2);
	printf("J = left                                      *");
	gotoxy(20,HEIGHT/2+1);
	printf("L = right                                     ***        ~");
	gotoxy(20,HEIGHT/2+3);
	printf("Press any key to begin playing...");

	gotoxy(10,HEIGHT/2+10);
	printf("Created by Tang-En Yen using C in Dev-C++. Revisions pending.");
}

int random(int dimension) {	//dimension = WIDTH or HEIGHT
	srand( time(NULL) );
	int randnum = 0;
	rand();rand();rand();		//throws away first three values
	while (randnum == 0 || randnum >= dimension-1 )
		randnum = (int)( (double)rand() / ((double)RAND_MAX + 1) * dimension );
	return randnum;
}
