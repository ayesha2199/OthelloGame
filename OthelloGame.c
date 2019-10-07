#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//function checks if move is in bounds using board dimensions
bool positionInBounds(int n, int row, int col)
{
    if(row<n && col<n && row>=0 && col>=0)
return true;
else 
return false;
}
//checks if enetered move is valid by checking pieces around it 
bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{  
int newRow=row +deltaRow;
int newCol=col +deltaCol;
bool legal=false;
if (board[newRow][newCol]!=colour && board[newRow][newCol]!='U' && positionInBounds(n, newRow, newCol))
{ 
do
{ //check each element in a row to determine if direction is legal 
newRow= newRow + deltaRow;
newCol = newCol +deltaCol;
} while (board[newRow][newCol]!= colour && board[newRow][newCol]!= 'U' && positionInBounds(n,newRow, newCol));
if (board[newRow][newCol]==colour && positionInBounds(n, newRow, newCol))
legal =true;
else legal = false; 
}
return legal;
}

//determines if move is legal using legalInDirection function
bool LegalMove(char board[26][26], int n, int row, int col, char colour)
{
    int deltaRow, deltaCol;
int direction= 1;
bool validMove;
if(board[row][col]=='U')
{
for (deltaRow=-1; deltaRow<=1; deltaRow++)
{
for(deltaCol=-1; deltaCol<=1; deltaCol++)
{
if (deltaRow==0 && deltaCol==0);
else if (checkLegalInDirection(board, n,row,col,colour,deltaRow, deltaCol))
direction++;
}
}
}
//If atleast one direction is returned truw, the move is legal 
if (direction >1)
validMove=true;
else 
validMove=false;
return validMove;
}

//function used to flip pieces in between after a valid move is made 
void flipPieces(char board[26][26], int n, int row, int col, char colour)
{
int deltaRow, deltaCol;
for (deltaRow=-1; deltaRow<=1; deltaRow++)
{
for(deltaCol=-1; deltaCol<=1; deltaCol++)
{
int i=row;
int j=col;
if (deltaRow==0 && deltaCol==0);
else 
{
if (checkLegalInDirection(board, n, i, j, colour, deltaRow, deltaCol)==true)
{
i=i+deltaRow;
j=j+deltaCol;
do
{ // changes colour of tiles in between two opposite colours
board[i][j]=colour;
i = i + (deltaRow);
j = j +(deltaCol);
} while( board[i][j]!=colour && board[i][j]!='U');
}
}
}
}
//prints final board after pieces have been flipped to opposite colour
printBoard(board, n);
}

//finds the score of each move by keeping track of pieces flipped
int scoreOfMove(char board[26][26], int n, int row, int col, char colour)
{
int score=0;
int deltaRow, deltaCol;
for (deltaRow=-1; deltaRow<=1; deltaRow++)
{
int i=row;
int j=col;
for(deltaCol=-1; deltaCol<=1; deltaCol++)
{
if (deltaRow==0 && deltaCol==0);
else 
{
if (checkLegalInDirection(board, n, i, j, colour, deltaRow, deltaCol)==true)
{
i=i+deltaRow;
j=j+deltaCol;
do
{  // adds to count as pieces are flipped 
score +=1;
i = i + (deltaRow);
j = j +(deltaCol);
} while( board[i][j]!=colour && board[i][j]!='U');
}
}
}
}
return score; 
}
//prints board at any given moment, after board elements are altered 
void printBoard(char board[26][26], int n)
{
int i,j,k;
printf("  ");
    
    //prints first row of characters
for (k=0; k<n; k++)
{
printf("%c", 97+k);
            
} 
        printf("\n");
        
        //prints characters in first column and board row by row 
        for(j=0;j<n;j++)
        {
            printf("%c ", 97+j);
            for(i=0;i<n;i++)
            {
                printf("%c", board[j][i]);
            }
               printf("\n");
        }
}
// function initializes original board 
void initializeBoard(char board[26][26], int n)
{
int i,j;

//Initializes all elements of board to U
for(i=0; i<n; i++)
{
                for(j=0;j<n;j++)
                {
                board[i][j]='U';
                
                }
            }
            
            
            board[n/2][n/2]='W';
            board[(n/2)-1][(n/2)-1]='W';
              board[(n/2)-1][(n/2)]='B';
                board[(n/2)][(n/2)-1]='B';
                
                //prints characters around board
                printBoard(board,n);
}

//determines the total number of moves each player has
//used to see if a player has any valid moves left 
int numOfMoves(char board[26][26], int n, char colour, char opposite)
{
int i, j, row, col;
int moves=0; 
for(i=0;i<=n;i++)
{
for(j=0;j<=n;j++)
{
if (board[i][j]=='U' && LegalMove(board, n, i, j, colour)==true)
moves+=1;
}
}
return moves;
}

