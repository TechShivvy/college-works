import java.lang.Math;
class ebill
{
	int cno;
	String name;
	int pr;
	int cr;
	String connex;
	double bill;
}
class First
{

public static void main(String args[])
{	
	ebill EB= new ebill();
	EB.cno=Integer.parseInt(args[0]);
	EB.name=args[1];
	EB.pr=Integer.parseInt(args[2]);
	EB.cr=Integer.parseInt(args[3]);
	EB.connex=args[4];
	System.out.println("Consumer no: "+EB.cno);
	System.out.println("Consumer Name: "+EB.name);
	System.out.println("Prev Reading: "+EB.pr);
	System.out.println("Cur Reading: "+EB.cr);
	System.out.println("Connecton : "+EB.connex);
	EB.bill=0;
	if(EB.connex.equals("domestic"))
	{
		
		if(EB.cr<=100)
			EB.bill+=EB.cr;
		else if(EB.cr>100&&EB.cr<=200)
			EB.bill+=100+(EB.cr-100)*2.5;
		else if(EB.cr>200&&EB.cr<=500)
			EB.bill+=350+(EB.cr-200)*4;
		else if(EB.cr>500)
			EB.bill+=1550+(EB.cr-500)*6;
		//EB.bill=Math.min(100d,0.5*(EB.cr+Math.abs(EB.cr)))+ Math.min(250d,0.5*2.5*(EB.cr-100+Math.abs(EB.cr-100)))+Math.min(1200d,2*(EB.cr-200+Math.abs(EB.cr-200)))+3*(EB.cr-500+Math.abs(EB.cr-500));	
	}
	else if(EB.connex.equals("commercial"))
	{
		if(EB.cr<=100)
			EB.bill+=EB.cr*2;																																																																																																						
		else if(EB.cr>100&&EB.cr<=200)
			EB.bill+=200+(EB.cr-100)*4.5;
		else if(EB.cr>200&&EB.cr<=500)
			EB.bill+=450+(EB.cr-200)*6;
		else if(EB.cr>500)
			EB.bill+=1800+(EB.cr-500)*7;
		//EB.bill=Math.min(100d,0.5*2*(EB.cr+Math.abs(EB.cr)))+ Math.min(250d,0.5*4.5*(EB.cr-100+Math.abs(EB.cr-100)))+Math.min(1200d,3*(EB.cr-200+Math.abs(EB.cr-200)))+7*0.5*(EB.cr-500+Math.abs(EB.cr-500));
	}
	else
		System.out.println("Invlid Input!");
	System.out.println("Bill: "+EB.bill);
}
}
