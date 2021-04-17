#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
// переменные размера поля игры
const int width = 24;
const int height = 24;
// переменные координат змейки и фруктов
int x, y, fruitX, fruitY;
// переменная счета игры
int score, maxScore;
// переменные координат хвоста змейки
int tailX[100], tailY[100];
int nTail;
// исчисления перемещений
enum direction { STOP = 0, LEFT = 1, RIGHT = -1, UP = 2, DOWN = -2};
direction dir;
direction prevdir;
// переменные выборов в меню
char choice, backMenu, afterGame;

int sleep_time = 250;

// ф-ия настройки нужных параметров
void Setup() {
	gameOver = false;
	score = 0;
	dir = STOP; 
	x = width/2 - 1;
	y = height/2 - 1;
	fruitX = rand() % (width-2) + 1;
	fruitY = rand() % (height-2) + 1;
    nTail = 0;
} 

void GameOver() {
	gameOver = true;
	system("cls"); 
	if(score > maxScore) maxScore = score;
	cout << endl;
	cout << "\x1b[33m________________________________________________________________________________"<< endl;
	cout << endl;
	cout << "         |$$$$$$ |$$$$$ |$$$$$$$ |$$$$$    |$$$$$ |$  |$ |$$$$$ |$$$$$" << endl;
	cout << "         |$      |$  |$ |$ |$ |$ |$        |$  |$ |$  |$ |$     |$  |$" << endl;
	cout << "         |$ |$$$ |$$$$$ |$ |$ |$ |$$$$     |$  |$ |$  |$ |$$$$  |$$$$" << endl;
	cout << "         |$   |$ |$  |$ |$ |$ |$ |$        |$  |$ |$  |$ |$     |$  |$" << endl;
	cout << "         |$$$$$$ |$  |$ |$ |$ |$ |$$$$$    |$$$$$  |$$$  |$$$$$ |$  |$" << endl;
	cout << "________________________________________________________________________________\x1b[0m"<< endl;
	cout << endl;
	cout << "                            TOTAL SCORE : " << score << endl;
	cout << "                            RECORD SCORE : " << maxScore << endl;
	cout << endl;
    cout << "                            PRESS THE KEY                                 \n";
    cout << "                            [1] - TRY AGAIN                               \n";
    cout << "                            [0] - BACK TO MAIN MENU                       \n";
   // do {
    	afterGame = getch();
   // } while(afterGame!= '0' || afterGame!= '1' );
}
// ф-ия для прорисовки
void Draw() {
	system("cls"); 
	/*for(int i = 0; i <= (width+1)/2; i++)
		cout << "* ";
	cout << endl;
		
	/*for(int i = 0; i < height-1; i++) {
		for(int j = 0; j < width+1; j++){
			if(j == 0 || j == width)
				cout << "*";
		}
		cout << endl;
	}*/
	
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++){
			
			if(i == 0 || i == height-1 || j == 0 || j == width - 1)
				cout << "\x1b[33m#\x1b[0m";
			else {
			if(i == y && j == x)
				cout << "O";
			else if(i == fruitY && j == fruitX)
				cout << "\x1b[32mF\x1b[0m";
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
		}
		cout << endl;
	}

	/*for(int i = 0; i <= (width+1)/2; i++)
		cout << "* ";*/
	cout << endl;
	cout << " SCORE: " << score << endl;
	cout << " RECORD: " << maxScore << endl;
	cout << " PRESS ANY KEY TO END THE GAME ";
}
// ф-ия отслеживания нажатий
void Input() {
	if(_kbhit()) {
		if(_getch() == 224) {
			if(nTail == 0) {
				switch(_getch()) {
					case 75:
						dir = LEFT;
						break;
					case 77:
						dir = RIGHT;
						break;
					case 80:			
						dir = DOWN;
						break;
					case 72:
						dir = UP;
						break;
				}
				prevdir = dir;
			} else {
				switch(_getch()) {
				
				case 75:
					if(prevdir == RIGHT) break;
					else {
						dir = LEFT;
						break;
				    }
				case 77:
					if(prevdir == LEFT) break;
					else {
						dir = RIGHT;
						break;
					}	
				case 80:
					if(prevdir == UP) break;
					else {			
						dir = DOWN;
						break;
					}
				case 72:
				if(prevdir == DOWN) break;
					else {
						dir = UP;
						break;
					}
				}
				prevdir = dir;
			}
		}
		else GameOver();
	}
}	  

