import java.util.*;
class Sort<Type extends Comparable<Type>>
{
	  int n;
	  Type[] arr;

	  Sort(int n, Type[] arr)
	  {
		    this.n=n;
		    this.arr=arr;
	  }

	  void sortArray()
	  {
		    for(int i=0;i<n;i++)
		    {
			      Type min=arr[i];
			      int pos=i;
			      for(int j=i;j<n;j++)
			      {
					if(arr[j].compareTo(min)<0)
					{
						  min=arr[j];
						  pos=j;
					}
			      }
			      Type temp=arr[pos];
			      arr[pos]=arr[i];
			      arr[i]=temp;
		    }
		    System.out.print("\nSorted array: ");
		    for(int i=0;i<n;i++)
		    {
		     	 System.out.print(arr[i] + " ");
		    }
	  }
}

class sort
{
	  public static void main(String[] args)
	  {
	    
		    /*System.out.print("\nDouble array size: ");
		    int dsize = sc.nextInt();
		    Double[] darr = new Double[dsize];*/
		    Double darr[]= new Double[]{1.2,1.3,1.5,1.4,1.7,1.8,0.0,5.0,1.1};
		    System.out.print("Double: [1.2,1.3,1.5,1.4,1.7,1.8,0.0,5.0,1.1]");
		    Sort<Double> ds = new Sort<>(9, darr);
		    /*for(int i = 0; i < dsize; i++)
		    {
			      System.out.print("\nEnter element: ");
			      darr[i] = sc.nextDouble();
		    }*/
		    ds.sortArray(); 	
		  
		    /*Scanner sc = new Scanner(System.in);
		    System.out.print("Integer array size: ");
		    int isize = sc.nextInt();
		    Integer[] iarr = new Integer[isize];*/
		    Integer iarr[]=new Integer[]{1,2,3,0,-1,7,3,5};
		    System.out.print("\n\nInteger: [1,2,3,0,-1,7,3,5]");
		    Sort<Integer> is = new Sort<>(8, iarr);
		    /*for(int i = 0; i < isize; i++)
		    {
			      System.out.print("\nEnter element ");
			      iarr[i] = sc.nextInt();
		    }*/
		    is.sortArray();

		    /*System.out.print("\nCharacter array size: ");
		    int csize = sc.nextInt();
		   Character[] carr = new Character[csize];*/
		   Character carr[]=new Character[]{'t','y','c','q','U','P','O','h','K'};
		   System.out.print("\n\nChar: ['t','y','c','q','U','P','O','h','K']");
		    Sort<Character> cs = new Sort<>(9, carr);
		    /*for(int i = 0; i < csize; i++)
			    {
			      System.out.print("\nEnter element: ");
			      carr[i] = sc.next().charAt(0);
		    }*/
		    cs.sortArray();
		    System.out.println();
	  }
}
