#include<stdio.h>
#include<string.h>
#define SIZE 100

int n=5, r=3;          //given value for deafult test case
int max[SIZE][SIZE];
int alloc[SIZE][SIZE];
int Palloc[SIZE];
int need[SIZE][SIZE];
int Pneed[SIZE];
int req[SIZE];
int avail[SIZE];
int Pavail[SIZE];
int req_flag[SIZE];

//default test case
/*int alloc[5][3] = { { 0, 1, 0 }, // P0    // Allocation Matrix
                        { 2, 0, 0 }, // P1
                        { 3, 0, 2 }, // P2
                        { 2, 1, 1 }, // P3
                        { 0, 0, 2 } }; // P4
 
    int max[5][3] = { { 7, 5, 3 }, // P0    // MAX Matrix
                      { 3, 2, 2 }, // P1
                      { 9, 0, 2 }, // P2
                      { 2, 2, 2 }, // P3
                      { 4, 3, 3 } }; // P4
 
    int avail[3] = { 3, 3, 2 };  */

void input();		// to take input
void disp();		// to display table
int safety();
void reset(int t);	// to revert back to original state
void copy(int t);	// backup of original state
void request();


int main()
{
	int ch;
	printf("\n********** Banker's Algorithm************\n");
	printf("\n1. Read Data\n2. Print Data\n3. Check system state\n4. Resource request\n5. Exit\n");
	do 
	{
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				input();
				break;
			case 2:
				disp();
				break;
			case 3:
				safety();
				//disp();
				reset(-1);
				break;
			case 4:
				request();
				break;
			case 5: 
				printf("\nExiting...\n");
				return 0;
				break;
		}	
	}while(ch!=5);
	return 0;
}

void input()
{
	printf("\nEnter the number of processes:");
	scanf("%d",&n);
	printf("Enter the number of resources:");
	scanf("%d",&r);
	printf("\n");
	
	for(int i=0;i<r;i++)
	{
		printf("Enter the Number of Available instances of %c:",(char)(65+i));
		scanf("%d",&avail[i]);
		Pavail[i]=avail[i];
	}   
	
	printf("\nEnter the Max Requirement for:\n");
	for(int i=0;i<n;i++)
	{
		printf("P%d: ",i);
		for(int j=0;j<r;j++)
		    scanf("%d",&max[i][j]);            
	}
	
	printf("\nEnter the values of Allocation for:\n");
	for(int i=0;i<n;i++)
	{
		printf("P%d: ",i);
		for(int j=0;j<r;j++)
		    scanf("%d",&alloc[i][j]);           
	}  
	
	// to calc need
	for (int i = 0; i < n; i++) 
	{
       	for (int j = 0; j < r; j++)
         		need[i][j] = max[i][j] - alloc[i][j];
    	}
	    
}
void disp()
{
	printf("\nPID\tAlloc\t\tMax\t\tNeed\t\tAvail\n   \t");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<r;j++)
		{
			printf("%c  ",(char)(65+j));
		}
		printf("\t");
	}
	printf("\n");		
	
	// to calc need, cuz of deafult test case
	for (int i = 0; i < n; i++) 
	{
       	for (int j = 0; j < r; j++)
         		need[i][j] = max[i][j] - alloc[i][j];
    	}
	
	for (int i = 0; i < n; i++)
	{
                printf("P%d \t",i);
                for (int j = 0; j < r; j++)
                	printf("%-3d", alloc[i][j]);
                printf("\t");
                for (int j = 0; j < r; j++)
                	printf("%-3d", max[i][j]);
                printf("\t");
                for (int j = 0; j < r; j++)
                	printf("%-3d", need[i][j]);
                printf("\t");
                if(i==0)
                {
                	for (int j = 0; j < r; j++)
                    		printf("%-3d", avail[j]);
                }
                printf("\n");
         
        } 
}

int safety()
{
	int finish[SIZE], flag = 1, i, j, k, c1 = 0;
	char seq[100],buf[5];
	strcpy(seq,"");
	for (i = 0; i < n; i++)
		finish[i] = 0;
	
	// for need, cuz of deafult test case
	for (int i = 0; i < n; i++) 
	{
       	for (int j = 0; j < r; j++)
         		need[i][j] = max[i][j] - alloc[i][j];
    	}
	
	printf("\n");
	while(flag) 
	{
        	flag = 0;
        	for (i = 0; i < n; i++)
        	{
        		int c = 0;
            		for (j = 0; j < r; j++)
            		{
                		if ((finish[i] == 0) && (need[i][j] <= avail[j])) 
                		{
		            		c++;
		            		if(c == r)
		            		{
		                		for (k = 0; k < r; k++)
		                		{
							avail[k] += alloc[i][k];
							finish[i] = 1;
						    	flag = 1;
		                		}
		    
				        	sprintf(buf,"P%d->",i);
				        	strcat(seq,buf);
				 
		           		}
                		}
                		else
                			break;
            		}
        	}
    	}
    	for (i = 0; i < n; i++)
    	{
		if (finish[i] == 1)
			c1++;
    	}
    	if (c1 == n)
        	printf("\nThe system is in safe state\nSafety Seq: %s\b\b  \n",seq);
   	else
        	printf("\nProcess are in dead lock\nSystem is in unsafe state!\n");
        return c1-n;
}

void reset(int t)
{
	for(int i=0;i<r;i++)
	{
		avail[i]=Pavail[i];
		if(t!=-1)
		{
			alloc[t][i]=Palloc[i];
			need[t][i]=Pneed[i];
		}
	}	
}

void copy(int t)
{
	for(int i=0;i<r;i++)
	{
		Palloc[i]=alloc[t][i];
		Pneed[i]=need[t][i];
	}
}

void request() 
{
	int pid;
    	printf("\nEnter process to request: P");
   	scanf("%d",&pid);
   	printf("Enter the request vector for process P%d: ",pid);
   	for(int i=0;i<r;i++)
		scanf("%d",&req[i]);
		
		
	int flag=-1;
    	for(int i=0;i<r;i++)
    	{
      		if(req[i]>need[pid][i] && req[i]>avail[i])	// checking 1st 2 steps
      	  	{
      	  		flag=i;
            		break;
          	}
    	}            
    	if(flag!=-1)
    	{
        	printf("\nThe system is not safe as request for resource %c is more than its need!\n",(char)(65+flag));
        	printf("Resource request by P%d CANNOT be granted\n",pid);
        	return;
    	}
    	
    	// if both steps are TRUE, proceeding to 3rd one							
    	copy(pid);
    	
    	for (int i = 0; i < r; i++) 
    	{
            	avail[i] -= req[i];
            	alloc[pid][i] += req[i];
            	need[pid][i] -= req[i];
        }
    	if(safety()==0)
    		printf("Resource request by P%d CAN be granted\n",pid);
    	else
    		printf("Resource request by P%d CANNOT be granted\n",pid);
    	//disp();
    	reset(pid);
}

