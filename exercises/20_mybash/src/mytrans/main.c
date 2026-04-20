#include "myhash.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: mytrans <file>\n");
    return 1;
  }

  return __cmd_mytrans(argv[1]);
}
