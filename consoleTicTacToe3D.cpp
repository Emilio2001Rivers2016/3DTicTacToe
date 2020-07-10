/* Start date: July 6th, 2020
 * End date: July 6th, 2020
 * Lines of useful code: 144
 * Emilio Rios Ochoa */
#include <iostream>
#include <string>
#include <fstream>
//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"      /* Yellow */
#define BRED     "\033[1m\033[31m"      /* B Red */
#define BCYAN    "\033[1m\033[36m"      /* B Cyan */
#define BWHITE   "\033[1m\033[37m"      /* B White */
#define PATH_TO_DB "/Users/emiliorios/Desktop/Rivers/EXTRAS/C++_Programs/\
3DTicTacToe/TicTacToeDB.txt"

using namespace std;

/******************************************************************************/
//Class for the cell of each board
class Cell {
	public:
		char value;
		Cell() { value = ' '; }
		~Cell() {}
};

/******************************************************************************/
//Class for the game board
class Board {
	public:
		Board() {
			int s[] = {0,1,2};
			for(int i:s) { for(int j:s) { for(int k:s) {
				Cell newCell;
				board[i][j][k] = newCell;
			}}}
		}
		void displayBoard() {
			string div(9, '-'), spc(5,' ');
			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 3; j++) {
					for(int k = 0; k < 3; k++) {
						cout <<((board[j][i][k].value=='X')?BRED:BCYAN)<<\
						board[j][i][k].value << BWHITE << " | ";
					} cout << "\b\b\b     ";
				} if(i<2) { cout <<'\n'<<div<<spc<<div<<spc<<div<<spc<<'\n'; }
			} cout << endl << RESET;
		}
		bool selectCell(int set, int x, int y, char token) {
			if(board[set][x][y].value == ' ') {
				board[set][x][y].value = token;
				return true;
			} return false;
		}
		bool detectTie() {
			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 3; j++) {
					for(int k = 0; k < 3; k++) {
						if(board[i][j][k].value==' ') { return false; }}}}
			return true;
		}
		bool detectWin(char token) {
			for(int i = 0; i < 3; i++) {
				for(int j = 0; j < 3; j++) {
					int h=0, v=0, bH=0, bV=0, dr=0, dl=0, bDr=0, bDl=0;
					for(int k = 0; k < 3; k++) {
						if(board[i][j][k].value == token) h++;
						if(board[i][k][j].value == token) v++;
						if(board[k][j][k].value == token) bH++;
						if(board[k][k][j].value == token) bV++;
						if(board[i][k][k].value == token) dr++;
						if(board[i][k][2-k].value == token) dl++;
						if(board[k][k][k].value == token) bDr++;
						if(board[2-k][k][2-k].value == token) bDl++;
					}if(h==3||v==3||bH==3||bV==3||dr==3||dl==3||bDr==3||bDl==3)\
					 return true;
				}
			} return false;
		}
		void resetBoard() {
			int s[] = {0,1,2};
			for(int i:s) for(int j:s) for(int k:s) board[i][j][k].value = ' ';
		}
		~Board() {}
	private:
		Cell board[3][3][3];
};

/******************************************************************************/
//Class for the game lifecycle
class Game {
	public:
		Game() {}
		void initGame() {
			cout << YELLOW << " >> G A T O   3 D << " << endl << endl;
			cout << "Segundo juego en C++\nEmilio Rivers\n9 de julio 2020\n\n";
			cout << "Instrucciones:\n-Dos jugadores\n-Para seleccionar la " << \
			"casilla elige las coordenadas del tablero, renglón y columna\n"<< \
			"-Ganas si juntas 3 en línea horizontal, vertical y diagonal, en"<<\
			" uno sólo o en los 3 tableros" << RESET << endl << endl;
		}
		int playGame() {
			int turn = 1;
			board.displayBoard();
			while(true) {
				int T = (turn%2!=0) ? 1 : 2;
				cout << ((T==1)?BRED:BCYAN) << "JUGADOR " << T << RESET << endl;
				int set, x, y;
				while(true) {
					validateInput("Introduce el tablero: ", set, 1, 3);
					validateInput("Introduce la fila: ", x, 1, 3);
					validateInput("Introduce la columa: ", y, 1, 3);
					bool ok = board.selectCell(set-1,x-1,y-1,((T==1)?'X':'O'));
					if(!ok){ cout << "ESPACIO OCUPADO!!!\n"; } else { break; }
				}
				board.displayBoard();
				if(board.detectTie()) return 0;
				if(board.detectWin(((T==1)?'X':'O'))) return T;
				turn++;
			}
		}
		bool endGame(int status) {
			int playAgain;
			ofstream gameDataBase(PATH_TO_DB, ios::app);
			cout << YELLOW;
			if(status == 0) {
				cout << "EMPATE! NADIE GANA..." << endl;
				gameDataBase << "EL JUEGO TERMINÓ EN EMPATE - "<<__DATE__<<"\n";
			} else {
				cout << "GANA EL JUGADOR " << status << "!!" << endl;
				gameDataBase<<"GANA EL JUGADOR "<<status<<" - "<<__DATE__<<"\n";
			} gameDataBase.close();
			cout << RESET;
			board.resetBoard();
			validateInput("Jugar de nuevo? (1=Sí,2=No): ",playAgain,1,2);
			return ((playAgain==1) ? true : false);
		}
		~Game() {}
	private:
		Board board;
		void validateInput(string message, int& var, int inf, int sup) {
			while(true) {
				cout << message;
				if(cin >> var) {
					if(var >= inf && var <= sup) break;
					else cout << "RANGO INVÁLIDO ("<<inf<<"-"<<sup<<")!"<<"\n";
				} else cout << "ENTRADA INVÁLIDA!\n";
				cin.clear(); cin.ignore(256,'\n');
			}
		}
};

/*******************************************************************************
*******************************************************************************/
int main() {
	Game game;
	bool keepPlaying = false;
	game.initGame();
	do {
		int exitStatus = game.playGame();
		keepPlaying = game.endGame(exitStatus);
	} while(keepPlaying);
	return 0;
};
