#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex;
pthread_cond_t cond  = PTHREAD_COND_INITIALIZER;
int condition = 0;

void *worker(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!condition) {
      pthread_cond_wait(&cond, &mutex);
    }
    printf("Hello from thread %d\n", counter++);
    pthread_mutex_unlock(&mutex);
}

int main()
{
  pthread_t t1;
  pthread_mutex_init(&mutex, 0);
  pthread_create(&t1, 0, &worker, 0);

  sleep(5);
  condition = 1;
  /* do something that might make condition true */
  pthread_cond_signal(&cond);
  while(1);
}