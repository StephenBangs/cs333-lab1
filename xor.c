//Stephen Bangs
//4/16/25
//CS333 - Jesse Chaney
//Lab 1 - Caesar Cipher, XOR Cipher, mystat()

//This is the XOR cipher c code.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define OPTIONS "k:"
#define DEFAULT_KEY "Xerographic"
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {

	char *key = DEFAULT_KEY;
	size_t key_len = strlen(key);

	unsigned char buffer[BUF_SIZE];
	ssize_t bytes_read;
	size_t key_index = 0;
	int opt = 0;

	while((opt = getopt(argc, argv, OPTIONS)) != -1) {
		switch (opt) {
			case 'k':
				fprintf(stderr, "\ncase k");
				if(optarg == NULL || strlen(optarg) == 0) {
					fprintf(stderr, "Please enter a key.");
					exit(EXIT_FAILURE);
				}
				key = optarg;
				key_len = strlen(key);
				break;
			default:
				fprintf(stderr, "\ncase default");
				break;
		}
	}
	


	while((bytes_read = read(STDIN_FILENO, buffer, BUF_SIZE)) > 0) {
		for(ssize_t i = 0; i < bytes_read; i++) {
			buffer[i] ^= key[key_index];
			key_index = (key_index + 1) % key_len;
		}

		if(write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
			perror("write");
			exit(EXIT_FAILURE);
		}
	}

	if(bytes_read < 0) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;

}
