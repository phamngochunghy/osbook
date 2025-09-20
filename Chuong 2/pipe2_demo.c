#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1
#define MAX_SIZE 100

int main() {
    int pipe1[2]; // Cha -> Con
    int pipe2[2]; // Con -> Cha
    pid_t pid;
    char buffer[MAX_SIZE];
    const char *message = "hello from parent";

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Tiến trình con
        close(pipe1[WRITE_END]); // Đóng đầu ghi pipe 1
        close(pipe2[READ_END]);  // Đóng đầu đọc pipe 2

        // Con đọc từ pipe 1
        read(pipe1[READ_END], buffer, MAX_SIZE);
        printf("Con: nhận được '%s' từ cha\n", buffer);

        // Chuyển chuỗi thành chữ hoa
        for (int i = 0; i < strlen(buffer); i++) {
            buffer[i] = toupper(buffer[i]);
        }

        // Con ghi vào pipe 2
        write(pipe2[WRITE_END], buffer, strlen(buffer) + 1);
        printf("Con: đã gửi '%s' cho cha\n", buffer);

        close(pipe1[READ_END]);
        close(pipe2[WRITE_END]);
        exit(EXIT_SUCCESS);
    } else {
        // Tiến trình cha
        close(pipe1[READ_END]);  // Đóng đầu đọc pipe 1
        close(pipe2[WRITE_END]); // Đóng đầu ghi pipe 2

        // Cha ghi vào pipe 1
        write(pipe1[WRITE_END], message, strlen(message) + 1);
        printf("Cha: đã gửi '%s' cho con\n", message);
        close(pipe1[WRITE_END]);

        // Cha đọc từ pipe 2
        read(pipe2[READ_END], buffer, MAX_SIZE);
        printf("Cha: nhận được '%s' từ con\n", buffer);

        close(pipe2[READ_END]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}