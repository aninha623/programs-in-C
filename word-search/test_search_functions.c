// test_search_functions.c
// anna andrade
// aandra12
// B4E772



#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "search_functions.h"


/* 
 * Declarations for tester functions whose definitions appear below.
 * (You will need to fill in the function definition details, at the
 * end of this file, and add comments to each one.) 
 * Additionally, for each helper function you elect to add to the 
 * provided search_functions.h, you will need to supply a corresponding
 * tester function in this file.  Add a declaration for it here, its
 * definition below, and a call to it where indicated in main.
 */
void test_file_eq();      // This one is already fully defined below.
void test_populate_grid();
void test_find_right();
void test_find_left();
void test_find_down();
void test_find_up();
void test_find_all();


/*
 * Main method which calls all test functions.
 */
int main() {
  printf("Testing file_eq...\n");
  test_file_eq();
  printf("Passed file_eq test.\n\n");

  printf("Running search_functions tests...\n");
  test_populate_grid();
  test_find_right();
  test_find_left();
  test_find_down();
  test_find_up();
  test_find_all();
  

  /* You may add calls to additional test functions here. */

  printf("Passed search_functions tests!!!\n");
}



/*
 * Test file_eq on same file, files with same contents, files with
 * different contents and a file that doesn't exist.
 * Relies on files test1.txt, test2.txt, test3.txt being present.
 */
void test_file_eq() {
  FILE* fptr = fopen("test1.txt", "w");
  fprintf(fptr, "this\nis\na test\n");
  fclose(fptr);

  fptr = fopen("test2.txt", "w");
  fprintf(fptr, "this\nis\na different test\n");
  fclose(fptr);

  fptr = fopen("test3.txt", "w");
  fprintf(fptr, "this\nis\na test\n");
  fclose(fptr);

  assert( file_eq("test1.txt", "test1.txt"));
  assert( file_eq("test2.txt", "test2.txt"));
  assert(!file_eq("test2.txt", "test1.txt"));
  assert(!file_eq("test1.txt", "test2.txt"));
  assert( file_eq("test3.txt", "test3.txt"));
  assert( file_eq("test1.txt", "test3.txt"));
  assert( file_eq("test3.txt", "test1.txt"));
  assert(!file_eq("test2.txt", "test3.txt"));
  assert(!file_eq("test3.txt", "test2.txt"));
  assert(!file_eq("", ""));  // can't open file
}


//test populate grid based on if the resulting number is what it is expected to be
void test_populate_grid(){

  /*
  //debugging populate_grid
  printf("%d \n", grid_size);
  for (int i=0; i<grid_size; i++){
    for (int j=0; j<grid_size; j++){
      printf("%c ", grid[i][j]);
    }
    printf("\n");
  }
  */

  char grid[MAX_SIZE][MAX_SIZE]; //initialize grid 

  int result = 0;

  result = populate_grid(grid, "boo");
  assert(result == 4);

  assert(populate_grid(grid, "boo")== 4); //successful

  //assert(populate_grid(grid, "x.txt") == -1);
  printf("populate grid works\n");
  

}

//test find_right based on if the result that the function writes to a file matches 
//the expected output which is written in a different file
void test_find_right(){

  char grid1[MAX_SIZE][MAX_SIZE] = {
    {'o','n','e','d'},
    {'e','n','o','w'},
    {'r','e','s','t'},
    {'a','b','e','e'}
  };

  int result = 0;
  int result2= 0;
  int bruh = 4;


  FILE* output_file = fopen("output.txt", "w");
  FILE* output2_file = fopen("output2.txt", "w");

  char one[]= "one";
  char bee[] = "bee";
  result = find_right(grid1, bruh, one, output_file);
  result2 = find_right(grid1, bruh, bee, output2_file);

  
  //close files
  fclose(output_file);
  fclose(output2_file);

  //test for "one"
  assert( file_eq("output.txt", "approved.txt"));

  //test for "bee"
  assert( file_eq("output2.txt", "approved.txt"));

  printf("find_right works\n");
  

}

//test find_left based on if the result that the function writes to a file matches 
//the expected output which is written in a different file
void test_find_left(){

char grid1[MAX_SIZE][MAX_SIZE] = {
    {'o','w','e','d'},
    {'e','n','o','w'},
    {'r','i','s','t'},
    {'a','b','e','e'}
  };

  int result = 0;
  int bruh = 4;


  FILE* output_file = fopen("left_output.txt", "w");
  
  char dew[]= "dew";
  result = find_left(grid1, bruh, dew, output_file);
 
  //close files
  fclose(output_file);

  //test for "dew"
  assert( file_eq("left_output.txt", "approved.txt"));

  printf("find_left works\n");
}

//test find_down based on if the result that the function writes to a file matches 
//the expected output which is written in a different file
//tests if function can find multiple occurences of a word in the same direction
void test_find_down(){

  char grid1[MAX_SIZE][MAX_SIZE] = {
    {'o','w','y','d'},
    {'y','n','o','a'},
    {'o','i','u','t'},
    {'u','b','r','e'}
  };

  int result = 0;
  int bruh = 4;


  FILE* output_file = fopen("down_output.txt", "w");
  
  char you[]= "you";
  result = find_down(grid1, bruh, you, output_file);
 
  //close files
  fclose(output_file);

  //test for "you"
  assert( file_eq("down_output.txt", "down_approved.txt"));

  printf("find_down works\n");

}


//test find_up based on if the result that the function writes to a file matches 
//the expected output which is written in a different file
//tests if the word can find multiple occurences of the same word
//tests if no output is also returned correctly
void test_find_up(){

  char grid1[MAX_SIZE][MAX_SIZE] = {
    {'p','w','y','p'},
    {'i','n','p','i'},
    {'r','i','i','r'},
    {'u','b','r','e'}
  };

  int result = 0;
  int result2 = 0;
  int bruh = 4;


  FILE* output_file = fopen("up_output.txt", "w");
  FILE* output2_file = fopen("up_null.txt", "w");
  
  char rip[]= "rip";
  result = find_up(grid1, bruh, rip, output_file);

  char tea[] = "tea";
  result2 = find_up(grid1, bruh, tea, output2_file);
 
  //close files
  fclose(output_file);
  fclose(output2_file);

  //test for "rip"
  assert( file_eq("up_output.txt", "up_approved.txt"));
  assert( file_eq("up_null.txt", "null_approved.txt"));

  printf("find_up works\n");


}

//test find_all based on if the result that the function writes to a file matches 
//the expected output which is written in a different file
void test_find_all(){

  char grid1[MAX_SIZE][MAX_SIZE] = {
    {'p','i','t','k'},
    {'o','l','y','y'},
    {'p','k','e','e'},
    {'t','y','e','s'}
  };

  int result = 0;
  int bruh = 4;


  FILE* output_file = fopen("all_output.txt", "w");
  
  char yes[]= "yes";
  result = find_all(grid1, bruh, yes, output_file);
 
  //close files
  fclose(output_file);

  //test for "yes"
  assert( file_eq("all_output.txt", "all_approved.txt"));

  printf("find_all works\n");


}

