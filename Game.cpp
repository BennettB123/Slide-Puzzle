#include <iostream>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include "Board.h"


int main(void){


	// Asking user for size of puzzle
	cout << "Length of puzzle (2-10): ";
	string length;
	cin >> length;
	while(stoi(length) < 2 || stoi(length) > 10){
		if(stoi(length) < 2){
			cout << "\nMust be at least 2, please pick again: ";
			cin >> length;
		}
		else{
			cout << "\nMust be no more than 10, please pick again: ";
			cin >> length;
		}
	}

	cout << "\nHeight of puzzle (2-10): ";
	string height;
	cin >> height;
	while(stoi(height) < 2 || stoi(height) > 10){
		if(stoi(height) < 2){
			cout << "\nMust be at least 2, please pick again: ";
			cin >> height;
		}
		else{
			cout << "\nMust be no more than 10, please pick again: ";
			cin >> height;
		}
	}

	// Creating Board object and setting up window
	Board board(stoi(length), stoi(height));

	//creating line numbers
	int instructLine = 1;
	string instructions = "Use arrow keys to move numbers, or press 'q' to quit";
	int puzzleLine = instructLine + 2;
	int movesLine = puzzleLine + (2 + (board.getHeight() * 2)); //calculation to get 2 lines under the puzzle
	int messageLine = movesLine + 2;;

	initscr(); //initialize screen 
	clear(); //clear screen
	noecho(); //don't echo any keypresses to console
	cbreak(); //input is immediately passed to window (return is not needed)
	curs_set(FALSE); //don't display a cursor
	keypad(stdscr, TRUE); //enabling keypad use (needed for arrow keys)
	

	// Begin playing Game (infinite loop until game is won & key is pressed)
	while(1){

		// Printing instructions and puzzle
		mvprintw(instructLine, 0, instructions.c_str());
		mvprintw(puzzleLine, 0, board.toString().c_str());
		string pMoves = "Moves: " + to_string(board.getTotalMoves());
		mvprintw(movesLine, 0, pMoves.c_str());

		//getting next move (arrow keys)
		int ch;
		ch = getch();

		clear();

		//evaluating user's input
		switch(ch){
			case KEY_LEFT:
				if(board.canMoveLeft()){
					board.moveLeft();
				}
				else{
					mvprintw(messageLine, 0, "Cannot move Left");
				}
				break;

			case KEY_RIGHT:
				if(board.canMoveRight()){
					board.moveRight();
				}
				else{
					mvprintw(messageLine, 0, "Cannot move Right");
				}
				break;

			case KEY_UP:
				if(board.canMoveUp()){
					board.moveUp();
				}
				else{
					mvprintw(messageLine, 0, "Cannot move Up");
				}
				break;

			case KEY_DOWN:
				if(board.canMoveDown()){
					board.moveDown();
				}
				else{
					mvprintw(messageLine, 0, "Cannot move Down");
				}
				break;

			default:
				mvprintw(messageLine, 0, "Invalid choice. please pick again.");
				break;
		}
		
		//ascii codes for 'q' & 'Q' to quit the program
		if(ch == 81 || ch == 113){
			break;
		}

		//check for win
		if(board.isSolved()){
			clear();
			mvprintw(instructLine, 0, instructions.c_str());
			mvprintw(puzzleLine, 0, board.toString().c_str());
			pMoves = "Moves: " + to_string(board.getTotalMoves());
			mvprintw(movesLine, 0, pMoves.c_str());

			string str = "Congratulations! You solved the puzzle!";
			str += "\n\nPress any button to exit";
			mvprintw(messageLine, 0, str.c_str());
			refresh();

			ch = getch(); //wait for input
			break;
		}	

	refresh();

	//end of game loop
	}

	endwin();

}
