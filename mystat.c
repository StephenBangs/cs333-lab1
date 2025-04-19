//Stephen Bangs
//4/16/25
//CS333 - Jesse Chaney
//Lab 1 - Caesar Cipher, XOR Cipher, mystat()

//This is the mystat c code. Prints mostly the same thing as 
//given example code. Whitespace might be different, but luckily that diff -w flag 
//is coming through very kindly for us.

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
#include <limits.h>

//fn prototypes
//handles permissions
void print_permissions(mode_t mode);
//handles time (hopefully)
void print_time(const char *label, time_t time, int time_type);
//returns file type char
const char *file_type_string(mode_t mode);
//handles printing file info
void print_file_info(const char *filename);

int main(int argc, char *argv[]) {
	
	//testing why my local time zone is not working properly
	time_t now = time(NULL);
	fprintf(stderr, "System local time: %s", asctime(localtime(&now)));

	//TODO - remove
	for(int i = 1; i < argc; i++) {
		fprintf(stderr, "Arg %d: %s\n", i, argv[i]);
	}
	
	//print error message if no filename given
	if(argc < 2) {
		fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	//print file info for each argument sequentially
	for(int i = 1; i < argc; i++) {
		print_file_info(argv[i]);
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
	
	//print em all up
	printf("  Mode:                     %s        (%o in octal)\n", perms, mode & 0777);
}


void print_time(const char *label, time_t t, int time_type) {
	char local_buf[64];
	char gmt_buf[64];

	struct tm *local = localtime(&t);
	struct tm *gmt = gmtime(&t);
	
	switch(time_type) {
		case 0:
			printf("  %s:   %ld (seconds since the epoch)\n", label, t);
			break;
		case 1:

			strftime(local_buf, sizeof(local_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", local);
			printf("  %s:       %s (local)\n", label, local_buf);
			break;
		case 2:
			strftime(gmt_buf, sizeof(gmt_buf), "%Y-%m-%d %H:%M:%S %z (%Z) %a", gmt);
			printf("  %s:       %s (GMT)\n", label, gmt_buf);
			break;
		default:
			fprintf(stderr, "Error: no case for print_time\n");
			break;
	}

}


void print_file_info(const char *filename) {
	
	struct stat sb;
	char link_target[PATH_MAX];
	ssize_t len;

	const char *ftype;
	struct passwd *pw;
	struct group *gr;
	struct stat target_stat;

	if(lstat(filename, &sb) == -1) {
		perror(filename);
		return;
	}

	printf("File: %s\n", filename);

	ftype = file_type_string(sb.st_mode);
	printf("  File type:                %s", ftype);

	if(S_ISLNK(sb.st_mode)) {
		len = readlink(filename, link_target, sizeof(link_target) -1);
		if (len != -1) {
			link_target[len] = '\0';
			printf(" -> %s", link_target);

			if (stat(filename, &target_stat) == -1) {
				printf(" - with dangling destination");
			}
		}
		else {
			printf(" -unreadable symlink");
		}
	}
	printf("\n  Device ID number:         %ld\n", (long) sb.st_dev);
	printf("  I-node number:            %ld\n", (long) sb.st_ino);
	print_permissions(sb.st_mode);
	printf("  Link count:               %ld\n", (long) sb.st_nlink);

	pw = getpwuid(sb.st_uid);
	gr = getgrgid(sb.st_gid);

	printf("  Owner Id:                 %s           (UID = %d)\n", pw ? pw->pw_name : "???", sb.st_uid);
	printf("  Group Id:                 %s              (GID = %d)\n", gr ? gr->gr_name : "???", sb.st_gid);

	printf("  Preferred I/O block size: %ld bytes\n", (long) sb.st_blksize);
	printf("  File size:                %ld bytes\n", (long) sb.st_size);
	printf("  Blocks allocated:         %ld\n", (long) sb.st_blocks);

	print_time("Last file access", sb.st_atime, 0);
	print_time("Last file modification", sb.st_mtime, 0);
	print_time("Last status change", sb.st_ctime, 0);

	print_time("Last file access", sb.st_atime, 1);
	print_time("Last file modification", sb.st_mtime, 1);
	print_time("Last status change", sb.st_ctime, 1);

	print_time("Last file access", sb.st_atime, 2);
	print_time("Last file modification", sb.st_mtime, 2);
	print_time("Last status change", sb.st_ctime, 2);
	printf("\n");

}

const char *file_type_string(mode_t mode) {

	if (S_ISREG(mode)) return "regular file";
	if (S_ISDIR(mode)) return "directory";
	if (S_ISLNK(mode)) return "Symbolic link";
	if (S_ISCHR(mode)) return "character device";
	if (S_ISBLK(mode)) return "block device";
	if (S_ISFIFO(mode)) return "FIFO/pipe";
	if (S_ISSOCK(mode)) return "socket";
	return "unknown";

}
