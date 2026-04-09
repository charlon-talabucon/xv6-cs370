#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define PREADY 0xBEEF
#define CREADY 0xDEAD

int main(int argc, char** argv) {
  int pid = fork();
  void *shared = 0;
  volatile int *value, *ready;
  if (!pid) {
    /* In child */
    shared = spage();
    ready = (int *)shared;
    value = ready + 1;

    /* Spin waiting for the parent to communicate */
    while (*ready != PREADY) { /* wait */ }
    printf("Parent PID is: %d\n", *value);

    /* Multiply the parent's pid by this processes pid */
    *value = *value * getpid();
    *ready = CREADY;
    
  } else {
    /* In parent */
    shared = spage();

    /* Place the parent pid in the shared region */
    ready = (int *)shared;
    value = ready + 1;
    *value = getpid();
    *ready = PREADY;

    /* Wait for the child to be ready */
    while (*ready != CREADY) { /* wait */ }
    printf("Child sent: %d\n", *value);
  }
}
