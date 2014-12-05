#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <mach/mach.h>

#include "task_vaccine/task_vaccine.h"

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

	task_t task;
	kern_return_t ret = task_for_pid(mach_task_self(), pid, &task);
	if(ret != KERN_SUCCESS) {
		printf("task_for_pid() failed: %s\n", mach_error_string(ret));
		return ret;
	}

	ret = task_vaccine(task, path);
	switch(ret) {
		case KERN_SUCCESS:
			puts("Injected lib sucessfully.");
			break;
		case KERN_INVALID_TASK:
			puts("dlopen() call in target failed.");
			break;
		case KERN_FAILURE:
			puts("Failed to inject into target.");
			break;
	}

	return ret;
}
