#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isValidDecimalFormat(const char *str);

int main( int argc, char *argv[])
{   
    if (argc < 2) {
        printf("Please enter the numbers you want to calculate in the form h.mm");
        return 1;
    }

    int hours = 0;
    int minutes = 0;

    for (int i = 1; i < argc; i++) {
        if (!isValidDecimalFormat(argv[i])) {
            printf("Error: Time %d ('%s') is not in a valid format. Please enter all values in the form h.mm\n", i, argv[i]);
            return 2; // Skip this iteration and move to the next argument
        }

        char *input = argv[i];
        char *token;
        int arg_hours, arg_mins;

        // Splitting the input at the decimal point
        token = strtok(input, ".");
        if (token != NULL) {
            arg_hours = atoi(token);  // Convert before decimal to integer
            hours = hours + arg_hours;
            token = strtok(NULL, ".");

            if (token != NULL) {
                arg_mins = atoi(token);  // Convert after decimal to integer
                minutes = minutes + arg_mins;
            }
        } 
    }

    while(minutes > 60){
        hours = hours + 1;
        minutes = minutes - 60;
    }

    printf("Total time: %d hours, %d minutes\n", hours, minutes);

}


// Check that each argument is in valid format
int isValidDecimalFormat(const char *str) {
    if (str == NULL) // Ensure string is not NULL
        return 0;

    // Check for correct overall format: one digit, then a dot, then two digits
    int len = strlen(str);
    if (len != 4) // Length must be exactly 4 characters (e.g., 1.23)
        return 0;

    // Check individual character positions
    if (!isdigit(str[0])) // First character must be a digit
        return 0;

    if (str[1] != '.') // Second character must be a dot
        return 0;

    if (!isdigit(str[2]) || !isdigit(str[3])) // Third and fourth must be digits
        return 0;

    if (str[2] > '5') // '5' in ASCII comparison
        return 0;

    return 1; // If all checks are passed, return true
}