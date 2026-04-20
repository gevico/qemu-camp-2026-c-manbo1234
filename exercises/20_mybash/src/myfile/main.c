#include "myfile.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: myfile <file>\n");
    return 1;
  }

  return __cmd_myfile(argv[1]);
}
