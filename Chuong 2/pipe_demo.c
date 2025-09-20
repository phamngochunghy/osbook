#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    const char *message = "Hello from parent!";

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Tiến trình con
        close(pipefd[1]);
        printf("Tiến trình con đang chờ dữ liệu...\n");
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Tiến trình con nhận được: %s\n", buffer);
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {
        // Tiến trình cha
        close(pipefd[0]);
        printf("Tiến trình cha đang gửi dữ liệu...\n");
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
        printf("Tiến trình cha đã gửi xong và kết thúc.\n");
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
