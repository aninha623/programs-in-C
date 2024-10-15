//project.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm_io.h"
#include "image_manip.h"

// Return (exit) codes
#define RC_SUCCESS            0
#define RC_MISSING_FILENAME   1
#define RC_OPEN_FAILED        2
#define RC_INVALID_PPM        3
#define RC_INVALID_OPERATION  4
#define RC_INVALID_OP_ARGS    5
#define RC_OP_ARGS_RANGE_ERR  6
#define RC_WRITE_FAILED       7
#define RC_UNSPECIFIED_ERR    8

void print_usage();

//this function will execute just blend because it takes in more files
int execute_blend(int argc, char* argv[]);
//this function will execute any other function
int execute_everything_else();

int main (int argc, char* argv[]) {

  //error handling: checks if enough command line arguments are provided to run functions
  if(argc < 4){
    fprintf(stderr, "Wrong usage. Mandatory arguments not provided.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }

  //take in the operation name
  char* test = argv[3];
  //initialize result variable, set to 8 just in case anything freaky happens
  int result = 8;

  if (strcmp(test, "blend") == 0){
    result = execute_blend(argc, argv);
  }
  else{
    result = execute_everything_else(argc, argv);
  }

  return result;

}


int execute_everything_else(int argc, char* argv[]){

  //take in test name
  char* test = argv[3];
  
  //grayscale
  if (strcmp(test, "grayscale") == 0) {
  //take in necessary arguments for grayscale
  char * first = argv[1]; // input file
  //error handling: input file name not found
  if (first == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }
  char * second = argv[2]; //output file
  //error handling: output file name not found
  if (second == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }

  //open files
  FILE * input_file = fopen(first, "rb"); //open first input
  //error handling: first input file couldn't be opened
  if (input_file == NULL){
    fprintf(stderr, "Input file I/O error: issue opening input file.\n");
    return RC_OPEN_FAILED; //return 2
  }
  
  FILE * output_file = fopen(second, "wb"); //open output file
  //error handling: output file couldn't be opened
  if (output_file == NULL){
    fprintf(stderr, "Input file I/O error: issue opening output file.\n");
    return RC_OPEN_FAILED; //return 2
  }

  //read input files as ppm files
  Image in = read_ppm(input_file);
  //error handling: first input file cannot be read as ppm file
  if (in.data == NULL){
    fprintf(stderr, "Invalid PPM error: input file could not be read as PPM file.\n");
    fclose(input_file);
    fclose(output_file);
    return RC_INVALID_PPM; //return 3
  }

  //check for missing arguments
  if (argc != 4){
    fprintf(stderr, "Incorrect number of arguments for Grayscale operation.\n");
    print_usage();
    return RC_INVALID_OP_ARGS; //return 5
  }

  //actually execute grayscale
  Image out = grayscale(in);
  int out_pixel_count = write_ppm(output_file, out);
  //error handling: output file I/O error
  if (out_pixel_count == 1){ //failure return for write_ppm is 1
    fprintf(stderr, "Output file I/O error: Failed to write output to PPM");
    fclose(input_file);
    free_image(&in);
    fclose(output_file);
    free_image(&out);
    return RC_WRITE_FAILED; //return 7
  }

  //error handling: calloc error in image_manip.c
  if (out.data == NULL){
    fprintf(stderr, "Other error not specified.\n");
    fclose(input_file);
    free_image(&in);
    fclose(output_file);
    free_image(&out);
    return RC_UNSPECIFIED_ERR; //return 8
  }

  //function finished executing! close all files and free memory
  fclose(input_file);
  free_image(&in);
  fclose(output_file);
  free_image(&out);

  return RC_SUCCESS; //return 0
  }

  //rotate-ccw 
  else if (strcmp(test, "rotate-ccw")== 0) {
  //take in necessary arguments for rotate
  char * first = argv[1]; // input file
  //error handling: input file name not found
  if (first == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }
  char * second = argv[2]; //output file
  //error handling: output file name not found
  if (second == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }

  //open files
  FILE * input_file = fopen(first, "rb"); //open first input
  //error handling: first input file couldn't be opened
  if (input_file == NULL){
    fprintf(stderr, "Input file I/O error: issue opening input file.\n");
    return RC_OPEN_FAILED; //return 2
  }
  
  FILE * output_file = fopen(second, "wb"); //open output file
  //error handling: output file couldn't be opened
  if (output_file == NULL){
    fprintf(stderr, "Input file I/O error: issue opening output file.\n");
    return RC_OPEN_FAILED; //return 2
  }

  //read input files as ppm files
  Image in = read_ppm(input_file);
  //error handling: input file cannot be read as ppm file
  if (in.data == NULL){
    fprintf(stderr, "Invalid PPM error: input file could not be read as PPM file.\n");
    fclose(input_file);
    fclose(output_file);
    return RC_INVALID_PPM; //return 3
  }

  //check for missing arguments
  if (argc != 4){
    fprintf(stderr, "Incorrect number of arguments for Rotate-CCW operation.\n");
    print_usage();
    return RC_INVALID_OP_ARGS; //return 5
  }

  //actually execute rotate-ccw
  Image out = rotate_ccw(in);
  int out_pixel_count = write_ppm(output_file, out);
  //error handling: output file I/O error
  if (out_pixel_count == 1){ //failure return for write_ppm is 1
    fprintf(stderr, "Output file I/O error: Failed to write output to PPM");
    fclose(input_file);
    free_image(&in);
    fclose(output_file);
    free_image(&out);
    return RC_WRITE_FAILED; //return 7
  }

  //error handling: calloc error in image_manip.c
  if (out.data == NULL){
    fprintf(stderr, "Other error not specified.\n");
    fclose(input_file);
    free_image(&in);
    fclose(output_file);
    free_image(&out);
    return RC_UNSPECIFIED_ERR; //return 8
  }

  //function finished executing! close all files and free memory
  fclose(input_file);
  free_image(&in);
  fclose(output_file);
  free_image(&out);

  return RC_SUCCESS; //return 0
  }

  //pointilism
  else if (strcmp(test, "pointilism") == 0) {
    
  //take in necessary arguments for pointilism
  char * first = argv[1]; // input file
  //error handling: input file name not found
  if (first == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }
  char * second = argv[2]; //output file
  //error handling: output file name not found
  if (second == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }

  //open files
  FILE * input_file = fopen(first, "rb"); //open first input
  //error handling: first input file couldn't be opened
  if (input_file == NULL){
    fprintf(stderr, "Input file I/O error: issue opening input file.\n");
    return RC_OPEN_FAILED; //return 2
  }
  
  FILE * output_file = fopen(second, "wb"); //open output file
  //error handling: output file couldn't be opened
  if (output_file == NULL){
    fprintf(stderr, "Input file I/O error: issue opening output file.\n");
    return RC_OPEN_FAILED; //return 2
  }

  //read input files as ppm files
  Image in = read_ppm(input_file);
  //error handling: first input file cannot be read as ppm file
  if (in.data == NULL){
    fprintf(stderr, "Invalid PPM error: input file could not be read as PPM file.\n");
    fclose(input_file);
    fclose(output_file);
    return RC_INVALID_PPM; //return 3
  }

  //check for missing arguments
  if (argc != 4){
    fprintf(stderr, "Incorrect number of arguments for Pointilism operation.\n");
    print_usage();
    return RC_INVALID_OP_ARGS; //return 5
  }

  //actually execute pointilism
  Image out = pointilism(in, 1);
  int out_pixel_count = write_ppm(output_file, out);
  //error handling: output file I/O error
  if (out_pixel_count == 1){ //failure return for write_ppm is 1
    fprintf(stderr, "Output file I/O error: Failed to write output to PPM");
    fclose(input_file);
    free_image(&in);
    fclose(output_file);
    free_image(&out);
    return RC_WRITE_FAILED; //return 7
  }

  //error handling: calloc error in image_manip.c
  if (out.data == NULL){
    fprintf(stderr, "Other error not specified.\n");
    fclose(input_file);
    free_image(&in);
    fclose(output_file);
    free_image(&out);
    return RC_UNSPECIFIED_ERR; //return 8
  }

  //function finished executing! close all files and free memory
  fclose(input_file);
  free_image(&in);
  fclose(output_file);
  free_image(&out);

  return RC_SUCCESS; //return 0
  }

  else{
    //error handling: not any of the image processing functions
    fprintf(stderr, "Unsupported image processing operations.\n");
    print_usage();
    return RC_INVALID_OPERATION; //return 4
  }

  return RC_SUCCESS;

}



int execute_blend(int argc, char* argv[]){
  //take in necessary arguments for blend
  char * first = argv[1]; //first input file
  //error handling: first input file name not found
  if (first == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }
  char * second = argv[2]; //second input file
  //error handling: second input file name not found
  if (second == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }
  char * third = argv[4]; //output file to write to
  //error handling: third input file name not found
  if (third == NULL){
    fprintf(stderr, "Wrong usage, mandatory arguments not provided: Filename not found.\n");
    print_usage();
    return RC_MISSING_FILENAME; //return 1
  }

  char * alpha_value = argv[5]; //alpha pointer
  //convert alpha to a double in case it's a string
  char * end_of; 
  double alpha = strtod(argv[5], &end_of);

  //open files
  FILE * input_file1 = fopen(first, "rb"); //open first input
  //error handling: first input file couldn't be opened
  if (input_file1 == NULL){
    fprintf(stderr, "Input file I/O error: issue opening first input file.\n");
    return RC_OPEN_FAILED; //return 2
  }
  FILE * input_file2 = fopen(second, "rb"); //open second file
  //error handling: second input file couldn't be opened
  if (input_file2 == NULL){
    fprintf(stderr, "Input file I/O error: issue opening second input file.\n");
    return RC_OPEN_FAILED; //return 2
  }
  FILE * output_file = fopen(third, "wb"); //open output file
  //error handling: output file couldn't be opened
  if (output_file == NULL){
    fprintf(stderr, "Input file I/O error: issue opening output file.\n");
    return RC_OPEN_FAILED; //return 2
  }

  //read input files as ppm files
  Image in1 = read_ppm(input_file1);
  //error handling: first input file cannot be read as ppm file
  if (in1.data == NULL){
    fprintf(stderr, "Invalid PPM error: first input file could not be read as PPM file.\n");
    fclose(input_file1);
    fclose(output_file);
    return RC_INVALID_PPM; //return 3
  }
  Image in2 = read_ppm(input_file2);
  //error handling: second input file cannot be read as ppm file
  if (in2.data == NULL){
    fprintf(stderr, "Invalid PPM error: second input file could not be read as PPM file.\n");
    fclose(input_file2);
    fclose(output_file);
    return RC_INVALID_PPM; //return 3
  }

  //check for missing arguments
  if (argc != 6){
    fprintf(stderr, "Incorrect number of arguments for Blend operation.\n");
    print_usage();
    return RC_INVALID_OP_ARGS; //return 5
  }

  //check for invalid arguments for blend
  if (*end_of != '\0'){
    fprintf(stderr, "1 Invalid arguments for Blend.\n");
    print_usage();
    fclose(input_file1);
    free_image(&in1);
    fclose(input_file2);
    free_image(&in2);
    fclose(output_file);
    return RC_OP_ARGS_RANGE_ERR; //return 6
  }

  //check if alpha value is valid
  if (alpha >= 1 || alpha <= 0){
    fprintf(stderr, "2 Invalid alpha value for Blend.\n");
    print_usage();
    fclose(input_file1);
    free_image(&in1);
    fclose(input_file2);
    free_image(&in2);
    fclose(output_file);
    return RC_OP_ARGS_RANGE_ERR; //return 6
  }

  if (alpha_value == NULL){
    fprintf(stderr, "3 Invalid alpha value for Blend.\n");
    print_usage();
    return RC_OP_ARGS_RANGE_ERR; //return 6
  }

  //actually execute blend
  Image out = blend(in1, in2, alpha);
  int out_pixel_count = write_ppm(output_file, out);
  //error handling: output file I/O error
  if (out_pixel_count == 1){ //failure return for write_ppm is 1
    fprintf(stderr, "Output file I/O error: Failed to write output to PPM");
    fclose(input_file1);
    free_image(&in1);
    fclose(input_file2);
    free_image(&in2);
    fclose(output_file);
    free_image(&out);
    return RC_WRITE_FAILED; //return 7
  }

  //error handling: calloc error in image_manip.c
  if (out.data == NULL){
    fprintf(stderr, "Other error not specified.\n");
    fclose(input_file1);
    free_image(&in1);
    fclose(input_file2);
    free_image(&in2);
    fclose(output_file);
    free_image(&out);
    return RC_UNSPECIFIED_ERR; //return 8
  }

  //function finished executing! close all files and free memory
  fclose(input_file1);
  free_image(&in1);
  fclose(input_file2);
  free_image(&in2);
  fclose(output_file);
  free_image(&out);

  return RC_SUCCESS; //return 0

}




void print_usage() {
  printf("USAGE: ./project <input-image> <output-image> <command-name> <command-args>\n");
  printf("SUPPORTED COMMANDS:\n");
  printf("   grayscale\n" );
  printf("   blend <target image> <alpha value>\n" );
  printf("   rotate-ccw\n" );
  printf("   pointilism\n" );
  printf("   blur <sigma>\n" );
  printf("   saturate <scale>\n" );
}