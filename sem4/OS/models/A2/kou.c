#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main(int argc,char *argv[]){
    if(argc>2){
        printf("Check args");
        exit(0);
    }
    int fd=open(argv[1],O_RDONLY);
    if(fd==-1){
        printf("File cannot be read");
        exit(0);
    }
    char character;
    int i=0,l=0;
    
    int shmid=shmget(123,sizeof(char**),IPC_CREAT|0666);
    
    int pid=fork();
    if(pid==0){
        
        
        sleep(2);
        char **content=(char**)shmat(shmid,NULL,0);
        for(int k=0;k<=l;k++){
            printf("%s\n",content[k]);
        }
        for(int j=1;j<l;j++){
            for(int k=0;k<(l-j);k++){
                if(strcmp(content[k+1],content[k])<0){
                    char s[100];
                    strcpy(s,content[k]);
                    strcpy(content[k],content[k+1]);
                    strcpy(content[k+1],s);
                }
            }
        }
        for(int k=0;k<=l;k++){
            printf("%s\n",content[k]);
        }
        shmdt(content);
    }
    else if(pid>0){
    
    char **content=(char**)shmat(shmid,NULL,0);
    content[l]=(char*)calloc(30, sizeof(char));
    while(read(fd,&character,sizeof(char))!=0){
            if(character!='\n'){
                content[l][i]=character;
                i++;
            }
            else{
                content[l][i]='\0';
                l++;
                i=0;
                content[l]=(char*)calloc(30, sizeof(char));
            }
        }
        
        for(int k=0;k<=l;k++)
            printf("%s\n",content[k]);
        wait(NULL); 
        shmdt(content);
}
shmctl(shmid,IPC_RMID,NULL);
}
