#include <stdio.h> 
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock;

void* thread_function(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        //Bỏ dòng dưới để thử
        pthread_mutex_lock(&lock);
        counter++;
        //Bỏ dòng dưới để thử
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Giá trị cuối cùng của counter là: %d\n", counter);

    return 0;
}

