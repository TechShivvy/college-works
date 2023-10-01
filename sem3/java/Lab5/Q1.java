import java.util.*;

class MinorCitizenException extends Exception
{
	String msg;
	public MinorCitizenException(String str)
	{
		super(str);
		msg=str;
	}
}

class Person
{
	String name;
	int age;
	long aadharnumber;
	void getInput()
	{
		Scanner scan=new Scanner(System.in);
		String AGE=null;
		long aadharnumber;
		System.out.print("\nEnter Name: ");
		name=scan.nextLine();
		System.out.print("Enter Aadhar No.: ");
		this.aadharnumber=scan.nextLong();
		scan.nextLine();
		hasAadhar();
		//scan.nextInt();
		try
		{
			System.out.print("Enter Age: ");
			AGE=scan.nextLine();
			Integer.parseInt(AGE);
		}
		catch(NumberFormatException e)
		{
			System.out.println("\nPlease Enter a valid age!\n");
			return;
		}
		age=Integer.parseInt(AGE);
	}
	void display()
	{
		System.out.print("\nName: "+name);
		System.out.print("\nAge: "+age);
		System.out.println("\nAadhar No.: "+aadharnumber);
		canVote();		
	}
	void canVote()
	{
		try{
			if(age<18)
				throw new MinorCitizenException("\nYou arent eligible to vote!\n");
			else
				System.out.println("\nYou are eligible to vote!\n");	
		}
		catch(MinorCitizenException e){
			System.out.println(e.msg);
			
		}
	}
	void hasAadhar()
	{
		try
		{
		
		if(aadharnumber<100000000000L)
			throw new NullPointerException("\nEnter a valid AADHAR No!!\n");
			
		}
		catch(NullPointerException n)
		{
			System.out.println(n.getMessage());
			System.exit(0);
		}
	}
}
class Q1
{
	public static void main(String args[])
	{
		Person p=new Person();
		p.getInput();
		p.hasAadhar();
		p.display();
	}
}
