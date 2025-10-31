#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        printf("ERROR: No arguments");
        return 1;
    }

    if (argc != 3) {
        printf("USAGE: partc <word> <file>");
        return 1;
    }

    const char* word = argv[1];
    const char* file_path = argv[2];

    pid_t child = fork();

    if (child < 0) {
        perror("fork");
        return 1;
    }

    if (child == 0) {
        const char* grep_args[] = { "grep", "-s", "-q", word, file_path, NULL };
        execv("/usr/bin/grep", (char* const*)grep_args);
        perror("execv");
        _exit(1);
    }

    int status = 0;

    if (waitpid(child, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    if (!WIFEXITED(status)) {
        printf("ERROR: Child process terminated unexpectedly");
        return 1;
    }

    int child_status = WEXITSTATUS(status);

    if (child_status == 0) {
        printf("FOUND: %s", word);
        return 0;
    }

    if (child_status == 1) {
        printf("NOT FOUND: %s", word);
        return 0;
    }

    if (child_status == 2) {
        printf("ERROR: %s doesn't exist", file_path);
        return 2;
    }

    printf("ERROR: grep exit status %d", child_status);
    return child_status;
}