//prints the move for the comupter user using the move that result sin the most flips 
void printMoveForComputer(char board[26][26], int n, char colour, char opposite, int e)
{
int i, j, row, col;
int score=0; 
for(i=0;i<=n;i++)
{
for(j=0;j<=n;j++)
{
if (board[i][j]=='U' && LegalMove(board, n, i,j, colour)==true)
{//sets score to the highest value out of all other scores 
if(score < scoreOfMove(board, n, i, j, colour))
{
score = scoreOfMove(board, n, i, j, colour);

row = i;
col=j;
}
}
}
}
if(LegalMove(board, n, row,col, colour)==true && board[row][col]=='U' && positionInBounds(n, row, col)==true)
{
printf("Computer places %c at %c%c.\n", colour, row+97, col+97);
board[row][col]=colour;

flipPieces(board, n, row, col, colour);
}
else if (e==0);
else 
printf("%c player has no valid move.\n", colour);
}

//detemrines the final number of a colour after the board is full
//used to determine the winner at the end 
int numOfColour(char board[26][26], int dimension, char colour)
{
int m, n;
int num=0;
for (m=0; m<dimension; m++ )
{
for (n=0;n<dimension; n++)
{
if (board[m][n]==colour)
{
num+=1;
}
}
}
return num;
}

//prints the user move using the move entered
//checks if move is valid 
void printUserMove(char board[26][26], int dimension, char colour, char opposite, int *e)
{
    char moveR, moveC;
int moveRow, moveColumn;
printf("Enter move for colour %c (RowCol): ", colour);
scanf("%c",&moveR);
scanf("%c",&moveR);
scanf("%c",&moveC);
moveRow= moveR-97;
moveColumn = moveC-97;

if(LegalMove(board, dimension, moveRow, moveColumn, colour)==true && positionInBounds(dimension, moveRow, moveColumn)==true && board[moveRow][moveColumn]=='U')
{
board[moveRow][moveColumn]=colour;
flipPieces(board, dimension,moveRow, moveColumn,colour);
}
else 
{
printf("Invalid move.\n%c player wins.\n", opposite);
*e = -1;
}
}

int main(void)
{ 
//initializes functions 
bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
bool LegalMove(char board[26][26], int n, int row, int col, char colour);
bool positionInBounds(int n, int row, int col);

int dimension=0; 
char board[26][26];
char colour='a';
int rowIndex, columnIndex;
char row, col, moveColour, moveRow, moveColumn, compColour, opposite;
int empty=0;
int m, n, i, j;

//prompts user to enter dimension and board configuration and assigns corresponding values 
printf("Enter the board dimension: ");
scanf("%d", &dimension);
//Initializes original board 
printf("Computer plays (B/W) : ");
scanf("%c", &compColour);
scanf("%c", &compColour);
 
//Initializes original board 
initializeBoard(board, dimension);

//detemrines the total number of empty spaces the game begins with 
for (m=0; m<dimension; m++ )
{
for (n=0;n<dimension; n++)
{
if (board[m][n]=='U')
{
empty+=1;
}
}
}
//continues game until the board is full OR neither player has a valid move 
while(empty>0 && (numOfMoves(board, dimension, 'W', 'B')>0 || (numOfMoves(board, dimension, 'B', 'W')>0 )))
{
if (compColour == 'B')
{
opposite = 'W';
//while the computer has valid moves 
if (numOfMoves(board, dimension, 'B', 'W')>0)
	//decrease the number of empty spaces as moves are made 
empty-=1;
printMoveForComputer(board, dimension, 'B', 'W', empty);
 
if (numOfMoves(board, dimension, opposite, compColour)>0)
{
empty -=1;
printUserMove(board, dimension, opposite, compColour, &empty);
}
else 
printf("W player has no valid move.\n");
}
 
 //runs when computer is 'W' player 
else 
{
opposite = 'B';
if (numOfMoves(board, dimension, opposite, compColour)>0)
{
empty -=1;
printUserMove(board, dimension, opposite, compColour, &empty);
}
else 
printf("W player has no valid move.\n");
if (numOfMoves(board, dimension, 'W', 'B')>0)
empty-=1;
if (empty>0)
printMoveForComputer(board, dimension, 'W', 'B', empty);
}

//when board is empty, determines which player has more pieces and declares winner 
if (empty ==0 || (numOfMoves(board, dimension, 'W', 'B')<1 && numOfMoves(board, dimension, 'B', 'W')<1) )
{
if (numOfColour(board, dimension, 'W')>numOfColour(board, dimension, 'B') )
printf("W player wins.\n");
else 
printf("B player wins.\n");
}
}
return 0;
}

