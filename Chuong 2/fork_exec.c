#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Tiến trình cha đang chạy với PID: %d\n", getpid());
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Tiến trình con
        printf("Tiến trình con đang chạy với PID: %d\n", getpid());
        printf("Tiến trình con sẽ thực thi lệnh 'ls -l'...\n");
        execlp("/bin/ls", "ls", "-l", (char *) NULL);
        
        // Đoạn code này sẽ chỉ được thực thi nếu execlp thất bại
        perror("execlp"); 
        exit(EXIT_FAILURE);
    } else {
        // Tiến trình cha
        wait(NULL); 
        printf("Tiến trình cha đã chờ con kết thúc.\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}
