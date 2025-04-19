//Stephen Bangs
//4/16/25
//CS333 - Jesse Chaney
//Lab 1 - Caesar Cipher, XOR Cipher, mystat()
//
//This is the caesar cipher file. It takes options e, d, and s with required argument.
//They encrypt, decrypt, and change number of cryption. default encryption amount is 3.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define OPTIONS "eds:"

//options for 
#define PRINT_START 32
#define PRINT_END 126
#define PRINT_TOTAL (PRINT_END - PRINT_START + 1)

//prototype for shifting characters function
char ch_shift(char, int, int);


int main(int argc, char *argv[]) {

	//holds shift amt, encrypt/decrypt flag, and char for passing to ch_shift()
	int shift_amt = 3;
	int crypt_opt = 1;
	int curr_char = 0;
	int opt = 0;

	while((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
			//encrypt flag
			case 'e':
				fprintf(stderr, "\ncase e\n");
				crypt_opt = 1;
				break;
			//decrypt flag
			case 'd':
				fprintf(stderr, "\ncase d\n");
				crypt_opt = -1;
				break;
			//#chars to crypt
			case 's':
				fprintf(stderr, "\ncase s: %s\n", optarg);
				//check for valid digit argument
				for(int i = 0; optarg[i]; i++){
					if(!isdigit(optarg[i])){
					fprintf(stderr, "\nPlease enter an integer from 0-95.\n");
					exit(EXIT_FAILURE);
					}
				}
				//convert to int, check bounds
				shift_amt = atoi(optarg);
				if(shift_amt < 0 || shift_amt > 95){
					fprintf(stderr, "Character shift out of bounds. Must be 0-95 inclusive.\n");
					exit(EXIT_FAILURE);
				}
				break;
			//shift_amt remains 3 if default 
			default:
				fprintf(stderr, "\ncase default\n");
				break;
		}
	}
	
	//grab chars from stdin sequentially in while loop, 
	//then sequentially output to stdout one at a time
	while((curr_char = getchar()) != EOF) {
		putchar(ch_shift(curr_char, shift_amt, crypt_opt));
	}

	return EXIT_SUCCESS;

}


//takes current char, shifts, can either encrypt or decrypt. Returns shifted char.
char ch_shift(char curr_char, int shift_amt, int crypt_opt){
	if(curr_char < PRINT_START || curr_char > PRINT_END) {
		return curr_char;
	}

	//flips direction for decrypt - when taking into account print_start later
	//when % ing
	if (crypt_opt == -1) {
		shift_amt = PRINT_TOTAL-shift_amt;
	}
	
	//cryption step
	curr_char = ((curr_char - PRINT_START + shift_amt) % PRINT_TOTAL) + PRINT_START;

	return curr_char;
}
