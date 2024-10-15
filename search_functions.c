// search_functions.c
// anna andrade
// aandra12
// B4E772


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "search_functions.h"

         

/* 
 * Given a filename and a MAX_SIZExMAX_SIZE grid to fill, this function 
 * populates the grid and returns n, the actual grid dimension. 
 * If filename_to_read_from can't be opened, this function returns -1.
 * If the file contains an invalid grid, this function returns -2.
 */

 //[]rows, [max_size] columns
int populate_grid(char grid[][MAX_SIZE], char filename_to_read_from[]){

  //open file to read from
  FILE* input = fopen(filename_to_read_from, "r");

  //error handling: if filename_to_read_from can't be opened, return -1
  if (input == NULL){
    fprintf(stdout, "Grid file failed to open.\n");
    fclose(input);
    return -1;
  }

  char letter[MAX_SIZE +1]; //array of each row of letters
  int parse = fscanf(input," %s ", letter); //read in row by row
  int rows = (int)strlen(letter); //length of first row
  int row_num = 0; //initialize row counter

  //error handling: if the number of rows is 0
  if (!rows){
    fprintf(stdout, "Invalid grid.\n");
    fclose(input);
    return -2;
  }

  //iterate through each row
  while(parse == 1){
    int length = (int)strlen(letter); //length of current row of characters

    //error handling: if grid rows have differing numbers of letters
    if (length != rows){
      fprintf(stdout, "Invalid grid.\n");
      fclose(input);
      return -2;
    }

    //error handling: if the number of rows/columns is greater than 10
  if (rows > MAX_SIZE){
    fprintf(stdout, "Invalid grid.\n");
    fclose(input);
    return -2;
  }

    for (int i=0; i< rows; i++){
      //convert every letter that is scanned in into lowercase
      letter[i] = tolower(letter[i]);
      //populate grid in current row with the letter from the txt file at that index
      grid[row_num][i] = letter[i];
    }

    //move on to next row
    row_num++;

    //revert parse to be 1 again so while loop doesn't terminate after just scanning in first row of text
    parse = fscanf(input," %s ", letter);
  }

  //error handling: if the number of rows doesn't match the number of columns
  if (rows != row_num){
    fprintf(stdout, "Invalid grid.\n");
    fclose(input);
    return -2;
  }


  fclose(input); //close file

  //return dimensions of grid
  return row_num; 

}


/* 
 * Given a populated grid, size of the grid, word to search for, 
 * and file to write the output to, this function iterates through the
 * rows, then through each column from left to right until a match for the
 * word is found. When the word is found, it prints out the word and the 
 * coordinates of the first letter of the word and indicates which direction
 * is being searched in. 
 */
int find_right(char grid[][MAX_SIZE], int n, char word[], FILE *write_to){

  int column_num = n; //size of grid
  int len_word = (int)strlen(word); //length of word
  char right = 'R'; 

  //indices for word in grid
  int first_index;
  int final_index;

  //convert word into lowercase
  for (int i=0; i<len_word; i++){
    word[i] = tolower(word[i]);
  }
  
  int counter = 0; //counts number of appearances of word rightwards

  //loop thru each row
  for (int row =0; row<column_num; row++){

    //loop through each letter in row  
    for (int letter_main=0; letter_main<column_num; letter_main++){

      //if the letter in row matches the first letter of the word being searched for
      if (grid[row][letter_main] == word[0]){

        int letter_sub=0;
        //iterate further to check if all the letters match in word and grid
         for (letter_sub = 0; grid[row][letter_main+letter_sub] && word[letter_sub]; letter_sub++){

          //if the letters don't match, break
          if (grid[row][letter_main+letter_sub] != word[letter_sub]){
            break;
           }
         }

           //if you reach the end of the word and the loop hasn't broken, take indices
          if (letter_sub == len_word){
            first_index = row;
            final_index = letter_main;

            //increment counter of how many times a word shows up
            counter++;

            //write number of word occurences to write_to
            fprintf(write_to, "%d\n", counter);
            
            //print "{word} {row index} {column index} R"
            printf("%s %d %d %c\n", word, first_index, final_index, right);
          }
        }
      }
    }
  
  return counter; 

}


