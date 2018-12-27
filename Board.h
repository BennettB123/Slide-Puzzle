/* 
 *  GAME BOARD HEADER FILE
 *
 *	This is a class to represent the sliding puzzle
 *
 *	The solved puzzle (4 x 4)  will look like this:
 *	 -------------
 *	 |1 |2 |3 |4 |
 *   |--|--|--|--|
 *	 |5 |6 |7 |8 |
 *	 |--|--|--|--|
 *	 |9 |10|11|12|
 *   |--|--|--|--|
 *	 |13|14|15|  |
 *   -------------
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

using namespace std;

class Board {
	private:

		vector<vector<int>> board;
		vector<vector<int>> solvedBoard;
		int totalMoves;
		int LENGTH;
		int HEIGHT;
		int blankLength;
		int blankHeight;

	public:

		Board(int l, int h); //paramatorial constructor (l is LENGTH, h is HEIGHT)

		int getTotalMoves(); //getter for totalMoves
		int getLength(); //getter for LENGTH
		int getHeight(); //getter for HEIGHT
		int getBlankLength(); //getter for blankLength
		int getBlankHeight(); //getter for blankHeight

		void setLength(int i); //setter for LENGTH
		void setHeight(int h); //setter for HEIGHT
		void setTotalMoves(int m); //setter for totalMoves
		void setBlankHeight(int h); //setter for blankHeight
		void setBlankLength(int l); //setter for blankLength
		void findBlankTile(); //setter for blankLength and blankHeight (searches entire board)
		void setSolvedBoard(); //setter for solvedBoard

		void incrementMoves(); //add 1 to totalMoves

		bool canMoveLeft(); //checks if a left move is valid
		bool canMoveRight(); //checks if a right move is valid
		bool canMoveUp(); //checks if a up move is valid
		bool canMoveDown(); //checks if a down move is valid

		void moveLeft(); //swaps the empty piece with the piece to its left
		void moveRight(); //swaps the empty piece with the piece to its right
		void moveUp(); //swaps the empty piece with the piece above it
		void moveDown(); //swaps the empty piece with the piece below it

		void scrambleBoard(); //scrambles the board
		bool isSolvable(); //checks if the current state of the board is possible to solve

		bool isSolved(); //checks the puzzle for a win

		void swap(int& l, int& r); //swaps 2 integers

		string toString(); //returns a string to represent the board

};


#endif
