#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>
/*int strcmpi(char const *a, char const *b) //case insensitive comparision
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}*/

void display(char A[][20],int n) //display array
{
	for(int i=0; i<n; i++)
		printf("%s \n", A[i]);
}

/*void sort(char A[][20],int n) //sort the array
{
	char temp[30];
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-1-i; j++)
		{
			if(strcasecmp(A[j],A[j+1]) > 0)
			{
				strcpy(temp,A[j]);
       			strcpy(A[j],A[j+1]);
       			strcpy(A[j+1],temp);
      			}
    		}
  	}
  	display(A,n);
}*/
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


char ** ls(const char *dir)
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
	dirs[n++]=NULL;
	return dirs;
	
}
void lsR(char **dirs,int k)
{
	struct dirent *d;
	//int n=scandir(dir, &dirs, NULL, alphasort),i=-1;
	int i=0;
	DIR *dh;
	while(dirs[i])
	{
	dh=opendir(dirs[i]);
	if(!dh)
	{
		closedir(dh);
		i++;
		continue;
	}
	while(d=readdir(dh))
	{	
		if (d->d_type == DT_DIR) 
		{
			if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
				continue;
			!k?printf("\n."):printf("\n./%s",dirs[i]);
			printf("/%s:\n",d->d_name);
			char **dirs2=ls(d->d_name);
			lsR(dirs2,k+1);
		}
			
	}
	closedir(dh);
	i++;
	}
}
int main(int argc,char *arg[])
{
	if(argc==1)
	{
		printf(".:\n");
		char **dirs=ls(".");
		printf("\n%s\n",dirs[4]);
		lsR(dirs,0);
	}
	else 
	{
        	while( --argc ) 
        	{
             		printf( "%s:\n", * ++arg );
             		ls(*arg);
             		lsR(*arg,0);
         	}
         }
	return 0;	
}
