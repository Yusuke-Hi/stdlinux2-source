#include <stdio.h>
#include <stdlib.h>

static void do_head(FILE* f, long nlines);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s n [filr filr ...]\n", argv[0]);
    exit(1);
  }

  if (argc == 2) {
    do_head(stdin, atol(argv[1]));
  } else {
    for (int i = 2; i < argc; i++) {
      FILE* f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_head(f, atol(argv[1]));
      fclose(f);
    }
  }
}

static void do_head(FILE* f, long nlines) {
  int c;
  while ((c = getc(f)) != EOF) {
    if (putchar(c) < 0) exit(1);
    if (c == '\n') {
      nlines--;
      if (nlines == 0) break;
    }
  }
}
