#include "mywc.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: mywc <file>\n");
    return 1;
  }

  return __cmd_mywc(argv[1]);
}
