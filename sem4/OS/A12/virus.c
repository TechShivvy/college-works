#include<stdio.h>
#include<string.h>
struct file{
	char name[100];
	char path[100];
};

struct directory{
	char name[100];
	struct file FILE[100];
	int no_of_files;
};

struct master_dir{
	char name[100];
	struct directory DIR[100];
};

void single_level()
{
	int choice;
	struct file FILE[100];
	int no_of_files=0; 
	int address=1000;
	printf("\n\n------Single Level Directory------\n");
	printf("1.Create file\n2.List the files\n3.Exit\n");
	printf("Enter option:");
	scanf("%d",&choice);
	
	while(choice>=1 && choice<=2)
	{
		if(choice==1)
		{
			char temp[100];
			printf("Enter the name of the file:");
			scanf("\n");
			scanf("%[^\n]",temp);
			
			int flag=0;
			for(int i=0;i<no_of_files;i++)
			{
				if(strcmp(FILE[i].name,temp)==0)
				{
					printf("File already exists");
					strcat(temp,"(1)");
					flag=1;
				}
			}
			
			
		
			strcpy(FILE[no_of_files].name,temp);
			strcpy(FILE[no_of_files].path,"/usr1/");
			no_of_files++;
			
			if(flag==0)
				printf("\nFile added\n");
		}
		if(choice==2)
		{
			printf("\n\n%s%20s\n","File Name","Path");
			for(int i=0;i<no_of_files;i++)
			{
				printf("%s%24s\n",FILE[i].name,FILE[i].path);
			}
		}	
		
		printf("\n\n1.Create file\n2.List the files\n3.Exit\n");
		printf("Enter option:");
		scanf("%d",&choice);	
		
		
			
	}
	return ;
	
}

void two_level()
{
	printf("\n\n------Two Level Directory------\n");
	
	int no_of_user,choice;
	printf("Enter number of user:");
	scanf("%d",&no_of_user);
	
	struct master_dir mDIR;
	strcpy(mDIR.name,"/");
	
	printf("\nEnter directory names:\n");
	for(int i=0;i<no_of_user;i++)
	{
		char temp[100];
		scanf("\n");
		scanf("%[^\n]",temp);
		strcpy(mDIR.DIR[i].name,temp);
		mDIR.DIR[i].no_of_files=0;
	}
	
	
	printf("\n\n1.Create file\n2.List the files\n3.Search for a file\n4.Exit\n");
	printf("Enter option:");
	scanf("%d",&choice);
	
	while(choice>=1 && choice<=3)
	{
		if(choice==1)
		{
			char dir_name[100];
			printf("\nEnter directory name:");
			scanf("\n");
			scanf("%[^\n]",dir_name);
			
			int flag=0;
			for(int i=0;i<no_of_user;i++)
				if(strcmp(mDIR.DIR[i].name,dir_name)==0)
				{
					flag=1;
					char temp[100];
					printf("Enter the name of the file:");
					scanf("\n");
					scanf("%[^\n]",temp);
			
					int flag=0;
					for(int j=0;j<mDIR.DIR[i].no_of_files;j++)
					{
						if(strcmp(mDIR.DIR[i].FILE[j].name,temp)==0)
						{
							printf("File already exists");
							strcat(temp,"(1)");
							flag=1;
						}
					}
			
			
		
					strcpy(mDIR.DIR[i].FILE[mDIR.DIR[i].no_of_files].name,temp);
					
					strcpy(temp,"");
					strcat(temp,mDIR.name);
					strcat(temp,mDIR.DIR[i].name);
					strcat(temp,"/");
					strcat(temp,mDIR.DIR[i].FILE[mDIR.DIR[i].no_of_files].name);
					strcpy(mDIR.DIR[i].FILE[mDIR.DIR[i].no_of_files].path,temp);
					
					mDIR.DIR[i].no_of_files+=1;
			
					if(flag==0)
						printf("\nFile added\n");
				}
			if(flag==0)
				printf("\nNo directory found\n");
		}
		if(choice==2)
		{
			printf("\n\n%s%20s\n","File Name","Path");
			for(int i=0;i<no_of_user;i++)
			for(int j=0;j<mDIR.DIR[i].no_of_files;j++)
			{
				printf("%s%24s\n",mDIR.DIR[i].FILE[j].name,mDIR.DIR[i].FILE[j].path);
			}
		}
		if(choice==3)
		{
			char temp_name[100];
			int flag=0;
			printf("Enter file name to be seached:");
			scanf("\n");
			scanf("%[^\n]",temp_name);
			for(int i=0;i<no_of_user;i++)
			for(int j=0;j<mDIR.DIR[i].no_of_files;j++)
			{
			
				if(strcmp(mDIR.DIR[i].FILE[j].name,temp_name)==0)
				{
					printf("\nFile found at:%s",mDIR.DIR[i].FILE[j].path);
					flag=1;
				}
					
			}
			if(flag==0)
				printf("\nFile not found");
		}
			
		
		printf("\n\n1.Create file\n2.List the files\n3.Search for a file\n4.Exit\n");
		printf("Enter option:");
		scanf("%d",&choice);	
	}
	return;
}

int main()
{
	printf("-----File Organization techniques-----\n\n");
	int choice=0;
	
	printf("\n1.Single level\n2.Two level");
	printf("\nEnter choice:");
	scanf("%d",&choice);
	
	if(choice==1)
		single_level();
	if(choice==2)
		two_level();
		
	
	return 0;	
}
