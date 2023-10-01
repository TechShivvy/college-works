#include<stdio.h>
#include "studimpl.h"
int main()
{
	struct studADT s;
	struct stud S;
	int ch,n;
	printf("No of Records to be Inserted: ");
	scanf("%d",&n);
	init(&s,n);
	insert(&s);
  computeResult(&s);
	display(s);
	printf("\n-----------------------------------------------\nMenu: \n\n1.Insert a record at Front\n2.Insert a Record at Back\n3.After a RegNo\n4.Search Name\n5.Delete a Record\n6.List details of Students those who passed\n7.List the number of Students who secured FirstClass\n8.Exit");
  do{
  /*printf("\n-----------------------------------------------\nMenu: \n\n1.Insert a record at Front\n2.Insert a Record at Back\n3.After a RegNo\n4.Search Name\n5.Delete a Record\n6.List details of Students those who passed\n7.List the number of Students who secured FirstClass\n8.Exit\n\nEnter your choice: ");*/
  printf("\n\nEnter your choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:// printf("\nAt Front: \n");
            insDet(&S);
            insertFront(&s,&S);
            computeResult(&s);
            display(s);
            break;
		case 2://	printf("\nAt End: \n");
            insDet(&S);
            //computeResult(&s);
            insertEnd(&s,&S);
            computeResult(&s);
            display(s);
            break;
		case 3://	printf("\nAfter RegNo: \n");
            printf("\nInsert After Reg. No.: ");
            int rno,i;
            scanf("%d",&rno);
            for(i=0;i<s.max;i++)
	    {
	    	if(s.s[i].rno==rno)
	    		break;
	    }
	    if(i==s.max)
	    	printf("\n%d is not in the records, new record is not inserted!\n",rno);
	    else
	    {
		    insDet(&S);
		    //computeResult(&s);
		    insertRegNo(&s,&S,rno);
		    computeResult(&s);
		    display(s); 
	    }
            break;
		case 4: //printf("\nSearch Name: \n");
            printf("\nEnter Name: ");
            char key[30];
            scanf("%s",key);
            struct studADT p;
            //printf("\nmax: %d\n",p.max);			
            p=searchName(s,key);	
            display(p);
            break;
		case 5:// printf("\nDeletion: \n");
            printf("\nEnter Reg. No.: ");
            scanf("%d",&rno);
            del(&s,rno);
            display(s);
            break;
    case 6: printf("\nPassed students:\n");
            struct studADT FC;
            FC=listResult(s);
            //printf("\nmax: %d\n",FC.max);
            if(FC.max!=0)
              display(FC);
            else
              printf("\nNo one passed!\n");
            break;
    case 7: printf("\nNumber of FC Students: %d\n",listClass(s));
            break;
		case 8: return 0;
			      break;	
		default: printf("\nInvalid Input!\n");
	}
  }while(ch!=8);
	return 0;
}
