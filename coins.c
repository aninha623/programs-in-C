//B4E772

#include <stdio.h>

int main(void){

    //initialize all variables that will be used throughout the program
    const int MAX_TYPES = 20;
    char identifiers[MAX_TYPES];
    int values[MAX_TYPES];
    int num_denominations;
    int counter [20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char coin_type;
    int coin_value;
    char coin_command;
    char coin_style;
    int coin_quantity;
    int total_value;
    int check = 0;

    //ask for number of denominations
    printf("How many denominations? ");
    //error handling: if user tries to pass a non-digit into num_denominations, raise error & return 1
    if (scanf(" %d", &num_denominations) != 1){
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    //ask for coin identifiers and values of coins
    for (int i =0; i <= (num_denominations-1); i++){
        printf("Enter coin identifier and value in cents: ");

        //error handling: if user inputs invalid identifier and value for coin denomination, raise error and return 1
        if (scanf(" %c%d", &coin_type, &coin_value) != 2){
            fprintf(stderr, "Invalid input\n");
            return 1;
        }

        //append each coin type and value to identifiers array and values array
        identifiers[i] = coin_type;
        values[i] = coin_value;
    }

    //prompt command for the first time
    printf("Enter a command: ");

    //scan in and read the first letter/the command letter. loop terminates with ctrl-d.
    while (scanf(" %c", &coin_command) != EOF){
        //set up handling to deal with different command cases
        switch(coin_command){

            case 'a': 

            //read in coin type and quantity
            //error handling: if the user doesn't enter a valid identifier and counter
            //after the "a" command
            if (scanf(" %c%d", &coin_style, &coin_quantity) !=2){
                fprintf(stderr, "Invalid input\n");
                return 1;
            }

            //loop through the number of coin denominations and find the index of whenever the
            //coin type that the user inputs with the coin command matches
            for (int j =0; j < num_denominations; j++){
                check = 0;
                
                if (identifiers[j] == coin_style){
                    //populate counter array with updated quantity of each coin. this array will 
                    //align with the identifiers and value arrays
                    counter[j] = counter[j] + coin_quantity;
                    check = 1;
                    break;
                }
                
            }
            
            //error handling: if coin is present, value will be updated to 1 in for loop above
            //if coin is not present already in identifier array, raise error and return error code 2
            if (check==0){
                fprintf(stderr, "Unknown coin identifier\n");
                return 2;
            }

            break;

            case 'r': 

            //read in coin type and quantity
            //error handling: if the user doesn't enter a valid identifier and counter
            //after the "a" command
            if (scanf(" %c%d", &coin_style, &coin_quantity) !=2){
                fprintf(stderr, "Invalid input\n");
                return 1;
            }
            
            //loop through the number of coin denominations and find the index of whenever the
            //coin type that the user inputs with the coin command matches
            for (int j =0; j < num_denominations; j++){
                check = 0;
                
                if (identifiers[j] == coin_style){
                    //populate counter array with updated quantity of each coin. this array will 
                    //align with the identifiers and value arrays
                    counter[j] = counter[j] - coin_quantity;
                    check = 1;
                    break;
                }
                
            }
            
            //error handling: if coin is present, value will be updated to 1 in for loop above
            //if coin is not present already in identifier array, raise error and return error code 2
            if (check==0){
                fprintf(stderr, "Unknown coin identifier\n");
                return 2;
            }
            break;

            case 's':
            
            //print user's coin collection as CSV, print header values
            printf("Identifier,Face Value,Count,Total Value \n");

            //initialize the total value of the collection to 0
            total_value = 0;
            
            for (int i=0; i < num_denominations; i++){
                
                //initialize new variables to avoid indexing issues
                char coin_identifier = identifiers[i];
                int coin_significance = values[i];
                int coin_count = counter[i];
                int gen_value = values[i]*counter[i];

                //print according to CSV headers
                printf("%c,", coin_identifier);
                printf("%d,", coin_significance);
                printf("%d,", coin_count);
                printf("%d \n", gen_value);

                //calculate total value of collection
                total_value += gen_value;

                }
            
            //format total value of collection into dollars and cents instead of just cents
            if (total_value>99){
                int remainder = total_value%100;
                int dollars = total_value/100;
                
                printf("Overall value of collection: $%d.%02d\n", dollars, remainder);
            }
            else {
                printf("Overall value of collection: $0.%02d\n", total_value);
            }

            //keep prompting commands from user until user terminates
            //printf("Enter a command: ");
            break;

            //establish user command to quit command loop
            case 'q': 
            printf("Bye!\n");
            return 0;
            
            //error handling: if the user enters a command character that isn't one 
            //of the previously defined commands: exit with exit code 3
            default: fprintf(stderr, "Invalid command\n");
            return 3;
            
        }

        //continue prompting user to input a command until user either breaks the loop with
        //ctrl-d or q command
        printf("Enter a command: ");
        

    }
    //print Bye! after command loop ends
    printf("Bye!\n");

    //if no errors present, return 0
    return 0;
}