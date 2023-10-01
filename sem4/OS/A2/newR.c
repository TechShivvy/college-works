#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>
#include <errno.h>
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
char ** ls( char *dir)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	if(!dh)
	{
		closedir(dh);
		return NULL;
	}
	
	char **dirs=(char**)calloc(200, sizeof(char*));
	int n=0;
	while(d=readdir(dh))
	{
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
                	continue;
               dirs[n]=(char*)calloc(30, sizeof(char)); 
		strcpy(dirs[n++],d->d_name);
			
	}
	closedir(dh);
	sort(dirs,n);
	for(int i=0;i<n;i++)
		printf("%s \n",dirs[i]);
	return dirs;
}
void lsR(char *dir,int k, char **fil)
{
	struct dirent *d;
	int i=0;
	char path[1000];
	while(fil[i])
	{
		/*strcpy(path,dir);
		strcat(path,"/");
		strcat(path,fil[i]);*/
		//DIR *dh=opendir(fil[i]);
		//if(!dh)
		//{
		//	closedir(dh);
		//	i++;
		//	continue;
		//	return;
		//}
		//d=readdir(dh);
		struct stat sb;
		strcpy(path,dir);
		strcat(path,"/");
		strcat(path,fil[i]);
		if(lstat(path,&sb)==-1)
			;
		if(S_ISDIR(sb.st_mode))
		{	
			//if (d->d_type == DT_DIR) 
			{
				//if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
				//	continue;
				!k?printf("\n."):printf("\n%s",dir);
				printf("/%s:\n",fil[i]);
				//strcpy(path,dir);
				//strcat(path,"/");
				//strcat(path,d->d_name);
				char **fil2=ls(path);
				lsR(path,k+1,fil2);
			}
				
		}
		i++;
		//closedir(dh);
	}
}
int main(int argc,char *arg[])
{
	if(argc==1)
	{
		printf(".:\n");
		char **fil=ls(".");
		int i=0;
		//while(fil[i])
		//	printf("%s \n",fil[i++]);
		//printf("%d",i);
		lsR(".",0,fil);
	}
	else 
	{
        	while( --argc ) 
        	{
             		printf("%s:\n", * ++arg );
             		char **fil=ls(*arg);
		int i=0;
             		lsR(*arg,1,fil);
         	}
         }
	return 0;
	
}
