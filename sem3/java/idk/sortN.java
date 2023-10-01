import java.util.*;
import java.lang.*;
class sortN
{
	<T extends Number> T sorty(T n)
	{
		ArrayList<Integer> a=new ArrayList<>();
		long nl=n.longValue(),sum=0;
		int N,rem,i=0;
		while(nl>0)
		{
			rem=(int) nl%10;
			a.add(rem);
			nl=nl/10;
			i++;
		}
		Collections.sort(a);
		for(int j=0;j<i;j++)
		{
			N=(int)((int)a.get(j)*Math.pow(10,i-j-1));
			sum+=N;	
		}
		return (T)(Object)sum;
	}
}
class  Main
{
	public static void main(String args[])
	{
		sortN s=new sortN();
		System.out.println(s.<Long>sorty(9876543L));
	}
}
