/*-------------------------
* Program: 1024 using Linked Lists
*
* Author: Abraheem Irheem 
*
* System: Linux, GCC
*
-------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <iostream>

using namespace std;

//ANSI escape codes to display output in colour
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

// Node saves board state at each turn
struct Node{
    int score;
	int moveNumber;
	int *board;
	Node* pNext;
};


//----------------------------------------------------------------------
// *** Directions ***
void identifyingInfo(){

  cout << RESET << endl;
  printf( GREEN"Abraheem Irheem\nUIC CS 141, Spring 2014\n\n" RESET);
  printf("Welcome to 1024 and More.\n");
  printf("This program is based off of Gabriele Cirulli's game online at\n");
  printf("    bit.ly/great2048\n");
  printf("For each move enter a direction as a letter key, as follows:\n");
  printf(RED"    W\n  A S D\n"RESET);
  printf("where A=left,W=up, D=right and S=down.\n");
  printf("After a move, when two identical valued tiles come together they\n");
  printf("join to become a new single tile with the value of the sum of the\n");
  printf("two originals. This value gets added to the score.  On each move\n");
  printf("one new randomly chosen value of 2or4 is placed in a random open\n");
  printf("square. "); 
  printf("User input of "RED "R" RESET " restarts the board\n"); 
  printf("Input " RED "U" RESET " undoes the last move\n");
  printf("And input of " RED "X" RESET " exits the game,\n");
  cout << endl;
}


//----------------------------------------------------------------------
//Prompts for user input for board size
void getBoardSize( int &size, int &totalSize, int &targetScore){

    do{
        printf("Enter board size between 4 and 12: ");
        cin >> size;

        if(size>12 || size<4)
            printf("You must enter a valid board size\n");
        else
            break;
    } while( 1);

    totalSize = size*size;

    if(size == 4)
      targetScore = 1024;
    else if(size == 5)
      targetScore = 2048;
    else if(size == 6)
      targetScore = 4096;
    else if(size == 7)
      targetScore = 8192;
    else if(size == 8)
      targetScore = 16384;
    else if(size == 9)
      targetScore = 32768;
    else if(size == 10)
      targetScore = 65536;
    else if(size == 11)
      targetScore = 131072;
    else if(size == 12)
      targetScore = 262144;

    cout << "Game ends when you reach " << targetScore << endl;
}


//----------------------------------------------------------------------
//Initialize board
void InitializeBoard( int board[], int totalSize){
  int i, r1, r2, g1, g2, random[] = { 2, 4};
  	//Initializes array to 0
  	for(i=0; i<totalSize; i++){
  		board[i] = 0;  	
  	}
  	//Inserts two random numbers of either 2 or 4 into array
  	r1 = rand()%totalSize;
  	g1 = rand()%2;
  	g2 = rand()%2;
  	board[r1] = random[g1];

  	do{
  		r2 = rand()%totalSize;
  	} while(r2 == r1);
    
	board[r2] = random[g2];
}


//----------------------------------------------------------------------
//Prints Board in colour
void printBoard( int board[], int totalSize, int size, int k, int score){
  int i;

	printf("\n\nScore: %d", score);
  	//Prints array in rows and columns
  	for(i=0; i<totalSize; i++){
  		if(i%size == 0)
  			printf("\n\n\n");

		// Displays each number with a unique color
  		if(board[i] == 2)
	  		printf(RED "%7d" RESET, board[i]);
  		else if(board[i] == 4) 
  			printf(GREEN "%7d" RESET, board[i]);
  		else if(board[i] == 8)
  			printf(MAGENTA "%7d" RESET, board[i]);
  		else if(board[i] == 16)
  			printf(BOLDBLUE "%7d" RESET, board[i]);
  		else if(board[i] == 32)
  			printf(BOLDGREEN "%7d" RESET, board[i]);
  		else if(board[i] == 64)
  			printf(BOLDRED "%7d" RESET, board[i]);
  		else if(board[i] == 128)
  			printf(YELLOW "%7d" RESET, board[i]);
  		else if(board[i] == 256)
  			printf(BOLDMAGENTA "%7d" RESET, board[i]);
  		else if(board[i] == 512)
  			printf(BOLDYELLOW "%7d" RESET, board[i]);
  		else if(board[i] == 1024)
  			printf(YELLOW "%7d" RESET, board[i]);
        else if(board[i] == 2048)
            printf(YELLOW "%7d" RESET, board[i]);
  		else 
  			printf("%7d", board[i]);
  	}
  	printf("\n%d. Your move: ", k);
  	//printf("\n\n");

}


//----------------------------------------------------------------------
//Gets user input and make a move
void getInput( char &userInput, int board[], int size, int totalSize){
  int boardIndex, value;

    do{
        scanf(" %c", &userInput);
        userInput = toupper(userInput);
        if(userInput != 'W' && userInput != 'S' && userInput != 'A' && 
           userInput != 'D' && userInput != 'R' && userInput != 'U' &&
           userInput != 'P' && userInput != 'X' ){
            printf("  ---Invalid input---\n");
			printf("Your move: ");
		}
        else
            break;

    } while(1);
    //Exits program if user inputs 'X'
  	if(userInput == 'X'){
  		printf("\n\nExiting ...\n");
  		exit(0);
  	}
    //This is to place a number in a particular spot in the board
    if(userInput == 'P'){
        scanf(" %d %d", &boardIndex, &value);
        board[boardIndex] = value;
    }
}


//----------------------------------------------------------------------
//Random number generator
void randGenerator( int board[], int totalSize){
  int random[] = { 2, 4}, r, count=0;

    //This generates a random number (2 or 4) and places it in an empty spot
  	do{
  		r = rand()%totalSize;
  		if( board[r] != 0)
  			continue;
  		board[r] = random[rand()%2];
  		break;
  	}while( 1); 
}


//----------------------------------------------------------------------
//Called by makeMove() to move values to the RIGHT
void moveRight( int board[], int i, int endRow, int &score, int &check1){
    //Checks if next position from the right is empty then moves number RIGHT
    while( (board[i+1] == 0) && (i<endRow) ){
        board[i+1] = board[i];
        board[i] = 0;
        i++;
        check1 = 1;
    }
}


//----------------------------------------------------------------------
//Called by makeMove() to move values DOWN
void moveDown( int board[], int i, int endCol, 
               int size, int &score, int &check2){
    //Checks if next position from below is empty then moves number DOWN
    while( (i<endCol) && (board[i+size] == 0) ){
        board[i+size] = board[i];
        board[i] = 0;
        i += size;
        check2 = 1;
    }
}


//----------------------------------------------------------------------
//Called by makeMove() to move values to the LEFT
void moveLeft( int board[], int i, int beginRow, int &score, int &check3){
    //Checks if next position from the left is empty then moves number left
    while( (board[i-1] == 0) && (i>beginRow) ){
        board[i-1] = board[i];
        board[i] = 0;
        i--;
        check3 = 1;
    }
}


//----------------------------------------------------------------------
//Called by makeMove() to move values UP
void moveUp( int board[], int i, int beginCol, 
             int size, int &score, int &check4){
    //Checks if next position from above is empty then moves number UP
    while( (i>beginCol) && (board[i-size] == 0) ){
        board[i-size] = board[i];
        board[i] = 0;
        i -= size;
        check4 = 1;
    }
}


//----------------------------------------------------------------------
//Calls the functions above to make moves
//The loops inside iterate through the array row by row or column by column
//depending on the user input direction 
void makeMove(int* board, int totalSize, int size, 
              char userInput, int &score, int &moveFAIL){
  
  int row, col, current, beginRow, endRow, beginCol, endCol;
  //These fariables are used to check if there has been a move made
  int check1=0, check2=0, check3=0, check4=0;
  
    moveFAIL = 0;
    //Moves everything RIGHT if input is 'D'
    if(userInput == 'D'){
        for(row=(size-1); row>=0; row--){  
            for(col=(size-2); col>=0; col--){
                current = row*size + col; //Current index of each piece    
                endRow = row*size + (size-1); //End of row index

                if(board[current] != 0){  
                    moveRight( board, current, endRow, score, check1); 
                }
            }
        }
    }
    //Moves everything DOWN if input is 'S'
    if(userInput == 'S'){
        for(col=0; col<size; col++){
            for(row=(size-2); row>=0; row--){
                current = row*size + col; //Current index of each piece
                endCol = (size-1)*size + col; //End of column index

                if(board[current] != 0){
                    moveDown( board, current, endCol, size, score, check2);
                }
            }
        }
    }
    //Moves everything LEFT if input is 'A'
    if(userInput == 'A'){
        for(row=0; row<size; row++){
            for(col=1; col<size; col++){
                current = row*size + col; //Current index of each piece
                beginRow = row*size; //Beginning of row index

                if(board[current] != 0){
                    moveLeft( board, current, beginRow, score, check3);
                }
            }
        }
    }
    //Moves everything UP if input is 'W'
    if(userInput == 'W'){
        for(col=0; col<size; col++){
            for(row=1; row<size; row++){
                current = row*size + col; //Current index of each piece
                beginCol = col;      //Beginning of column index

                if(board[current] != 0){
                    moveUp( board, current, beginCol, size, score, check4);
                }
            }
        }
    }  
    //If no move has been made, then FAIL is true
    if(check1 == 0 && check2 == 0 && check3 == 0 && check4 == 0)
        moveFAIL = 1;
}


//----------------------------------------------------------------------
//Merge
void merge( int board[], int totalSize, int size, 
            char userInput, int &score, int &mergeFAIL){
  int i, check=0;
    //In these loops, merged values are assigned to [i] not [i-+1] or [i-+size]
    //to prevent merging the values a second time

    //Merges values going (RIGHT)
    if(userInput == 'D'){
        for(i=(totalSize-1); i>=0; i--){
            if(i == 0) //If [i] is 0, there will be no more values to check
                break;
            if(i%size == 0) //To jump to next row
                i--;
            if( (board[i] == board[i-1]) && (board[i] != 0) ){
                board[i] = board[i] + board[i-1];
                board[i-1] = 0;
                score += board[i];
                check = 1; //Means there has been a merge
            }
        }
    }
    //Merges values going (LEFT)
    else if(userInput == 'A'){
        for(i=0; i<totalSize; i++){
            if(i == (totalSize-1)) //Breaks at last index of board
                break;
            if((i+1)%size == 0) //To jump to next row
                i++;
            if( (board[i] == board[i+1]) && (board[i] != 0) ){
                board[i] = board[i] + board[i+1];
                board[i+1] = 0;
                score += board[i];
                check = 1; //Means there has been a merge
            }        
        }
    }
    //Merges values going (UP)
    else if(userInput == 'W'){
        for(i=0; i<totalSize; i++){
            if(i == ((size-1)*size)) //Breaks at last index of first column
                break;
            if( (board[i] == board[i+size]) && (board[i] != 0) ){
                board[i] = board[i] + board[i+size];
                board[i+size] = 0;
                score += board[i];
                check = 1; //Means there has been a merge
            }
        }        
    }
    //Merges values going (DOWN)
    else if(userInput == 'S'){
        for(i=(totalSize-1); i>=0; i--){
            if(i == (size-1)) //Breaks at last index of first row
                break;
            if( (board[i] == board[i-size]) && (board[i] != 0) ){
                board[i] = board[i] + board[i-size];
                board[i-size] = 0;
                score += board[i];
                check = 1; //Means there has been a merge
            }
        }
    }
    //If no merge has been made, then mergeFAIL is true
    if(check == 0)
        mergeFAIL = 1;
}


//----------------------------------------------------------------------
//Checks if user reached winning score
void checkWin( int board[], int totalSize, int targetScore){
  int i;

	for (i=0; i<totalSize; i++){
		if(board[i] == targetScore){
			printf("\n   ***** You Won d(^_^)b *****\n");
			printf("Exiting ...\n");
			exit(1);
		}
	}	
}


//----------------------------------------------------------------------
//Checks if user has no more moves to make
void checkLose( int board[], int size, int totalSize, int targetScore){
  int i, emptySpot=0, PASS=1, win=0;
    //Check if the board is full
    for(i=0; i<totalSize; i++){
        if(board[i] == 0){
            emptySpot = 1;
            break;
        }
    }
    for(i=0; i<totalSize; i++){
        if(board[i] == targetScore){
            win = 1; //Exits the function to proceed to checkWin
            break;       
        }
    }
    //If the board is full, this checks if two values can still be merged
    if(emptySpot == 0 && win == 0){ 
        PASS = 0;
        for(i=(totalSize-1); i>=0; i--){
            if(i == 0) //To prevent checking past the start of the array
                break;
            if(i%size == 0) //To proceed to the next row
                i--;
            if(board[i] == board[i-1]){
                PASS = 1;//Means still two horizontal numbers to be added 
                break;
            }
        }
        for(i=0; i<totalSize; i++){
            if(i == ((size-1)*size)) //Stops at last index of first column
                break;
            if(board[i] == board[i+size]){
                PASS = 1;//Means still two vertical numbers to be added 
                break;
            }
        }
    }
    if(PASS == 0){
        printf("\n --- Game Over Loser (>_<) ---\n");
        printf("Exiting ...\n");
        exit(1);
    }    
}


//----------------------------------------------------------------------
//Stores the board's state before every move by copying all values
//(board, score, and moveNumber) into the new Node pTemp, then connects
//pTemp to the head of the list, then connects pHead to the new head
//of the list.
void storeNode(Node* &pHead, int board[], int &score, int &moveNumber, 
                int size, int totalSize){
  int i;
  Node *pTemp;

    pTemp = new Node;
	pTemp->board = new int[totalSize];

    for(i=0; i<totalSize; i++){
        pTemp->board[i] = board[i];
    }
    pTemp->score = score;
    pTemp->moveNumber = moveNumber;

	pTemp->pNext = pHead;
	pHead = pTemp;
}


//----------------------------------------------------------------------
//Deletes last Node added to list by first copying all values stored in pHead 
//back into the main values (board, score, moveNumber). Then pHead is assigned 
//to pTemp so that we don't lose pHead. Since pHead holds the node we want to 
//delete, we want pHead to point to the next node (pHead->pNext) and delete 
//pTemp which holds the actual pHead node.
void deleteNode( Node* &pHead, int board[], int &score, int &moveNumber, 
                int totalSize){
    int i;
    Node *pTemp;
    //Assigns the board state in the last node to the actual board
    for(i=0; i<totalSize; i++){
        board[i] = pHead->board[i];
    }
    score = pHead->score;
    moveNumber = pHead->moveNumber;
    //Deletes the last node from the list
    pTemp = pHead;
    pHead = pHead->pNext;

    delete[] pTemp->board; 
    delete(pTemp);
}


//----------------------------------------------------------------------
//Deletes all nodes and resets board
void deleteAllNodes( Node* &pHead){
  Node *pTemp;

    while(pHead != NULL){
        pTemp = pHead;
        pHead = pHead->pNext;
        delete(pTemp);
    }
}


//----------------------------------------------------------------------
//Prints last node added
//This function is used for debugging
void printLinkedList( Node* pHead, int board[], int totalSize, int size){
  char line[] = "-------------------------"; //Line separator
  int i=0;
    Node *pTemp = new Node;
    pTemp = pHead;

    //This code prints the whole Linked List
	while( pTemp != NULL){
        for(i=0; i<totalSize; i++){
            if(i%size == 0)
                printf("\n\n");
            printf("%7d", pTemp->board[i]);
        }
        printf("\n\n    %s", line);
        pTemp = pTemp->pNext;
	} 
    printf("\n\n");
}

//===========================================================================
int main(void){  

  int size, totalSize, *board, k=1, score=0, targetScore, moveFAIL, mergeFAIL;
  char userInput;
  Node *pHead = NULL;

  	srand( (unsigned) time(NULL)); //To change random numbers with time

  	system("clear"); //Clears screen
  	identifyingInfo(); //Prints name and instructions

	//Prompts user for size
    getBoardSize( size, totalSize, targetScore);
 	//Allocates memory for board 
    board = new int[totalSize];
	//Initialize board to zeros and two random numbers
  	InitializeBoard( board, totalSize);
  //These are used to store the previous board state so the user can undo 
  int tempBoard[totalSize], tempScore;

  	do{ //MAIN LOOP
            moveFAIL = 0; //Used to check if any moves have been made
            mergeFAIL = 0;//Used to check if any merges have been made
		//printLinkedList( pHead, board, totalSize, size);

		    //Prints board, move number, and score
  		    printBoard( board, totalSize, size, k, score);
            //Checks if user gets the winning number
            checkWin( board, totalSize, targetScore);     
            //Checks if no more moves can be made
            checkLose( board, size, totalSize, targetScore);
		    //Prompts for user input for direction
  		    getInput( userInput, board, size, totalSize);

            if(userInput == 'P'){ 
                system("clear"); //Clears screen
                cout << "  --- A particular value has been placed ---" << endl;
                continue;
            }
            if(userInput == 'U'){ //Undoes last move
                if(pHead == NULL){
                    system("clear"); //Clears screen
                    cout << " --- Already in the beginning ---" << endl;
                    continue;
                }        
                deleteNode( pHead, board, score, k, totalSize);
                system("clear"); //Clears screen
                cout << "  --- Board is back one step ---" << endl;
                        continue;
            }
  		    if(userInput == 'R'){ //Resets board
                deleteAllNodes( pHead);
  			    InitializeBoard( board, totalSize);//Re-initializes board
  			    k=1; //Resets moves back to 1
                score = 0;
                system("clear"); //Clears screen
  			    cout << "  ---Board has been reset---" << endl;
  			    continue; 
            }
			//Stores the board's state into a Node
            storeNode( pHead, board, score, k, size, totalSize);  
            makeMove( board, totalSize, size, userInput, score, moveFAIL);
            merge( board, totalSize, size, userInput, score, mergeFAIL);
			//Prints error if user fails to move or merge any values
            if( moveFAIL == 1 && mergeFAIL == 1){ 
                system("clear"); //Clears screen
                cout << " --- You are not moving any values ---" << endl;
                deleteNode( pHead, board, score, k, totalSize);
                continue;
            }
            //Attempt to move again after any merge
            makeMove( board, totalSize, size, userInput, score, moveFAIL);
  		    randGenerator( board, totalSize);//Generates a random number
	  	    k++; //Move count
  		    system("clear"); //Clears screen
  	}while(1);

    delete(board);

	return 0;
} // THE END

