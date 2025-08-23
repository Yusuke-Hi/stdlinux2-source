#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 2048

static void do_wc(const char* path);
static void die(const char* err_msg);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: This command need some arguments\n", argv[0]);
    exit(1);
  }
  for (int i = 1; i < argc; i++) {
    do_wc(argv[i]);
  }
  exit(0);
}

static void do_wc(const char* path) {
  int fd = open(path, O_RDONLY);
  if (fd < 0) die(path);

  unsigned char buf[BUFF_SIZE];

  int lines = 0;
  while (1) {
    int n = read(fd, buf, sizeof(buf));
    if (n < 0) die(path);
    if (n == 0) break;
    for (int i = 0; i < n; i++) {
      if (buf[i] == '\n') lines++;
    }
  }

  char str_lines[20];
  sprintf(str_lines, "%d\n", lines);

  if (write(STDOUT_FILENO, str_lines, strlen(str_lines)) < 0) die(path);
  if (close(fd) < 0) die(path);
}

static void die(const char* err_msg) {
  perror(err_msg);
  exit(1);
}
