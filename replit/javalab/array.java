import java.util.*;
class array
{
	public static void main(String[] args)
	{	
		int[] a1=new int[]{1,2,3,4,4,3,2,1,5,6};
		int[] a2=new int[]{1,1,3,3,5,6,7,8};
		ArrayList<Integer> A1=new ArrayList<>();
		ArrayList<Integer> A2=new ArrayList<>();
		//int[] ints = {1, 2, 3};
		//List<Integer> intList = new ArrayList<Integer>(ints.length);
		for (int i : a1)
		{
		    A1.add(i);
		}
		for (int i : a2)
		{
		    A2.add(i);
		}
		System.out.println(A1);
		ArrayList<Integer> A3=new ArrayList<>();
		A3.addAll(A1);
		A3.addAll(A2);
		System.out.println(A3);
		Set<Integer> s1=new HashSet<>(A3);
		System.out.println(s1);
		//A1.retainAll(A2);
		//System.out.println(A1);
		System.out.println(A1.equals(A2)				);	
	}
}
