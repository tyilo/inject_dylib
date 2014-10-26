#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <mach/mach.h>

#include "rd_inject_library/rd_inject_library.h"

int main(int argc, const char *argv[]) {
	if(argc != 3) {
		printf("Usage: %s pid lib\n", argv[0]);
		return 1;
	}
	
	pid_t pid = atoi(argv[1]);
	const char *lib = argv[2];
	
	char path[MAXPATHLEN];
	if(!realpath(lib, path)) {
		puts("Couldn't get absolute path to lib.");
		return -1;
	}
	
	int ret = rd_inject_library(pid, path);
	switch(ret) {
		case KERN_SUCCESS:
			puts("Inserted lib sucessfully.");
			break;
		case KERN_INVALID_OBJECT:
			puts("dlopen call in target failed.");
			break;
		case KERN_FAILURE:
			puts("Failed to inject into target.");
			break; 
	}

	return ret;
}
