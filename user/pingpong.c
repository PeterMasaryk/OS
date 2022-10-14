#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(int argc, char *argv[])
{
  if(argc != 1){
    printf("usage: ping pong NOARGS, send bit between pipes");
    exit(0);
  }

  int parent_pipe [2];
  int child_pipe [2];
  int buf[1];
  pipe(parent_pipe);
  pipe(child_pipe);

  int pid = fork();
  if(pid>0){
  // i am the parent
   write(child_pipe[1], "", 1);
   wait(0);
   close(child_pipe[1]);
   read(parent_pipe[0], buf, 1);
   printf("%d: received pong\n", getpid());
   close(parent_pipe[0]);
  }else if(pid == 0){
   read(child_pipe[0], buf, 1);
   printf("%d: received ping\n", getpid());
   write(parent_pipe[1], "", 1);
   close(child_pipe[0]);
   close(parent_pipe[1]);
   exit(0);

  }else{
   printf("fork error\n");
   exit(0);
  }

  exit(0);
}