/* 
 * Given a populated grid, size of the grid, word to search for, 
 * and file to write the output to, this function iterates through the
 * rows, then through each column from left to right until a match for the
 * reverse spelling of the word is found. When the word is found, it prints out the word and the 
 * coordinates of the first letter of the word and indicates which direction
 * is being searched in. 
 */
int find_left (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){

  int column_num = n; //size of grid
  int len_word = (int)strlen(word); //length of word
  char left = 'L'; 

  //indices for word in grid
  int first_index;
  int final_index;

  //convert word into lowercase
  for (int i=0; i<len_word; i++){
    word[i] = tolower(word[i]);
  }
  
  char word_rev[len_word];
  for (int i=0; i<=len_word; i++){
    word_rev[i] = word[i];
  }

  //reverse word
  for (int i=0, j=len_word-1; i<=j; i++, j--){
    char l = word_rev[i];
    word_rev[i] = word_rev[j];
    word_rev[j] = l;
  }
  
  int counter = 0; //counts number of appearances of word leftwards

  //loop thru each row
  for (int row =0; row<column_num; row++){

    //loop through each letter in row  
    for (int letter_main=0; letter_main<column_num; letter_main++){

      //if the letter in row matches the first letter of the word being searched for
      if (grid[row][letter_main] == word_rev[0]){

        int letter_sub=0;
        //iterate further to check if all the letters match in word and grid
         for (letter_sub = 0; grid[row][letter_main+letter_sub] && word_rev[letter_sub]; letter_sub++){

          //if the letters don't match, break
          if (grid[row][letter_main+letter_sub] != word_rev[letter_sub]){
            break;
           }
         }

           //if you reach the end of the word and the loop hasn't broken, take indices
          if (letter_sub == len_word){
            first_index = row;
            final_index = letter_main + len_word -1;

            //print "{word} {row index} {column index} R"
            printf("%s %d %d %c\n", word, first_index, final_index, left);

            //increment counter of how many times a word shows up
            counter++;

            //write number of word occurences to write_to
            fprintf(write_to, "%d\n", counter);
          }
        }
      }
    }
  
  return counter; 

}


/* 
 * Given a populated grid, size of the grid, word to search for, 
 * and file to write the output to, this function iterates through the
 * columns, then through each row from up to down until a match for the
 * word is found. When the word is found, it prints out the word and the 
 * coordinates of the first letter of the word and indicates which direction
 * is being searched in. 
 */
int find_down (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){

  int column_num = n; //size of grid
  int len_word = (int)strlen(word); //length of word
  char down = 'D'; 

  //indices for word in grid
  int first_index;
  int final_index;

  //convert word into lowercase
  for (int i=0; i<len_word; i++){
    word[i] = tolower(word[i]);
  }
  
  int counter = 0; //counts number of appearances of word downwards

  //loop thru each column
  for (int column =0; column< column_num; column++){

    //loop through each letter in column  
    for (int letter_main=0; letter_main< column_num; letter_main++){

      //if the letter in column matches the first letter of the word being searched for
      if (grid[letter_main][column] == word[0]){
        
        int letter_sub=0;
        //iterate further to check if all the letters match in word and grid
         for (letter_sub = 0; grid[letter_main+letter_sub][column] && word[letter_sub]; letter_sub++){

          //if the letters don't match, break
          if (grid[letter_main+letter_sub][column] != word[letter_sub]){
            break;
           }
         }

           //if you reach the end of the word and the loop hasn't broken, take indices
          if (letter_sub == len_word){
            first_index = letter_main;
            final_index = column;
            
            //print "{word} {row index} {column index} D"
            printf("%s %d %d %c\n", word, first_index, final_index, down);

            //increment counter of how many times a word shows up
            counter++;

            //write number of word occurences to write_to
            fprintf(write_to, "%d\n", counter);
          }
        }
      }
    }
  
  return counter; 

}