//ф-ия логики игры
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int	prev2X, prev2Y;
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
		
	if(x > width-2 || x < 1 || y > height-2 || y < 1) {
		GameOver();
    }
	
	if(x == fruitX && y == fruitY) {
		score += 100;
		fruitX = rand() % (width-2) + 1;
		fruitY = rand() % (height-2) + 1;
		nTail ++;
	}	
}

void mainMenu() {
	system("cls");
	cout << endl;
	cout << "\x1b[33m________________________________________________________________________________\n";
    cout << endl;
	cout << "                            G A M E   M E N U                                  \n";
    cout << "________________________________________________________________________________\x1b[0m\n";
    cout << endl;
	cout << "                             PRESS THE KEY                                   \n";
	cout << endl;
	cout << "                            [1] - START GAME                                 \n";
    cout << endl;
    cout << "                            [2] - ABOUT GAME                                 \n";
    cout << endl;  
	cout << "                            [3] - QUIT                                       \n";
    choice = getch(); 
}

void aboutGame() {
	system("cls"); 
	cout << "\x1b[33m________________________________________________________________________________\n";
	cout << endl;
    cout << "                            A B O U T   G A M E                                  \n";
    cout << "________________________________________________________________________________\x1b[0m\n"; 
	cout << endl;
	cout << "                            Welcome to 'Snake'!\n";
    cout << " - At the beginning of the game, the snake consists of one link\n";
	cout << " - If snakes head bumps into an obstacle (the snake stumbles on\n";
	cout << "   yourself or on the border of the field), the game is lost\n";
	cout << " - At each moment of time there is food on the playing field, occupying\n";
	cout << "   one cell fields\n";
	cout << " - When the snake eats fruit it grows by one link, and on the field in\n";
	cout << "   a new portion of food automatically appears in an arbitrary space   \n";
	cout << " - To control the snake, you can use the keys:\n";
	cout << "	'^' to go UP, \n";
	cout << "	'<' - LEFT, \n";
	cout << "	'>' - RIGHT, \n";
	cout << "	'v' - DOWN\n";
	cout << " - When the snake eats fruit, the score is increased by 100 points\n";
	cout << " - 'F' on the field marks a fruit to eat\n";
	//cout << " - To QUIT the game press 'x'\n";
	cout << endl;
    cout << "                            PRESS [0] TO BACK  ";
    //cin >> backMenu;
    backMenu = getch();
    
}
void start() {
	system("cls");
	cout << endl;
	cout << "\x1b[33m________________________________________________________________________________\n";
 	cout << endl; 
	cout << endl; 
	cout << endl;
	cout << "                  |$$$$    |$   |$    |$$$    |$  |$   |$$$$$           \n";
	cout << "                  |$       |$$  |$   |$  |$   |$ |$    |$               \n";
	cout << "                  |$$$$$   |$|$ $$   |$$$$$   |$|$     |$$$$            \n";
	cout << "                      |$   |$ |$|$   |$  |$   |$ |$    |$               \n";
	cout << "                  |$$$$$   |$   |$   |$  |$   |$  |$   |$$$$$           \n";
	cout << endl; 
	cout << endl; 
	cout << endl;
	cout << "________________________________________________________________________________\x1b[0m"; 
	Sleep(2000);
}

// ф-ия работы игры
void game() {
	Setup();
	do { 
    	Draw();
   		Input();
		Logic();
		Sleep(sleep_time);
	} while(!gameOver);
}

int main() {
	start();
    do {
        mainMenu();
        
		switch(choice) {
            case '1':
            	game();
            	do {
			if (afterGame == '1') game();
			else if (afterGame == '0') break;
			else afterGame = _getch();     
		} while(afterGame != '0');
		break;
            case '2':
                do {
        		aboutGame();
    		} while(backMenu != '0');
                break;
            case '3':
                break;
            default:
            	break;
        }
    } while(choice != '3');
    return 0;
}            
