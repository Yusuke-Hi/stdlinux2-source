#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    FILE* f = fopen(argv[i], "r");
    if (!f) {
      perror(argv[i]);
      exit(1);
    }

    int c;
    while ((c = fgetc(f)) != EOF) {
      if (c == '\t') {
        if (fputs("\\t", stdout) == EOF) exit(1);
      }

      else if (c == '\n') {
        if (fputs("$\n", stdout) == EOF) exit(1);
      }

      else {
        if (putchar(c) < 0) exit(1);
      }
    }

    fclose(f);
  }

  exit(0);
}