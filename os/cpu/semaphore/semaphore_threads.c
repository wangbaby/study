#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t mutex;

void thread() {
  // wait
  sem_wait(&mutex);
  printf("\nEntered..\n");

  // critical section
  sleep(4);

  // signal
  printf("\nJust Exiting...\n");
  sem_post(&mutex);
}

int main() {
  if (sem_init(&mutex, 0, 1) != 0) perror("sem_init failed");

  pthread_t t1, t2;

  pthread_create(&t1, NULL, thread, NULL);
  sleep(2);

  pthread_create(&t2, NULL, thread, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  if (sem_destroy(&mutex) != 0) perror("sem_destory failed");

  return 0;
}
