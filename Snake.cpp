#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 25, height = 20;
int x, y, fruitx, fruity, score; // Head coordinate, fruit coordinate, and score
int tailx[400], taily[400], nTail; // Tail property
bool available[height+2][width+2] = {1};
enum direction {STOP = 0, LEFT, RIGHT, DOWN, UP}; // Movement
direction dir;

void setup()
{
	for(int i = 0; i < 400; i++){
		tailx[i] = -1;
		taily[i] = -1;
	}
	for(int i = 0; i < height+2; i++){
		for(int j = 0; j < width+2; j++){
			available[i][j] = 1;
		}
	}
	gameOver = 0;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitx = x;
	fruity = y;
	while((x == fruitx && y == fruity) || fruitx >= width || fruitx <= 0 || fruity >= height || fruity <= 0){
		fruitx = rand() % width;
		fruity = rand() % height;
	}
	score = 0;
	nTail = 0;
}

void draw()
{
	// Clearing the screen
	system("cls"); 

	// Drawing the map
	for(int i = 0; i < width + 1; i++){
		cout << "#";
	}
	cout << endl;
	for(int i = 1; i < height; i++){
		cout << "#";
		for(int j = 1; j < width; j++){
			if(i == y && j == x){
				cout << "O";
			} else if(i == fruity && j == fruitx){
				cout << "X";
			} else {
				if(!available[i][j])
					cout << 'o';
				else
					cout << ' ';
			}
		}
		cout << "#";
		cout << endl;
	}
	for(int i = 0; i < width + 1; i++){
		cout << "#";
	}
	cout << endl;

	// Show score
	cout << "Score : " << score << endl;

}

void input()
{
	if(_kbhit()){
		switch(_getch()){
			case 'w':
				if(dir != DOWN){
					dir = UP;
				}
				break;
			case 'a':
				if(dir != RIGHT){
					dir = LEFT;
				}
				break;
			case 'd':
				if(dir != LEFT){
					dir = RIGHT;
				}
				break;
			case 's':
				if(dir != UP){
					dir = DOWN;
				}
				break;
			case 'x':
				gameOver = 1;
				break;
		}
	}
}

void logic()
{
	int prevx = x, prevy = y;
	int prevx2, prevy2;
	for(int i = 0; i < nTail; i++){
		prevx2 = tailx[i];
		prevy2 = taily[i];
		available[taily[i]][tailx[i]] = 1;
		tailx[i] = prevx;
		taily[i] = prevy;
		if(prevx2 != -1 || prevy2 != -1){
			prevx = prevx2;
			prevy = prevy2;	
			available[taily[i]][tailx[i]] = 0;
		}
	}
	switch(dir){
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
	}
	if(x >= width || x <= 0 || y >= height || y <= 0 || !available[y][x]){
		gameOver = 1;
	}
	if(x == fruitx && y == fruity){
		system("color a");
		nTail++;
		score++;
		while((x == fruitx && y == fruity) || fruitx >= width || fruitx <= 0 || fruity >= height || fruity <= 0 || !available[fruity][fruitx]){
			fruitx = rand() % width;
			fruity = rand() % height;
		}
	}
}

int main()
{
	start:
	setup();
	while(!gameOver){
		system("color F");
		logic();
		draw();
		input();
		Sleep(100);
	}
	cout << "Game Over! Press R to restart" << endl;
	while(1){
		if(_kbhit()){
			if(_getch() == 'r'){
				goto start;
			} else {
				break;
			}
		} 
	}

	return 0;	
}
