#include <stdio.h>
#include <stdbool.h>

void initializeBoard(char board[26][26], int n)
{
	int i,j,k,m;
	char alpha[25] = "abcdefghijklmnopqrstuvwxyz";
	printf(" ");
	for(i=0; i<=n;)
	{
		if(i>0)
			board[i][0]=alpha[i-1];
		
		for (j=1; j<=n;)
		{
			if (i==0)
				board[i][j]=alpha[j-1];
				else if(i== n/2 && j== n/2)
					board[i][j] ='W';
				else if (i== n/2 && j== (n/2)+1)
					board[i][j] ='B';
				else if (i== (n/2)+1 && j== (n/2))
					board[i][j] ='B';
				else if (i== (n/2)+1 && j== (n/2)+1)
					board[i][j] ='W';
					else if (board[i][j]!='W' && board[i][j]!= 'B')
						board[i][j] ='U';
		j++;		
		}
		i++;
	}
		
		for (k=0; k<=n;)
	{
		for(m=0; m<=n;)
		{
			if (m==0 && k!=0)
			{
				printf("%c ", board[k][m]);
			m++;
			}
			else
			{
			printf("%c", board[k][m]);
			m++;

			}
			
		}
		printf("\n");
		k++;
	}	
		
	
}
void printBoard(char board[26][26], int n)
{
	int i,j,k,m;
	char alpha[25] = "abcdefghijklmnopqrstuvwxyz";
	printf(" ");
	
		
		for (k=0; k<=n;)
	{
		for(m=0; m<=n;)
		{
			if (m==0 && k!=0)
			{
				printf("%c ", board[k][m]);
			m++;
			}
			else
			{
			printf("%c", board[k][m]);
			m++;

			}
			
		}
		printf("\n");
		k++;
	}	
		
	
}

void printMovesForW(char board[26][26], int n, char colour, char opposite)
{
	int i,j;
	int k,m,p,q,r,s,t,u;
	
	
	for(i=1;i<=n;i++)
	{
		
		for(j=1;j<=n;j++)
		{
		k=1;
		m=1;
		p=1;
		q=1;
		r=1;
		s=1;
		t=1;
		u=1;
		
			if (board[i][j]=='U')
			{
					//move on left
					while (board[i][j+p]==opposite  && (j+p)<n)
					{
						p++;
						if (board[i][j+p]==colour)
						printf("%c%c\n", i-1+97, j-1+97);
					}
						//move on right 
						while (board[i][j-q]==opposite  && (j-q)>0)
					{
						q++;
						if (board[i][j-q]==colour)
						printf("%c%c\n", i-1+97, j-1+97);
					}
					
					//move of top left 
					while (board[i+r][j+r]==opposite  && (j+r)<n  && (i+r)<n)
					{
						r++;
						if (board[i+r][j+r]==colour)
						printf("%c%c\n", i-1+97, j-1+97);
					}
					
					//top
						while (board[i+k][j]==opposite  && (i+k)<n)
					{
						k++;
						if (board[i+k][j]==colour)
						printf("%c%c\n", i-1+97, j-1+97);
					}
					
					//top right 
					while (board[i+s][j-s]==opposite  && (j-s)>0  && (i+s)<n)
					{
						s++;
						if (board[i+s][j-s]==colour)
						printf("%c%c\n", i-1+97, j-1+97);
					}
					
					//bottom left 
					while (board[i-t][j+t]==opposite  && (j+t)<n  && (i-t)>0)
					{
						t++;
						if (board[i-t][j+t]==colour)
						printf("%c%c\n", i-1+97, j-1+97);
					}
					
					//bottom 	
						while (board[i-m][j]==opposite  && (i-m)>0)
					{
						m++;
						if (board[i-m][j]==colour)
						printf("%c%c\n", i-1+97,j-1+97);
					}
					
					//bottom right 
						while (board[i-u][j-u]==opposite  && (j-u)>0  && (i-u)>0)
					{
						u++;
						if (board[i-u][j-u]==colour)
						printf("%c%c\n", i-1+97, j-1+97);
					}
				
				

			}
				
				
			}
			
		}
	}
	
