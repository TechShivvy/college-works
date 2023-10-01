#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<ctype.h>
int strcmpi(char const *a, char const *b) //case insensitive comparision
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
}

void display(char A[][20],int n) //display array
{
	for(int i=0; i<n; i++)
		printf("%s \n", A[i]);
}

void sort(char A[][20],int n) //sort the array
{
	char temp[30];
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-1-i; j++)
		{
			if(strcmpi(A[j],A[j+1]) > 0)
			{
				strcpy(temp,A[j]);
       			strcpy(A[j],A[j+1]);
       			strcpy(A[j+1],temp);
      			}
    		}
  	}
  	display(A,n);
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
	char dirs[100][20];
	int n=0;
	while(d=readdir(dh))
	{
		strcpy(dirs[n++],d->d_name);
			
	}
	closedir(dh);
	sort(dirs,n);
}
int main(int argc,char *arg[])
{
	ls(".");
	
}
