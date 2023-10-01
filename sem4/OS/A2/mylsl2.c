#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
#include<fcntl.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>
void printsrc(char A[],int n)
{
	if(A[n]=='/')
		return;
	printsrc(A,n-1);
	printf("%c",A[n]);
}

void sort(char** A, int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(strcasecmp(A[j],A[j+1])>0)
			{
				char* temp;
				temp=(char*)calloc(30, sizeof(char));
				strcpy(temp,A[j]);
				strcpy(A[j],A[j+1]);
				strcpy(A[j+1],temp);
			}
		}	
	}
}
void ls(const char *dir)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	if(!dh)
	{
		//printf("Dir Error!\n");
		closedir(dh);
		return;
	}
	char **dirs=(char**)calloc(200, sizeof(char*));
	int n=0;
	while(d=readdir(dh))
	{
		if(strcmp(d->d_name,".")==0||strcmp(d->d_name,"..")==0)   // only for ls -a . , ..
                	continue;
		dirs[n]=(char*)calloc(30, sizeof(char));
		strcpy(dirs[n++],d->d_name);
	}
	closedir(dh);
	sort(dirs,n);
		struct stat sb;
		int total=0;
		for(int i=0; i<n; i++)
		{
			if(lstat(dirs[i],&sb)==-1)
			{
				printf("ERRRORRR\n");
				exit(0);
			}
			total+=sb.st_blocks;
		}
		printf("total %d\n",total/2);
		
		char *args[10];
		args[0]="stat";
    		args[1]="--format";
    		args[2]="%A %h %U %G%6s %.16y %N ";
    		for(int j=0;j<n;j++)
    		{
    			args[j+3]=dirs[j];
    		}
    		args[n+3]=NULL;
    		execvp("stat",args);
	
}
int main(int argc,char *arg[])
{
	if(argc==1)
	{
		printf(".:\n");
		ls(".");
	}
	else 
	{
        	while( --argc ) 
        	{
             		printf( "%s:\n", * ++arg );
             		ls(*arg);
         	}
         }
	return 0;
	
}

