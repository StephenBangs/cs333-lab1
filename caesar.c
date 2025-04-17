//Stephen Bangs
//4/16/25
//CS333 - Jesse Chaney
//Lab 1 - Caesar Cipher, XOR Cipher, mystat()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define OPTIONS "eds:"

//Source: Jesse Chaney Video Assignment #2
#ifndef FALSE
# define FALSE 0
#endif // FALSE
#ifndef TRUE
# define TRUE 1
#endif //TRUE
       
#ifdef NOISY_DEBUG
#define NOISY_DEBUG_PRINT fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__);
#else //NOISY_DEBUG
# define NOISY_DEBUG_PRINT
#endif //NOISY_DEBUG

#define PRINT_START 32
#define PRINT_END 126
#define PRINT_TOTAL (PRINT_END - PRINT_START + 1)

char ch_shift(char, int, int);

int main(int argc, char *argv[]) {
	
	int shift_amt = 3;
	int crypt_opt = 1;
	int opt = 0;
	int curr_char = 0;
	while((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
			case 'e':
				fprintf(stderr, "\ncase e\n");
				crypt_opt = 1;
				break;
			case 'd':
				fprintf(stderr, "\ncase d\n");
				crypt_opt = -1;
				break;
			case 's':
				fprintf(stderr, "\ncase s: %s\n", optarg);
				
				for(int i = 0; optarg[i]; i++){
					if(!isdigit(optarg[i])){
					fprintf(stderr, "\nPlease enter an integer from 0-95.\n");
					exit(EXIT_FAILURE);
					}
				}
				shift_amt = atoi(optarg);
				if(shift_amt < 0 || shift_amt > 95){
					fprintf(stderr, "Character shift out of bounds. Must be 0-95 inclusive.\n");
					exit(EXIT_FAILURE);
				}
				break;
			default:
				fprintf(stderr, "\ncase default\n");
				break;
		}
	}
	
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

	//flips direction for decrypt
	if (crypt_opt == -1) {
		shift_amt = PRINT_TOTAL-shift_amt;
	}
	
	curr_char = ((curr_char - PRINT_START + shift_amt) % PRINT_TOTAL) + PRINT_START;

	return curr_char;

}
