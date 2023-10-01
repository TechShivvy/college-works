import java.util.Scanner;
class Employee
{
	String name;
	Long id;
	String desgn;
	int YOE;
	float bp=10_000,DA,HRA,LIC,PF,gpay,npay,ded;
	Long NOH;
	void input()
	{
		Scanner scan =  new Scanner(System.in);
		System.out.print("\nEnter Name: ");
		name=scan.nextLine();
		System.out.print("Enter ID: ");
		id=scan.nextLong();
		scan.nextLine();
		int ch=0;
		do
		{
			System.out.print("Enter Designation: ");
			desgn=scan.nextLine();
			if(desgn.matches("Trainee|Analyst|Software engineer|TeamLead|Manager"))
			{	
				System.out.print("Enter Years of Exp. : ");
				YOE=scan.nextInt();
				ch=0;
			}
			else if(desgn.equals("Intern"))
			{
				System.out.print("Enter Hours worked: ");
				NOH=scan.nextLong();
				ch=0;
			}
			else
			{
				System.out.println("\nInvalid Input!\nEnter Again\n");
				ch=1;}
				//return 0;
		}while(ch==1);
		System.out.print("Enter LIC premium amount(enter 0 if u didnt opt): ");
		LIC=scan.nextFloat();
		//return 1;
	}
	void pay_calc()
	{
		if(desgn.equals("Intern"))
 		{
			DA=2000;
			HRA=1000;
			PF=500;
			gpay=NOH*1000+DA+HRA;
		}
		else if(desgn.equals("Manager"))
 		{
			DA=0.4f*bp;
			HRA=0.1f*bp;
			PF=0.08f*bp;
			gpay=bp+DA+HRA;
		}
		else
 		{
			DA=0.3f*bp;
			HRA=0.1f*bp;
			PF=0.08f*bp;
			gpay=bp+DA+HRA;
		}	
		ded=LIC!=0?LIC+PF:PF;
		npay=gpay-ded;	
	}
	void disp()
	{
		String str=!desgn.equals("Intern")?"\nYears Of Experience: "+YOE:"\nNo. of Hours Worked: "+NOH;
		System.out.println("\nName: "+name+"\nDesignation: "+desgn+"\nID: "+id+str+"\nGross Salary: "+gpay+"\nNet Salary: "+npay+"\nDA: "+DA+"\nHRA: "+HRA+"\nPF: "+PF+"\nLIC: "+LIC);
	} 
}
class Emp
{
	public static void main(String args[])
	{
		Scanner scan=new Scanner(System.in);
		System.out.print("\nEnter the number of Employees: ");
		int i,n=scan.nextInt();
		Employee[] emp = new Employee[n];
		for(i=0;i<n;i++)
		{
			emp[i]= new Employee();
			emp[i].input();
			//if(emp[i].input()==0)    int input
			//	System.exit(0);
			emp[i].pay_calc();
		}
		System.out.print("\nSalary Details of all Employees:\n");
		for(i=0;i<n;i++)
		{
			emp[i].disp();
		}
		System.out.print("\nEnter the ID of the Employee to search:\n");
		int f=0,id=scan.nextInt();	
		for(i=0;i<n;i++)
		{	
			if(id==emp[i].id)
			{
				emp[i].disp();
				f=1;	
				break;		
			}
		}
		if(f==0)
			System.out.print("\nMatch not found!\n");
		System.out.println("\n>>Eligible for promotion<<\n");
		for(i=0;i<n;i++)
		{
			if(!emp[i].desgn.equals("Intern") && emp[i].YOE>3)
				System.out.println("\n"+emp[i].name);
			
		}
	}
}