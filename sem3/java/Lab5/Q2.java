import java.util.*;

class PANRequiredException extends Exception 
{
    String message;
    PANRequiredException(String str)
    {
        message = str;
    }
}                

class PANFormatMismatchException extends Exception 
{
    String message;
    PANFormatMismatchException(String str)
    {
        message = str;
    }
}

class MinBalanceException extends Exception 
{
    String message;
    MinBalanceException(String str)
    {
        message = str;
    }
}

class NotEnoughMoneyInAccountException extends Exception 
{
    String message;
    NotEnoughMoneyInAccountException(String str)
    {
        message = str;
    }
}

class AccountNotFoundException extends Exception 
{
    String message;
    AccountNotFoundException(String str)
    {
        message = str;
    }
}

class BranchNotFoundException extends Exception 
{
    String message;
    BranchNotFoundException(String str)
    {
        message = str;
    }
}

class Account
{
	String name;
	long AC;
	String branch;
	float bal;
	String PAN;
	static int noObj= 0;
	
	{
		noObj+=1;
	}
	Account()
	{
	}
	void disp()
	{
					System.out.println("NAME:"+name);

					System.out.println("ACCOUNT NUMBER: "+AC);
					System.out.println("BRANCH: "+branch);
					
					System.out.println("BALANCE: "+bal);
				
					System.out.println("PAN NUMBER: "+PAN);
					
	}
	Account(String name,long acct_num,String branch,float balance,String pan_num)
    	{
		this.name = name;
		AC = acct_num;
		this.branch = branch;
		bal = balance;
		PAN = pan_num;
	}
	static boolean PANCheck(String p)
	{
		if(p.length()!=10||Character.isDigit(p.charAt(0))||Character.isDigit(p.charAt(1))||Character.isDigit(p.charAt(2))||Character.isDigit(p.charAt(3))||Character.isDigit(p.charAt(4))||Character.isDigit(p.charAt(9))||!Character.isDigit(p.charAt(5))||!Character.isDigit(p.charAt(6))||!Character.isDigit(p.charAt(7))||!Character.isDigit(p.charAt(8)))
			return true;
		return false;
		}
			
	void deposit(float amt)
	{
		try
		{
			if(amt>25000f)
				throw new PANRequiredException("\nPAN NUMBER REQUIRED!\n");
			else
				this.bal=this.bal+amt;
		}
		catch(PANRequiredException e)
		{
			Scanner sc=new Scanner(System.in); 
			System.out.println(e.message);
			while(true)
			{
				String pan=sc.nextLine();
				try
				{
					if(!pan.equals(PAN))
					{
						throw new PANRequiredException("\nWrong PAN Number! Enter again!\n");
					}
					else if(PANCheck(pan))
					{
					
						throw new PANFormatMismatchException("\nPAN Format mismatch! Enter again!\n");
					}
					else
						this.bal=this.bal+amt;
						break;
				}
				catch (PANRequiredException o)
				{
				    System.out.println(o.message);
				}
				catch (PANFormatMismatchException o)
				{
				    System.out.println(o.message);
				}
			}
		}
	}
	void withdrawl(float amt)
	{
		try{
			if(bal-amt<500)
				throw new MinBalanceException("\nMinimum value is 500!\n");
		 
			else if(amt > bal)
				throw new NotEnoughMoneyInAccountException("\nNot enof money IN ACC!\n");
			else
				bal -= amt;
			 
       	}
		catch(MinBalanceException e)
		{
		    System.out.println(e.message);
		}
		catch(NotEnoughMoneyInAccountException e)
		{
		    System.out.println(e.message);
		}

		
	}
}

class TestAcc
{
	public static int search(Account record[] ,long acct_num)
	{
		for(int i= 0;i<Account.noObj;i++)
		{
		    if(record[i].AC == acct_num)
		    {
		        return i;
		    }
		}
		return -1;
	}

	public static void main(String args[])
	{
		Scanner sc = new Scanner(System.in);
		char x;
		int ch=0;
		Account accs[] = new Account[10];
		accs[Account.noObj]=new Account();
		//System.out.println(Account.noObj);
		do
		{
			System.out.println("\n------------------MENU-------------------\n\n 1.Create an Account\n 2.Deposit Amount\n 3.Withdraw Amount\n 4.Exit\n");
			System.out.print("--->>Choice :");
			ch = sc.nextInt();
			sc.nextLine();
			switch(ch)
			{
				case 1: System.out.println("ENTER THE DETAILS :");
					System.out.print("NAME: ");
					String name = sc.nextLine();

					System.out.print("ACCOUNT NUMBER:");
					long acct_num = sc.nextLong();
					sc.nextLine();
					
					System.out.print("BRANCH:");
					String branch = sc.nextLine();
					
					System.out.print("BALANCE:");
					float balance = sc.nextInt();
					sc.nextLine();
					
					System.out.print("PAN NUMBER:");
					String pan_num;
					while(true){
					pan_num = sc.nextLine();
					try{
					if(Account.PANCheck(pan_num))
					{
					
						throw new PANFormatMismatchException("\nPAN Format mismatch! Enter again!\n");
					}
					else
						break;	
					}
					
					catch (PANFormatMismatchException o)
					{
					    System.out.println(o.message);
					}
					}
					accs[Account.noObj] = new Account(name,acct_num,branch,balance,pan_num);           
					accs[Account.noObj-1].disp();
					break;
				case 2:
					int index;
					System.out.println("ENTER ACCOUNT NUMBER :");
					long acc = sc.nextLong();
					sc.nextLine();
					try
					{
					    index  = search(accs, acc);
					    if(index==-1)
					    {
						throw new AccountNotFoundException("!!! ACCOUNT NOT FOUND !!");
					    }
					    else
					    {
						System.out.println("ENTER AMOUNT TO DEPOSIT :");
						float amt = sc.nextFloat();
						sc.nextLine();
						accs[index].deposit(amt);
					    }
					}
					catch(AccountNotFoundException e)
					{
					    System.out.println(e.message);
					}
					accs[Account.noObj-1].disp();
					break;
				case 3://int index;
					System.out.println("ENTER ACCOUNT NUMBER :");
					acc = sc.nextInt();
					try
					{
					    index  = search(accs, acc);
					    if(index==-1)
					    {
						throw new AccountNotFoundException("!!! ACCOUNT NOT FOUND !!");
					    }
					    else
					    {
						System.out.println("ENTER AMOUNT TO WITHDRAW :");
						float amt = sc.nextFloat();
						sc.nextLine();
						accs[index].withdrawl(amt);
					    }
					}
					catch(AccountNotFoundException e)
					{
					    System.out.println(e.message);
					}
					accs[Account.noObj-1].disp();
					break;
				case 4:
					break;
			}	
		}while(ch!=4);
		
		
	}
}

