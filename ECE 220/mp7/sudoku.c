#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

/* 
Team members - yab2, rkadiri2, heshama2
we use 5 functions to solve sudoku
the first scans rows, the second scans columns, 3rd scans 3x3 area,
the fourth  checks if a cell can be filled with a certain number and the 5th 
function uses backtracking to call the fourth function on every cell 
to find the complete solution.
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
//uses for loop to check row
  assert(i>=0 && i<9);

  // BEG TODO

  int j;
for (j = 0; j < 9; j++) {
  if (sudoku[i][j]==val) {
    return true;
  }
}

  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
//uses for loop to check column
  assert(j>=0 && j<9);

  // BEG TODO

  int i;
  for (i = 0; i < 9; i++) {
    if (sudoku[i][j]==val) {
      return true;
    }
  }

  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
//This function has for loops that check the 3x3 regions
  assert(i>=0 && i<9);

  // BEG TODO
  int x, y;
if (i<3 && j<3) {
  for(x=0;x<3;x++){
    for (y=0; y<3; y++) {
      if (sudoku[x][y]==val) {
        return true;
      }

    }

  }
}
else if ((i>=3&&i<6) && j<3) {
  for(x=3;x<6;x++){
    for (y=0;y<3;y++) {
      if (sudoku[x][y]==val) {
        return true;
      }
    }
  }

}
else if (i<3 && j>5) {
  for(x=0;x<3;x++){
    for (y=6;y < 9; y++) {
      if (sudoku[x][y]==val) {
        return true;
      }
    }
  }

}
else if (i<3 && (j>=3&&j<6)) {
  for (x = 0; x < 3; x++) {
    for (y=3; y < 6; y++) {
      if (sudoku[x][y]==val) {
        return true;
      }
    }
  }

}
else if ((i>=3&&i<6) && j>5) {
  for(x=3;x<6;x++){
    for (y=6;y < 9;y++) {
      if (sudoku[x][y]==val) {
        return true;
      }
    }

  }

}
else if (i>5 && (j>=3&&j<6)) {
  for(x=6;x<9;x++){
    for (y=3; y < 6; y++) {
      if (sudoku[x][y]==val) {
        return true;
      }
    }
  }

}
else if (i>5 && j>5) {
  for(x=6;x<9;x++){
    for (y=6;y < 9;y++) {
      if (sudoku[x][y]==val) {
        return true;
      }
    }
  }

}

else if ((i>=3&&i<6) && (j>=3&&j<6)) {
  for(x=3;x<6;x++){
    for (y=3;y< 6;y++) {
      if (sudoku[x][y]==val) {
        return true;
      }
    }
  }

}
else if (i>5 && j<3) {
  for(x=6;x<9;x++){
    for (y=0;y < 3; y++) {
      if (sudoku[x][y]==val) {
        return true;
      }
    }
  }

}

  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
// checks rows columns and 3x3 areas and returns 1 if value of cell is valid
  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if (is_val_in_row(val,i,sudoku))
  return 0;
else if (is_val_in_col(val,j,sudoku))
  return 0;
else if (is_val_in_3x3_zone(val,i,j,sudoku))
  return 0;
else
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
//use of backtracking to find the solutions
  // BEG TODO.
  int x, y, num;
  for (x = 0; x<9; x++){
    for(y=0;y<9;y++){
     if (sudoku[x][y]==0)
        break;
    }
    if (sudoku[x][y]==0 && y<9)
      break;
  }
  if (x==9)						//return true if all cells are checked
    return true;
  for(num=1; num<10; num++){
    if(is_val_valid(num , x , y, sudoku)){
      sudoku[x][y]=num;
      if (solve_sudoku(sudoku))
        return true;									// return true when solution is found
      sudoku[x][y]=0;
    }
  }

  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
