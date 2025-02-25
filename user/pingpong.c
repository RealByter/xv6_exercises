#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p[2];

  pipe(p);
  if (fork() == 0) {
    int id = getpid();
    char buf[4] = {0};

    read(p[0], buf, 4);
    close(p[0]);
    printf("%d: received %s\n", id, buf);

    write(p[1], "pong", 4);
    close(p[1]);
  } else {
    int id = getpid();
    char buf[4] = {0};

    write(p[1], "ping", 4);
    close(p[1]);

    read(p[0], buf, 4);
    close(p[0]);
    printf("%d: received %s\n", id, buf);
  }

  exit(0);
}
