#include <stdlib.h>
#include <stdio.h>
#include "data.h"

#ifdef _WIN32
#include <process.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

int compile_file(const char *filename){
#ifdef _WIN32
    const char *output = GENERATED_DIRECTORY "/out.exe";
    const char *argv[] = {"gcc", filename, "-o", output, NULL};
    int result = _spawnvp(_P_WAIT, "gcc", argv);
    if (result == -1) {
        perror("Failed to start gcc");
        return 1;
    }
#else
    const char *output = GENERATED_DIRECTORY "/out";

    pid_t pid = fork();
    if (pid == -1) {
        perror("Failed to start gcc");
        return 1;
    }
    if (pid == 0) {
        execlp("gcc", "gcc", filename, "-o", output, (char *)NULL);
        perror("Failed to execute gcc");
        _exit(127);
    }
    int result = 1;
    if (waitpid(pid, &result, 0) == -1) {
        perror("Failed to wait for gcc");
        return 1;
    }
    if (WIFEXITED(result)) {
        result = WEXITSTATUS(result);
    } else {
        result = 1;
    }
#endif

    if (result == 0) {
        printf("Compilation successful. Executable created as '%s'.\n", output);
        return 0;
    } else {
        printf("Compilation failed.\n");
        return 1;
    }
}