/* 
 * Given a populated grid, size of the grid, word to search for, 
 * and file to write the output to, this function iterates through the
 * columns, then through each row starting from the last row to the first until a match for the
 * word is found. When the word is found, it prints out the word and the 
 * coordinates of the first letter of the word and indicates which direction
 * is being searched in. 
 */
int find_up   (char grid[][MAX_SIZE], int n, char word[], FILE *write_to){

  int column_num = n; //size of grid
  int len_word = (int)strlen(word); //length of word
  char up = 'U'; 

  //indices for word in grid
  int first_index;
  int final_index;

  //convert word into lowercase
  for (int i=0; i<len_word; i++){
    word[i] = tolower(word[i]);
  }
  
  
  int counter = 0; //counts number of appearances of word upwards

  //loop thru each column
  for (int column =0; column<column_num; column++){

    //loop through each letter in column  
    for (int letter_main=(column_num); letter_main >=0; letter_main--){

      //if the letter in column matches the first letter of the word being searched for
      if (grid[letter_main][column] == word[0]){

        int letter_sub=0;
        //iterate further to check if all the letters match in word and grid
         for (letter_sub = 0; grid[letter_main-letter_sub][column] && word[letter_sub]; letter_sub++){

          //if the letters don't match, break
          if (grid[letter_main-letter_sub][column] != word[letter_sub]){
            break;
           }
         }

           //if you reach the end of the word and the loop hasn't broken, take indices
          if (letter_sub == len_word){
            first_index = letter_main;
            final_index = column;

            //print "{word} {row index} {column index} R"
            printf("%s %d %d %c\n", word, first_index, final_index, up);

            //increment counter of how many times a word shows up
            counter++;

            //write number of word occurences to write_to
            fprintf(write_to, "%d\n", counter);
          }
        }
      }
    }
  
  return counter; 

}


/* 
 * Given a grid of characters, size of the grid, word being searched for,
 * and file to write the return value to, find_all calls all 4 find functions
 * and totals the number of times the word is found. This total is returned. 
 * If the word is not found, it returns the word and a Not Found message.
 */
int find_all  (char grid[][MAX_SIZE], int n, char word[], FILE *write_to) {

  int total = 0; //initialize total counter for how many times word is found in any direction

  int total_right = find_right( grid, n, word, write_to);
  int total_left = find_left( grid, n, word, write_to);
  int total_down = find_down( grid, n, word, write_to);
  int total_up = find_up( grid, n, word, write_to);
  total = total_right + total_left + total_down + total_up;

  //if total = 0 or word isn't found in the grid
  if (!total){
    fprintf(stdout, "%s - Not Found\n", word);
  }

  //write counter to output file
  fprintf(write_to, "%d\n", total);

  //return total times word was found
  return total;

} 


/*
 * Reads lhs and rhs character by character until either reaches eof.
 * Returns true if the files can be read and the two files match
 * character by character. Returns false if two files either can't be
 * opened or don't match. The definition of this function is provided 
 * for you.
 */
int file_eq(char lhs_name[], char rhs_name[]) {
  FILE* lhs = fopen(lhs_name, "r");
  FILE* rhs = fopen(rhs_name, "r");

  // don't compare if we can't open the files
  if (lhs == NULL || rhs == NULL) return 0;

  int match = 1;
  // read until both of the files are done or there is a mismatch
  while (!feof(lhs) || !feof(rhs)) {
	if (feof(lhs) ||                      // lhs done first
		feof(rhs) ||                  // rhs done first
		(fgetc(lhs) != fgetc(rhs))) { // chars don't match
	  match = 0;
	  break;
	}
  }
  fclose(lhs);
  fclose(rhs);
  return match;
}

