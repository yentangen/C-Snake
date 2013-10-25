//Tang-En Yen
//Snake.h

#ifndef SNAKE_H
#define SNAKE_H
#define WIDTH 80
#define HEIGHT 24
#define DELAY 25000000

#include <stdio.h> 
#include <conio.h> 
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char screen[HEIGHT][WIDTH];			//Width and height defined above
char direction[HEIGHT][WIDTH];
time_t start,timediff;
int speedup;
int speed_flag;
int gameover;
int score;

//Snake information
int snake_length;
char snake_direction;			//r,l,u,d... self-explanatory directions
int posX;
int posY;
int tailX,tailY;
int flag;									//a flag for whether to add to tail

void calculate_new_tail();
int check_dir(char dir_input);
void clear_screen( );
void draw_screen( );
void elongate_flag( );
void generate_food( );
void gotoxy(short x, short y);
void initialize( );
void intro();
void move_snake( );

void game_over( );
int random(int dimension);
#endif
