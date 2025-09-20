#include <stdio.h> 
#include <stdlib.h>

// Cấu trúc để biểu diễn một tiến trình
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
} Process;

void find_waiting_time(Process proc[], int n, int quantum) {
    int time = 0;
    int i;
    int *queue = (int*) malloc(n * sizeof(int));
    int front = 0, rear = 0;
    int completed = 0;

    for (i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }

    queue[rear++] = 0;
    proc[0].waiting_time = 0;

    while (completed != n) {
        int current_proc_idx = queue[front++];
        int execution_time = (proc[current_proc_idx].remaining_time > quantum) ? quantum : proc[current_proc_idx].remaining_time;
        time += execution_time;

        proc[current_proc_idx].remaining_time -= execution_time;

        // Thêm các tiến trình mới đến vào hàng đợi
        for (i = 0; i < n; i++) {
            if (proc[i].arrival_time <= time && i != current_proc_idx) {
                // Kiểm tra xem tiến trình đã ở trong hàng đợi chưa
                int in_queue = 0;
                for (int j = 0; j < rear; j++) {
                    if (queue[j] == i) {
                        in_queue = 1;
                        break;
                    }
                }
                if (!in_queue) {
                    queue[rear++] = i;
                }
            }
        }
        
        if (proc[current_proc_idx].remaining_time > 0) {
            queue[rear++] = current_proc_idx;
        } else {
            completed++;
            proc[current_proc_idx].completion_time = time;
        }
    }
    
    free(queue);
}

void find_turnaround_time(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

void find_average_times(Process proc[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    
    find_waiting_time(proc, n, 2); // Giả sử quantum = 2
    find_turnaround_time(proc, n);

    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
    
    printf("\nAverage Waiting Time = %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    Process proc[] = {{1, 0, 10, 0, 0, 0, 0}, {2, 0, 5, 0, 0, 0, 0}, {3, 0, 8, 0, 0, 0, 0}};
    printf("\nRound robin simulation\n");
    int n = sizeof(proc) / sizeof(proc[0]);
    int quantum = 2; // Ví dụ quantum = 2
    
    find_average_times(proc, n);

    return 0;
}
