#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_STRING_LENGTH 100

int isPalindrome(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1])
            return 0; // Not a palindrome
    }
    return 1; // Palindrome
}

int main() {
    int n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);
    fflush(stdin); // Clear input buffer

    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child Process
        close(pipefd[1]); // Close the write end of the pipe

        char received_string[MAX_STRING_LENGTH];
        int palindrome_count = 0;

        printf("Child process:\n");
        printf("Palindromes received:\n");

        while (read(pipefd[0], received_string, MAX_STRING_LENGTH) > 0) {
            if (isPalindrome(received_string)) {
                printf("%s\n", received_string);
                palindrome_count++;
            }
        }

        printf("Total palindromes received: %d\n", palindrome_count);
        close(pipefd[0]); // Close the read end of the pipe
        exit(EXIT_SUCCESS);
    } else { // Parent Process
        close(pipefd[0]); // Close the read end of the pipe

        printf("Parent process:\n");
        printf("Enter %d strings:\n", n);

        char input_string[MAX_STRING_LENGTH];

        for (int i = 0; i < n; i++) {
            scanf("%s", input_string);
            write(pipefd[1], input_string, strlen(input_string) + 1);
        }

        close(pipefd[1]); // Close the write end of the pipe
        waitpid(pid, NULL, 0); // Wait for child process to finish
        exit(EXIT_SUCCESS);
    }

    return 0;
}
