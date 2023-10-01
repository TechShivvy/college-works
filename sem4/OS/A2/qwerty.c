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
void printsrc(char A[],int n)
{
	if(A[n]=='/')
		return;
	printsrc(A,n-1);
	printf("%c",A[n]);
}
void display(char A[][20],int n) //display array
{
	for(int i=0; i<n; i++)
		printf("%s \n", A[i]);
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
}
*/
/*void ls(const char *dir)
{
	struct dirent *d;
	DIR *dh=opendir(dir);
	if(!dh)
	{
		closedir(dh);
		return;
	}
	
	char dirs[100][20];
	int n=0;
	while(d=readdir(dh))
	{
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
                	continue;
		strcpy(dirs[n++],d->d_name);
			
	}
	closedir(dh);
	sort(dirs,n);
}*/
void lsR(const char *dir,int k)
{

	struct dirent *d;
	char path[1000];
	DIR *dh2=opendir(dir);
	if(!dh2)
	{
		closedir(dh2);
		return;
	}
	char **dirs=(char**)calloc(200, sizeof(char*));
	int n=0;
	//char dirs[100][20];
	//int n=0;
	while(d=readdir(dh2))
	{
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
                	continue;
                dirs[n]=(char*)calloc(30, sizeof(char));
                strcpy(path, dir);
          	strcat(path, "/");
           	strcat(path, d->d_name);
		strcpy(dirs[n++],path);
		//strcpy(dirs[n++],d->d_name);
			
	}
	closedir(dh2);
	sort(dirs,n);
	for(int i=0;i<n;i++)
	{printsrc(dirs[i],strlen(dirs[i]));
	printf("\n");}
	{
	//printf("%s \n",dirs[i]);
	}
	int i=0;
	while(i<n)
	{
	//printf("\nHAHHA: %s\n",dirs[i]);
	char path[1000];
	DIR *dh=opendir(dirs[i]);
	if(!dh)
	{
		printf("\nHAHHA: %s\n",dirs[i]);
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
			//path=(char*)calloc(200, sizeof(char));
			//path="\0";
			strcpy(path, dirs[i]);
          		strcat(path, "/");
           		strcat(path, d->d_name);
           		printf("\npath:%s\n",path);
			//ls(path);
			lsR(path,k+1);
			//ls(d->d_name);
			//lsR(d->d_name,k+1);
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
		//ls(".");
		lsR(".",0);
	}
	else 
	{
        	while( --argc ) 
        	{
             		printf( "%s:\n", * ++arg );
             		//ls(*arg);
             		lsR(*arg,0);
         	}
         }
	return 0;
	
}
