#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
const int MAXARGS=20;
const int ARGLEN=100;

char * makestring(char *buf){
    char *ans=malloc(strlen(buf)+1);
    char *tmpbuf=malloc(strlen(buf)+1);
     strcpy(tmpbuf,buf);
    int i=0;
    tmpbuf[strlen(buf)-1]='\0';
    while(tmpbuf[i]!=' '&&i<strlen(tmpbuf))i++;
    tmpbuf[i]='\0';
     strcpy(ans,tmpbuf);
     return ans;
}
int execute(char *arglist[]){
    int pid,exitstatus;
    pid= fork();
    if(pid==0){
       execvp(arglist[0], arglist);
       exit(1);
    }else{
        while(wait(&exitstatus)!=pid);
    }
    return 1;
}
int main(){
    char *arglist[MAXARGS+1];
    char argbuf[ARGLEN];
    int index;
    char bufcwd[80];
    char bufhostname[80];
    char bufusername[80];
    int i=0;
    for(;;){
    gethostname(bufhostname,sizeof(bufhostname));
    strcpy(bufusername,getpwuid(getuid())->pw_name);
    getcwd(bufcwd, sizeof(bufcwd));
    printf("%s@%s:%s>",bufusername,bufhostname,bufcwd);
    fgets(argbuf, ARGLEN, stdin);
        for(i=0;i<strlen(argbuf);i++){
            if(i==0||argbuf[i-1]==' ')
            arglist[index++] = makestring(argbuf+i);
        }
            if( index > 0 ){
                arglist[index] = NULL;
                execute(arglist);
                index = 0;
            }
        }
}

