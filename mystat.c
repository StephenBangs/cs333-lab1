
//Stephen Bangs
//4/16/25
//CS333 - Jesse Chaney
//Lab 1 - Caesar Cipher, XOR Cipher, mystat()

//This is the mystat c code.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>

void print_permissions(mode_t mode);
void print_time(const char *label, time_t time);


int main(int argc, char *argv[]) {

	for(int i = 1; i < argc; i++) {
		printf("Arg %d: %s\n", i, argv[i]);
	}

	return EXIT_SUCCESS;

}

//printing file permissions
void print_permissions(mode_t mode) {
	char perms[11] = "---------";

	//file types display
	if(S_ISDIR(mode)) perms[0] = 'd';	
	else if (S_ISCHR(mode)) perms[0] = 'c'; 
	else if (S_ISBLK(mode)) perms[0] = 'b';
	else if (S_ISFIFO(mode)) perms[0] = 'p';
	else if (S_ISLNK(mode)) perms[0] = 'l';
	else if (S_ISSOCK(mode)) perms[0] = 's';

	//owner of the file
	if(mode & S_IRUSR) perms[1] = 'r';
	if(mode & S_IWUSR) perms[2] = 'w';
	if(mode & S_IXUSR) perms[3] = 'x';

	//group access to file
	if(mode & S_IRGRP) perms[4] = 'r';
	if(mode & S_IWGRP) perms[5] = 'w';
	if(mode & S_IXGRP) perms[6] = 'x';

	//other access to file
	if(mode & S_IROTH) perms[7] = 'r';
	if(mode & S_IWOTH) perms[8] = 'w';
	if(mode & S_IXOTH) perms[9] = 'x';

	printf("  Mode:                 %s       (%o in octal)\n", perms, mode & 0777);
}

void print_time(const char *label, time_t t) {
	char local_buf[64];
	char gmt_buf[64];

	struct tm *local = localtime(&t);
	struct tm *gmt = gmtime(&t);
	
	strftime(local_buf, sizeof(local_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", local);
	strftime(gmt_buf, sizeof(gmt_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", gmt);

	printf("  %s:    %ld (seconds since the epoch)\n", label, t);
	printf("  %s:    %s (local)\n", label, local_buf);
	printf("  %s:    %s (GMT)\n", label, gmt_buf);

}
