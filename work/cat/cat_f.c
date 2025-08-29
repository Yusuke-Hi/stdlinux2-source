#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 2048

static void do_cat(const char* path);
static void die(const char* s);

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    do_cat(argv[i]);
  }
  exit(0);
}

static void do_cat(const char* path) {
  unsigned char buf[BUFF_SIZE];

  FILE* f = fopen(path, "r");
  if (!f) die(path);

  while (1) {
    size_t n_read = fread(buf, 1, sizeof(buf), f);
    if (ferror(f)) die(path);

    size_t n_write = fwrite(buf, 1, n_read, stdout);
    if (n_write < n_read) die(path);

    if (n_read < sizeof(buf)) break;
  }
  if (fclose(f) != 0) die(path);
}

static void die(const char* s) {
  perror(s);
  exit(1);
}
