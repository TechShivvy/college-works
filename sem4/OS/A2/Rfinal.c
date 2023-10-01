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
#include<errno.h>
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
		//printf("ls: cannot access '%s': No such file or directory\n",dir);
		
		switch (errno)
		{
			case EACCES:  printf("ls: cannot access '%s': Permission denied\n",dir); 
				      break;
		    	case ENOENT:  printf("ls: cannot access '%s': No such file or directory\n",dir); 
		    		      break;
		    	//case ENOTDIR: printf("'%s' is not a directory\n", dir);
		    	
		    	//	      break;
		}
		char **dirs=(char**)calloc(200, sizeof(char*));
		int n=0;
		dirs[n]=(char*)calloc(30, sizeof(char)); 
		strcpy(dirs[n++],"NULL");
		closedir(dh);
		return dirs;
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
void lsR(char *dir, char **fil)
{
	struct dirent *d;
	int i=0;
	char path[1000];
	while(fil[i])
	{
		struct stat sb;
		strcpy(path,dir);
		strcat(path,"/");
		strcat(path,fil[i]);
		if(lstat(path,&sb)==-1)
			;
		if(S_ISDIR(sb.st_mode))
		{	 
			printf("\n%s:\n",path);
			char **fil2=ls(path);
			lsR(path,fil2);
		}
		i++;
	}
}
int main(int argc,char *arg[])
{
	char **fil;
	if(argc==1)
	{
		printf(".:\n");
		fil=ls(".");
		lsR(".",fil);
	}
	else 
	{
        	while(--argc) 
        	{
             		printf("%s:\n", * ++arg );
             		fil=ls(*arg);
             		if(strcmp(fil[0],"NULL"))
             			lsR(*arg,fil);
             		printf("%s",(argc-1?"\n":""));
         	}
         }
	return 0;	
}