bool positionInBounds(int n, int row, int col)
{
	
    if(row<=n && col<=n && row>=0 && col>=0)
		return true;
		
		else 
			return false;
		
}


bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{  
		
	int newRow=row +deltaRow;
	int newCol=col +deltaCol;
	bool legal=false;
	
	if (board[newRow][newCol]!=colour && board[newRow][newCol]!='U' && positionInBounds(n, newRow, newCol))
	{
do
	{
		newRow= newRow + deltaRow;
		newCol = newCol +deltaCol;
		
	}	while (board[newRow][newCol]!= colour && board[newRow][newCol]!= 'U' && positionInBounds(n,newRow, newCol));
	
	
	
	if (board[newRow][newCol]==colour && positionInBounds(n, newRow, newCol))
				legal =true;
				
				else legal = false; 
				

	}
	return legal;
}

bool LegalMove(char board[26][26], int n, int row, int col, char colour)
{
	int direction= 1;
	bool validMove;
	
	if(board[row][col]=='U')
	{
		for (int deltaRow=-1; deltaRow<=1; deltaRow++)
		{
			for(int deltaCol=-1; deltaCol<=1; deltaCol++)
			{
				if (deltaRow==0 && deltaCol==0);
				 if (checkLegalInDirection(board, n,row,col,colour,deltaRow, deltaCol))
						direction++;
			}
		}
	}
	
	if (direction >1)
		validMove=true;
		
		else 
			validMove=false;
			
			return validMove;
		
		
}
	

void flipPieces(char board[26][26], int n, int i, int j, char colour)
{



		for (int deltaRow=-1; deltaRow<=1; deltaRow++)
		{
			for(int deltaCol=-1; deltaCol<=1; deltaCol++)
			{
				if (deltaRow==0 && deltaCol==0);
				else 
				{
					if (checkLegalInDirection(board, n, i, j, colour, deltaRow, deltaCol)==true)
					{
						i=i+deltaRow;
						j=j+deltaCol;
					
		do
					{
				
						board[i][j]=colour;
						i = i + (deltaRow);
						j = j +(deltaCol);
						
					} 	while( board[i][j]!=colour && board[i][j]!='U');
					
				
					
					}
					}
				}
			}
			printBoard(board, n);
			
		
		
	}
	
	int main(void)
{	
		bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
		bool LegalMove(char board[26][26], int n, int row, int col, char colour);
		bool positionInBounds(int n, int row, int col);
		
		
	int dimension=0; 
	char board[26][26];
	char colour='a';
	int rowIndex, columnIndex;
	char row, col;
	
	char moveColour, moveRow, moveColumn;
	//bool legal=false;
	//bool makemove=false;
	printf("Enter the board dimension: ");
	scanf("%d", &dimension);
	initializeBoard(board, dimension);
	
	printf("Enter the board configuration:\n");
	while (colour != '!')
	{
	scanf("%c", &colour);
	scanf("%c", &colour);
	
	scanf("%c", &row);
	scanf("%c", &col);

		rowIndex= row-97;
		columnIndex= col-97;
		
		if (colour=='B')
			board[rowIndex+1][columnIndex+1]='B';
		else if(colour=='W')
			board[rowIndex+1][columnIndex+1]='W';
	}
	
		printBoard(board, dimension);
		
			printf("Available moves for W:\n");
		
		printMovesForW(board, dimension, 'W','B');
		
			printf("Available moves for B:\n");
		printMovesForW(board, dimension, 'B','W');
		
		printf("Enter a move:");
	scanf("%c",&moveColour );
	scanf("%c",&moveColour );
	scanf("%c",&moveRow);
	scanf("%c",&moveColumn);
	
	moveRow= moveRow-96;
	moveColumn = moveColumn-96;

	if (LegalMove(board, dimension, moveRow, moveColumn, moveColour)==true)
		{
			printf("Valid move\n");
		board[moveRow][moveColumn]= moveColour;
			flipPieces(board, dimension, moveRow, moveColumn, moveColour);
				
		}
		
		else 
			{
				printf("Invalid Move\n");
			
			}
			
	
	return 0;

}


	
