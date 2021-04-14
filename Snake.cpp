#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;

bool gameOver;
// переменные размера поля игры
const int width = 36;
const int height = 20;
// переменные координат змейки и фруктов
int x, y, fruitX, fruitY;
// переменная счета игры
int score;
// переменные координат хвоста змейки
int tailX[100], tailY[100];
int nTail;
// исчисления перемещений
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dir;
// переменные выборов в меню
int choice, backMenu, afterGame;

// ф-ия настройки нужных параметров
void Setup() {
	gameOver = false;
	score = 0;
	dir = STOP; 
	x = width/2 - 1;
	y = height/2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	nTail = 0;
} 

void GameOver() {
	gameOver = true;
	system("cls"); 
	cout << endl;
	cout << "________________________________________________________________________________"<< endl;
	cout << endl;
	cout << "        |$$$$$ |$$$$$ |$$$$$$$ |$$$$$    |$$$$$ |$  |$ |$$$$$ |$$$$$" << endl;
	cout << "        |$     |$  |$ |$ |$ |$ |$        |$  |$ |$  |$ |$     |$  |$" << endl;
	cout << "        |$|$$$ |$$$$$ |$ |$ |$ |$$$$     |$  |$ |$  |$ |$$$$  |$$$$" << endl;
	cout << "        |$  |$ |$  |$ |$ |$ |$ |$        |$  |$ |$  |$ |$     |$  |$" << endl;
	cout << "        |$$$$$ |$  |$ |$ |$ |$ |$$$$$    |$$$$$  |$$$  |$$$$$ |$  |$" << endl;
	cout << "________________________________________________________________________________"<< endl;
	cout << endl;
	cout << "                            TOTAL SCORE : "<< score << endl;
	cout << endl;
    cout << "                            [1] - TRY AGAIN                               \n";
    cout << "                            [0] - BACK TO MAIN MENU                       \n";
	cout << endl;
    cout << "                            Your choice: ";
    cin >> afterGame;
}
// ф-ия для прорисовки
void Draw() {
	system("cls"); 
	for(int i = 0; i <= (width+1)/2; i++)
		cout << "* ";
	cout << endl;
	
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++){
			if(j == 0 || j == width-1)
				cout << "*";
		 	if(i == y && j == x)
				cout << "O";
			else if(i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for(int k = 0; k < nTail; k++) {
					if(tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o"; 
				    }
				}
				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	
	for(int i = 0; i <= (width+1)/2; i++)
		cout << "* ";
	cout << endl;
	cout << " SCORE: " << score << endl;
	cout << " PRESS [x] TO END THE GAME " << endl;
}
// ф-ия отслеживания нажатий
void Input() {
	if(_kbhit()) {
		switch(getch()) {
			case 'a':
			case 75:
				dir = LEFT;
				break;
			case 'd':
			case 77:
				dir = RIGHT;
				break;
			case 's':
			case 80:			
				dir = DOWN;
				break;
			case 'w':
			case 72:
				dir = UP;
				break;
			case 'x':
				GameOver();
				break;
		}
	}
}
// ф-ия логики самой игры
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	
	for(int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
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
	
	for(int i = 0; i < nTail; i++) {
		if(tailX[i] == x && tailY[i] == y) {
			GameOver();
	   }
	}
		
	if(x == width-1 || x < 0 || y == height || y < 0) {
		GameOver();
    }
	
	if(x == fruitX && y == fruitY) {
		score += 100;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail ++;
	}	
}

void mainMenu() {
	system("cls");
	cout << endl;
	cout << "________________________________________________________________________________\n";
    cout << endl;
	cout << "                            G A M E   M E N U                                  \n";
    cout << "________________________________________________________________________________\n";
    cout << endl;
	cout << "                            [1] - START GAME                                 \n";
    cout << endl;
    cout << "                            [2] - ABOUT GAME                                 \n";
    cout << endl;  
	cout << "                            [3] - QUIT                                       \n";
	cout << endl;
    cout << "                            Your choice: ";
    cin >> choice; 
}

void aboutGame() {
	system("cls"); 
	cout << "________________________________________________________________________________\n";
    //cout << endl;
	cout << "                            A B O U T   G A M E                                  \n";
    cout << "________________________________________________________________________________\n"; 
	cout << "                            Welcome to 'Snake'!\n";
    cout << " - At the beginning of the game, the snake consists of one link\n";
	cout << " - If snakes head bumps into an obstacle (the snake stumbles on\n";
	cout << "   yourself or on the border of the field), the game is lost\n";
	cout << " - At each moment of time there is food on the playing field, occupying\n";
	cout << "   one cell fields\n";
	cout << " - When the snake eats fruit it grows by one link, and on the field in\n";
	cout << "   a new portion of food automatically appears in an arbitrary space   \n";
	cout << " - To control the snake, you can use the keys:\n";
	cout << "	        ^\n";
	cout << "	'w' or '|' to go UP, \n";
	cout << "	'a' or '<-' - LEFT, \n";
	cout << "	'd' or '->' - RIGHT, \n";
	cout << "	's' or '|' - DOWN\n";
	cout << "	        v\n";
	cout << " - When the snake eats fruit, the score is increased by 100 points\n";
	cout << " - To QUIT the game press 'x'\n";
    cout << endl;
    cout << "                            PRESS [0] TO BACK  ";
    cin >> backMenu;
}

// ф-ия работы игры
void game() {
	Setup();
	do {
    	Draw();
		Input();
		Logic();
	} while(!gameOver);
}

int main() {
    do {
        mainMenu();
        
		switch(choice) {
            case 1:
            	do {
	            	game();
    	        	
					switch(afterGame) {
        	    		case 1:
            				game();
            			case 0:
							break;            		
					}
				} while(afterGame != 0);
			    break;
            case 2:
                do {
        			aboutGame();
    			} while(backMenu != 0);
                break;
            case 3:
                break;
        }
    } while(choice != 3);
    return 0;
}
