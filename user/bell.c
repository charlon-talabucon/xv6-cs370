#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // test loop to check if ticks was working
  // volatile int i;
  //for(i = 0; i < 1000000000000000; i++);

  //printf("HI Ticks : %d\n", tickshi());
  //printf("LO Ticks : %d\n", tickslo());
  //exit(0);

  //error messages
  if(argc != 2){
    printf("Error, too many inputs\n");
    exit(1);
  }

  //text to integer
  int limit = atoi(argv[1]);

  if(limit <1) {
    printf("Error, limit should be >= 1\n");
    exit(1);
  }
  
  //stores previous row of bell triangle
  int previous[100];
  //stores new row
  int current[100];

  //first row will always be a single value of 1
  int prevLen = 1;
  previous[0] = 1;

  while(1){
    //print current row
    for(int i = 0; i< prevLen; i++) {
      //prints the number at position i
      printf("%d", previous[i]);
      //prints a space
      if(i < prevLen - 1)
        printf(" ");
    }
    printf("\n");

    // first value of the next row is last value of previous row
    int nextFirstVal = previous[prevLen - 1];
    // stop if row begins with value greater than limit
    if (nextFirstVal > limit)
      break;

    // new row should be one more element bigger than previous row
    int currentLen = prevLen + 1;
    //first value is last value of previous row
    current[0] = nextFirstVal;
    //rest of row
    for(int i = 1; i < currentLen; i++) {
      current[i] = current[i - 1] + previous[i - 1];
    }

    //the new row becomes the previous row for the next iteration
    for(int i = 0; i < currentLen; i++) {
      previous[i] = current[i];
    }
    prevLen = currentLen;

  }
  printf("HI ticks: %d\n", tickshi());
  printf("LO ticks: %d\n", tickslo());

  exit(0);
}