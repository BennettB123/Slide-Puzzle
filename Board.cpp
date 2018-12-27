#include "Board.h"

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <ncurses.h>


//constructor that takes in the EDGELENGTH as parameter
Board::Board(int l, int h){
	setLength(l);
	setHeight(h);
	setSolvedBoard();
	setTotalMoves(0);

	//fill board
	int num = 1;
	for(int i = 0; i < getHeight(); i++){
		vector<int> temp;
		board.push_back(temp);
		for(int j = 0; j < getLength(); j++){
			board.at(i).push_back(num);
			num++;
		}
	}
	//setting the highest number to zero (this will appear to be blank)
	board.at(getHeight() - 1).at(getLength() - 1) = 0;

	//scramble board
	scrambleBoard();

	//finding/setting blank tile
	findBlankTile();
}

int Board::getTotalMoves(){
	return totalMoves;
}

int Board::getLength(){
	return LENGTH;
}

int Board::getHeight(){
	return HEIGHT;
}

int Board::getBlankLength(){
	return blankLength;
}

int Board::getBlankHeight(){
	return blankHeight;
}

void Board::setLength(int l){
	LENGTH = l;
}

void Board::setHeight(int h){
	HEIGHT = h;
}

void Board::setBlankHeight(int h){
	blankHeight = h;
}

void Board:: setBlankLength(int l){
	blankLength = l;
}

void Board::findBlankTile(){
	int h, l;
	for(int i = 0; i < getHeight(); i++){
		for(int j = 0; j < getLength(); j++){
			if(board[i][j] == 0){
				h = i;
				l = j;
			}
		}
	}

	blankHeight = h;
	blankLength = l;
}

void Board::setTotalMoves(int m){
	totalMoves = m;
}

void Board::incrementMoves(){
	totalMoves++;
}

void Board::setSolvedBoard(){
	int num = 1;
	for(int i = 0; i < getHeight(); i++){
		vector<int> temp;
		solvedBoard.push_back(temp);
		for(int j = 0; j < getLength(); j++){
			solvedBoard.at(i).push_back(num);
			num++;
		}
	}
	solvedBoard.at(getHeight()-1).at(getLength()-1) = 0;
}

bool Board::canMoveLeft(){
	if(getBlankLength() == getLength()-1){
		return false;
	}
	else{
		return true;
	}
}

bool Board::canMoveRight(){
	if(getBlankLength() == 0){
		return false;
	}
	else{
		return true;
	}
}

bool Board::canMoveDown(){
	if(getBlankHeight() == 0){
		return false;
	}
	else{
		return true;
	}
}

bool Board::canMoveUp(){
	if(getBlankHeight() == getHeight()-1){
		return false;
	}
	else{
		return true;
	}
}

void Board::moveRight(){ //swaps the empty piece with the piece to its left
	int l = getBlankLength();
	int h = getBlankHeight();
	swap(board.at(h).at(l), board.at(h).at(l-1));
	setBlankLength(l-1);
	incrementMoves();
}

void Board::moveLeft(){ //swaps the empty piece with the piece to its right
	int l = getBlankLength();
	int h = getBlankHeight();
	swap(board.at(h).at(l), board.at(h).at(l+1));
	setBlankLength(l+1);
	incrementMoves();
}

void Board::moveUp(){ //swaps the empty piece with the piece below it
	int l = getBlankLength();
	int h = getBlankHeight();
	swap(board.at(h).at(l), board.at(h+1).at(l));
	setBlankHeight(h+1);
	incrementMoves();
}

void Board::moveDown(){ //swaps the empty piece with the piece above it
	int l = getBlankLength();
	int h = getBlankHeight();
	swap(board.at(h).at(l), board.at(h-1).at(l));
	setBlankHeight(h-1);
	incrementMoves();
}


// randomly scrambles the board. repeat if board's state is not solvable
void Board::scrambleBoard(){
	srand(time(NULL));

	do{
		//create vector with all numbers on board
		vector<int> nums;
		for(int i = 0; i < getHeight(); i++){
			for(int j = 0; j < getLength(); j++){
				nums.push_back(board[i][j]);
			}
		}
	
		//shuffle elements
		random_shuffle(nums.begin(), nums.end());
	
		//put elements back into board
		for(int i = 0; i < getHeight(); i++){
			for(int j = 0; j < getLength(); j++){
				board[i][j] = nums.back(); //get last element
				nums.pop_back(); //remove last element
			}
		}
	} while(!isSolvable() || isSolved());
}

bool Board::isSolvable(){
	findBlankTile();

	vector<int> numLine; //array to represent the board row by row
	for(int i = 0; i < getHeight(); i++){ //filling numLine with board contents (not the blank space)
		for(int j = 0; j < getLength(); j++){
			if(board[i][j] != 0){
				numLine.push_back(board[i][j]);
			}
		}
	}
	
	//counting number of inversions(swaps between 2 numbers) in the board
	int inversions = 0;
	for(size_t i = 0; i < numLine.size(); i++){
		for(size_t j = i + 1; j < numLine.size(); j++){
			if(numLine[i] > numLine[j]){
				inversions++;
			}
		}
	}

	//determining if the puzzle is solvable
	if(getLength() % 2 != 0){ //odd number of columns
		if(inversions % 2 == 0){
			return true;
		}
		else{
			return false;
		}
	}
	else{ //even number of columns
		if(getHeight() % 2 == 0){ //even number of rows
			if((inversions + getBlankHeight()+1) % 2 == 0){
				return true;
			}
			else{
				return false;
			}
		}
		else { //odd number of rows
			if((inversions + getBlankHeight()+1) % 2 != 0){
				return true;
			}
			else{
				return false;
			}
		}
	}
}

bool Board::isSolved(){
	if(board == solvedBoard){
		return true;
	}
	else{
		return false;
	}
}

void Board::swap(int& l, int& r){
	int temp = l;
	l = r;
	r = temp;
}

string Board::toString(){
	int h = getHeight();
	int l = getLength();
	int numDashes = (l * 2) + (l + 1);
	string str = "";

	//top line
	for(int i = 0; i < numDashes; i++){
		str += "-";
	}
	str += "\n";

	//print each line of numbers
	for(int i = 0; i < h; i++){
		for(int j = 0; j < l; j++){
			str += '|';
			if(board[i][j] >= 1 && board[i][j] <= 9){
				str += to_string(board[i][j]);
				str += " ";
			}
			else if(board[i][j] >= 10){
				str += to_string(board[i][j]);
			}
			else if(board[i][j] == 0){
				str += "  ";
			}
		}
		str += "|\n";

		if(i != h-1){
			for(int i = 0; i < (getLength()*3) + 1; i++){
				if(i % 3 != 0){
					str += "-";
				}
				else{
					str += "|";
				}
			}
			str+= "\n";
		}
	}

	//bottom line
	for(int i = 0; i < numDashes; i++){
		str += "-";
	}
	str += "\n";

	return str;
}
