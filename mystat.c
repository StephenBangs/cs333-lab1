
//Stephen Bangs
//4/16/25
//CS333 - Jesse Chaney
//Lab 1 - Caesar Cipher, XOR Cipher, mystat()

//This is the mystat c code.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


//Source: Jesse Chaney Vid Assign 2
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

int main(int argc, char *argv[]) {

	for(int i = 1; i < argc; i++) {
		printf("Arg %d: %s\n", i, argv[i]);
	}


	return EXIT_SUCCESS;

}
