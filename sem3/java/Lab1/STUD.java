import java.util.*;

class student
{
	String name;
	String dept;
	char grade;
	long id;
	int m1,m2,m3;
	void input(String n,String d,long ID,int M1,int M2,int M3)
	{
		name=n;
		dept=d;
		id=ID;
		m1=M1;
		m2=M2;
		m3=M3;
	}
	void gcalc()
	{
		double x=(m1+m2+m3)/3;
		if(x>80&&x<=100)
			grade='O';
		else if(x>60 &&x<=80)
			grade='A';
		else if(x>40 && x<=60)
			grade='B';
		else
			grade='C';
	}
	void display()
	{
		System.out.println("\nName  : "+name+"\nDept  : "+dept+"\nID    : "+id+"\nMark 1: "+m1+"\nMark 2: "+m2+"\nMark 3: "+m3+"\nGrade : "+grade+"\n");
	}
	boolean search(String sdi)
	{
  		if(dept.equals(sdi))
		{
			display();
			return true;
		}
		return false;
	}
	boolean search(Long sdi)
	{
  		if(id==sdi)
		{
			display();
			return true;
		}
		return false;
	}
}
class stud
{
public static void main(String[] args)
{
	int i,ch,n=Integer.parseInt(args[0]);
	student[] s=new student[n];
	for(i=0;i<n;i++)
	{
		s[i]= new student();
		s[i].input(args[1+i*6],args[2+i*6],Long.parseLong(args[3+i*6]),Integer.parseInt(args[4+i*6]),Integer.parseInt(args[5+i*6]),Integer.parseInt(args[6+i*6]));
		s[i].gcalc();
		s[i].display();
	}
 	Scanner scan=new Scanner(System.in);
	do
	{
		System.out.println("1.Do you want to search?\n2.Exit");
		System.out.print("Enter your choice(1,2): ");
		ch=scan.nextInt();
		scan.nextLine();
		switch(ch)
		{
			case 1:System.out.print("\nEnter the Dept/ID to search: ");
				String key=scan.nextLine();
				Long id;
				boolean val=false;
				if(Character.isDigit(key.charAt(0)))
				{
					id=Long.parseLong(key);
					i=0;
					do
					{	
 						val=s[i++].search(id);
					}while(i<n&&(!val));	
				}
				else
				{	
					for(i=0;i<n;i++)
					{
 						val=s[i].search(key)||val;
					}
		
				}	
				if(!val)
					System.out.println("\nRecord not Found!\n");
				break;
			case 2:break;
			default:System.out.println("\nInvalid Input!\n");
		}	
	}while(ch!=2);
}
}
