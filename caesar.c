//Stephen Bangs
//4/16/25
//CS333 - Jesse Chaney
//Lab 1 - Caesar Cipher, XOR Cipher, mystat()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define OPTIONS "eds:"

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

	int opt = 0;
	while((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
			case 'e':
				printf("\ncase e\n");
				break;
			case 'd':
				printf("\ncase d\n");
				break;
			case 's':
				printf("\ncase s: %s\n", optarg);
				break;
			default:
				printf("\ncase default\n");
				break;
		}
	}

	//TODO
	argc = 0;
	argc++;
	argv = NULL;
	argv++;

return EXIT_SUCCESS;

}
