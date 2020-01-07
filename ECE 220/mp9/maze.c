/* 
The program solves the  maze using four functions. First function forms a maze using pointers, file I/O & dynamic memory. The maze is destroyed by the second fucntion.The third function prints the maze. The maze is solved Using recurrsion and backtracking by the fourth function.
Partners: rkadiri2, yab2, heshama2
*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)                                     // Creating maze
{
    // Your code here. Make sure to replace following line with your own code.
    maze_t *mymaze = (maze_t *)malloc(sizeof(maze_t));                   // Allocating dynamic memory
    char c;
    FILE *Cmaze;                                                         // Read file in Cmaze
    Cmaze = fopen(fileName,"r");
    int i;                                                               // To scan for height
    int j;                                                               // To scan for width
    fscanf(Cmaze, "%d %d", &(mymaze->width), &(mymaze->height));
    int width = mymaze->width;
    int height = mymaze->height;     
    mymaze->cells =(char **)malloc(sizeof(char *) * height);             // Allocating memory for each cell in the 2D array
                                                                         // no maze_t just size of char *
    for(i=0; i<width; i++){               
      mymaze->cells[i] = (char *)malloc(sizeof(char)*width);
    }
    c=fgetc(Cmaze);
    c=fgetc(Cmaze); 
    c=fgetc(Cmaze);                                                      // Skip 3 characters

    for(i=0; i<height; i++) {
      for(j=0; j<width; j++) {
        c = fgetc(Cmaze);                                                // Read char from file
        if(c == '\n')
          c = fgetc(Cmaze);
        mymaze->cells[i][j] = c;                                         // Assigning characters to cells
        if(c == START) {
          mymaze->startRow = i; 
          mymaze->startColumn = j;
        }
        if(c == END) {
          mymaze->endRow = i;                                            // Get S & E
          mymaze->endColumn = j;
        }
      }
    }

    return mymaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i=0; i<maze->height; i++){
      free(maze->cells[i]);    
    }
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int width = maze->width;       
    int height = maze->height;
    int i;                                                                
    int j;
    for(i=0; i<height; i++){                                                // Loop
      for(j=0; j<width; j++){
        printf("%c", maze->cells[i][j]);
      }
      printf("\n");                                                         // Next line
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if(row<0 || col<0 || row>-maze->height || col>=maze->width) {
      return 0;   
    }                                                                      // Checking for bounds
    if(maze->cells[row][col]=='E') {
      maze->cells[maze->startRow][maze->startColumn]='S';                  // Checking for End
      return 1;  
    }
    if(maze->cells[row][col] !=' '&&  maze->cells[row][col] != 'S')
      return 0;                   
                                         
    maze->cells[row][col] = '*'; 
   
    if(solveMazeDFS(maze, col-1, row)) {
      return 1;                                                            // Check Left
    }
    if(solveMazeDFS(maze, col, row+1)) {
      return 1;                                                            // Check Up         
    }        
    if(solveMazeDFS(maze, col+1, row)) {
      return 1;                                                            // Check Right
    }
    if(solveMazeDFS(maze, col, row-1)) {
      return 1;                                                            // Check Down
    }
    maze->cells[row][col] = '~';                                           // Else, assign '~'
    return 0;
}
