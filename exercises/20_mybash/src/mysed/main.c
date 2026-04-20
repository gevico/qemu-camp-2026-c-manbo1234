#include "mysed.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: mysed <rule> <string>\n");
    return 1;
  }

  return __cmd_mysed(argv[1], argv[2]);
}
