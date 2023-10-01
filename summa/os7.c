#include <stdio.h>
#define full 10
int n, m;
int request[full];
int avail[full];
int alloc[full][full];
int need[full][full];
int max[full][full];
int req_flag[full];

void safety(){
    int f[n], ans[n], ind = 0,k,i,j;
            for (k = 0; k < n; k++) {
                f[k] = 0;
            }

            int y = 0;
            for (k = 0; k < 5; k++) {
                for (i = 0; i < n; i++) {
                    if (f[i] == 0) {
                        int flag = 0;
                        for (j = 0; j < m; j++) {
                            if (need[i][j] > avail[j]){
                                
                                flag = 1;
                                break;
                            }
                        }

                        if (flag == 0) {
                            ans[ind++] = i;
                            printf("\nprocess %d executing\n",i);
                            printf("currently available resources\n");
                            for (y = 0; y < m; y++){
                                avail[y] += alloc[i][y];
                                
                                printf("%d ",avail[y]);
                            }
                            f[i] = 1;

                        }
                    }
                }
            }

            int flag = 1;
        
            for(int i=0;i<n;i++){
                if(f[i]==0){
                    flag=0;
                    printf("\nThe following system is not safe");
                    break;
                }
            }
        
            if(flag==1)
            {
                printf("\nFollowing is the SAFE Sequence\n");
                for (i = 0; i < n - 1; i++){
                    printf(" P%d ->", ans[i]);
                }
                printf(" P%d", ans[n - 1]);
            }
            printf("\n");
}


void res_request(){
    int t;
    
    printf("\nEnter process to request: P");
    scanf("%d",&t);
    printf("Enter the request vector for process P%d: ",t);
    for(int j=0;j<m;j++){
        if(j+1==m){
            scanf("%d",&request[j]);
        }
        else
            scanf("%d ",&request[j]);
    }
    int flag=-1;
    for(int i=0;i<m;i++){
        if(request[i]>need[t][i]){
            flag=i;
            break;
        }
    }            
    if(flag>=0){
        printf("\nThe system is not safe as request for resource %c is more than its need!\n",(char)(65+flag));
        return;
    }
    
    for(int i=0;i<m;i++)
        req_flag[i]=0;
    for(int j=0;j<m;j++){
        if(request[j]<=avail[j] && req_flag[j]==0){
            avail[j]=avail[j]-request[j];
            alloc[t][j]=alloc[t][j]+request[j];
            need[t][j]=need[t][j]-request[j]; 
            req_flag[j]=1; 
        }
    }
    for(int i=0;i<m;i++){
        if(req_flag[i]==0){
            printf("\nThe system is not safe as request for resource %c cannot be allocated!\n",(char)(65+i));
            return;
        }
    }
    printf("\nThe system is safe and request for process P%d is granted!\n",t);
}

int main()
{
    int ch;
    printf("Read data\n");
    
    printf("enter the number of processes:");
    scanf("%d",&n);
    printf("\nenter the number of resources:");
    scanf("%d",&m);

    
    for(int i=0;i<m;i++){
        printf("enter the availablity or resource %c:",(char)(65+i));
        scanf("%d",&avail[i]);
    }

    
    printf("\nenter the values of allocation:");
    for(int i=0;i<n;i++){
        printf("\n Process %d:\n",i);
        for(int j=0;j<m;j++){
            scanf("%d",&alloc[i][j]);            
        }
    }
    
    printf("\nenter the max values:");
    for(int i=0;i<n;i++){
        printf("\n Process %d:\n",i);
        for(int j=0;j<m;j++){
            scanf("%d",&max[i][j]);            
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    do{
        printf("1. Print data\n2. Safe sequence\n3. Request allocation\n4. Exit\nenter your choice:");
        scanf("%d",&ch);
        if (ch == 1) {
            printf("Pid\tAlloc\tMax  \tNeed \tAvail\t\n--\t");
            for(int i=0;i<m;i++) printf("%c ",(char)(65+i));
            printf("\t");
            for(int i=0;i<m;i++) printf("%c ",(char)(65+i));
            printf("\t");
            for(int i=0;i<m;i++) printf("%c ",(char)(65+i));
            printf("\t");
            for(int i=0;i<m;i++) printf("%c ",(char)(65+i));
            printf("\n");
            printf("\t");
            printf("\n----------------------------------\n");
            for (int i = 0; i < n; i++) {
                printf("P%d\t",i);
                for (int j = 0; j < m; j++)
                printf("%d ", alloc[i][j]);
                printf("\t");
                for (int j = 0; j < m; j++)
                printf("%d ", max[i][j]);
                printf("\t");
                for (int j = 0; j < m; j++)
                printf("%d ", need[i][j]);
                printf("\t");
                if(i==0)
                for (int j = 0; j < m; j++)
                    printf("%d ", avail[j]);
                printf("\t\n");
            }
        } 
        if(ch==2){
            safety();                
        }
        else if(ch==3){
            res_request();
            safety();
        }

    }while(ch<4 && ch>0);
       
}
