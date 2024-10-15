// word_search.c
// anna andrade
// aandra12
// B4E772


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "search_functions.h"


/*
 * This is the HW3 main function that performs a word search.
 */
int main(int argc, char* argv[]) {

  char grid[MAX_SIZE][MAX_SIZE]; //initialize grid from txt file
  char words [MAX_SIZE]; //initialize array to scan words into

  //error handling: if no file name is supplied, print error to stdout and return 1
  if(argc !=2){
    fprintf(stdout, "Please enter a command line argument.\n");
    return 1;
  }

  int grid_size = populate_grid(grid, argv[1]); //take grid dimension

  FILE* output = fopen("test1.txt", "w");

  //scan in words and iterate until user quits
  while (scanf(" %s", words) != EOF){
    find_all(grid, grid_size, words, output);
  }
  
  fclose(output);
  return 0;

}
