/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
 /* Intro Paragraph
 Team members - yab2, rkadiri2, heshama2
 The first function looks for the presence of neighbours in the 8 cells around it.
 It also counts presence of neighbours when a cell is located in an edge or corner
 and does not have 8 adjacent cells.
 The second function applies conditions to the neighbours counted. Lastly, we determine
 if any changes have to be made and execute. */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

  int a=0;													// define variables
	int n1 ,n2, n,i;
	n = (row*boardColSize+col)-1;									// cell before cell we test
  n1 = ((row*boardColSize+col)-boardColSize)-1;					// cell at top right of cell we test
  n2 = ((row*boardColSize+col)+boardColSize)-1;					// cell at bottom right of cell we test

	if(row*col!=0 && row<(boardRowSize-1) && col<(boardColSize-1)){		//case where cell will have 8 neighbours

    for(i=0;i<3;i++){
      a+=board[n1+i];
      a+=board[n2+i];
      a+=board[n+i];
        }

      }
      else if (row==0&& col==0){										//When cell at top right corner
        for(i=1;i<3;i++){
          a+=board[n2+i];
          a+=board[n+i];
}
}
  else if (row==0 && col==(boardColSize-1)){					//When cell is at top left corner
    for(i=0;i<2;i++){
      a+=board[n2+i];
      a+=board[n+i];
}
}
  else if (row==(boardRowSize-1) && col==0){			//cell @ bottom left corner
    for(i=1;i<3;i++){
      a+=board[n1+i];
      a+=board[n+i];
}
}
  else if (row==(boardRowSize-1) && col==(boardColSize-1)){		//cell @ bottom right corner
    for(i=0;i<2;i++){
      a+=board[n1+i];
      a+=board[n+i];
}
}
  else if (row==0 && col!=0 && col!=(boardColSize-1)){		//Cell at upper edge/row but not a corner
    for(i=0;i<3;i++){
      a+=board[n2+i];
      a+=board[n+i];
}
}

  else if (row==(boardRowSize-1)&& col!=0 && col!=(boardColSize-1)){		//Cell at bottom edge/row but not a corner
    for(i=0;i<3;i++){
      a+=board[n1+i];
      a+=board[n+i];
}
}
  else if (col==(boardColSize-1) && row!=(boardRowSize-1)&& row!=0){   	//Cell @ right edge but not a corner
    for(i=0;i<2;i++){
      a+=board[n1+i];
      a+=board[n2+i];
      a+=board[n+i];
}
}

  else if (col==0 && row!=(boardRowSize-1) && row!=0){					//Cell @ left edge but not corner
    for(i=1;i<3;i++){
      a+=board[n1+i];
      a+=board[n2+i];
      a+=board[n+i];
}
}
a = a - board[n+1];									// subtract cell value
return a;

      }


/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int a,b,c,x,y,z;
  z=0;

  x=boardRowSize*boardColSize;
  int board1[x];
  for (c=0;c<x;c++){							//copy array to test array
    board1[c]=board[c];
  }
  for(a=0;a<boardRowSize;a++){
    for(b=0;b<boardColSize;b++){      //call countLiveNeighbor function
      y=countLiveNeighbor(&board[0], boardRowSize, boardColSize,a,b);
      if(y==3 && board[z]==0){
        board1[z]=1;

        z++;

    }
    else if(board[z]==1 && (y<2 || y>3)){
        board1[z]=0;

        z++;

      }
    else
      z++;
	}
	}

 	 for (c=0;c<x;c++){										//copy the test array to the original one to return it
  	  board[c]=board1[c];
	}

  return;

	}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){

  int p, q;

  p=boardRowSize*boardColSize;
  int board1[p];
  for (q=0;q<p;q++){				//copy array to test array
    board1[q]=board[q];
}
updateBoard(board1, boardRowSize, boardColSize);
for (q=0;q<p;q++){                    //Check for changes
  if(board1[q]!=board[q])							//If change exists, return 0
    return 0;
}
return 1;			}							//if no change, return 1
				
				
			

