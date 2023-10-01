import java.util.*;
class dll
{
	public static void main(String[] args)
	{
    		int ch;
		Scanner scan=new Scanner(System.in);;
		LinkedList<Integer> dll= new LinkedList<>();
System.out.println("1.Insert element on both sides\n2.Delete element on both sides\n3.Insert an element at a particular position\n4.Delete a particular element\n5.Search for a particular element\n6.Display list in forward order and backward order\n7.Sort the elements in LinkedList\n8.Replace one element in the list with another list\n9.Remove duplicate elements\n10.Exit");

  do{
    System.out.print("\nEnter choice: ");
    ch=scan.nextInt();
    scan.nextLine();
		/*int[] a1=new int[]{1,2,3,4,4,3,2,1,5,6};
		for (int i : a1)
		{
		    dll.add(i);
		}*/
    int ele;
    switch(ch)
    {
      case 1: System.out.print("\nEnter the element: ");
                ele=scan.nextInt();
                scan.nextLine(); 
                dll.add(ele);
		            dll.addFirst(ele);
                break;
      case 2: if(dll.poll()==null||dll.pollLast()==null)
                {
                  System.out.print("\nNot enof elements to remove!");
                }
                break;
      case 3: System.out.print("\nEnter index and element: ");
              try{
          dll.add(scan.nextInt(),scan.nextInt());}
          catch(IndexOutOfBoundsException e)
          {
            System.out.print("\nINVALID INDEX!");
          }
          scan.nextLine();
                break;
      case 4: System.out.print("\nEnter element to remove: ");
                int a=dll.indexOf(scan.nextInt());
                a=(a==-1)?1:dll.remove(a);
                scan.nextLine();
                break;
      case 5: System.out.print("\nEnter element to search: ");
            int index=dll.indexOf(scan.nextInt());
            scan.nextLine();
              String str=index==-1?"Element is not there in the list":"Element is found at: "+index;
                System.out.println(str);
                break;
      case 6: System.out.print("\nFront: "+dll);
		            Collections.reverse(dll);
                System.out.print("\nReverse: "+dll);
                Collections.reverse(dll);
                break;
      case 7: Collections.sort(dll);
                break;
      case 8: 	System.out.print("\nEnter element and its replacement: ");
      		Collections.replaceAll(dll,scan.nextInt(),scan.nextInt());
                scan.nextLine();
                break;
      case 9: 	Set<Integer> s1=new HashSet<>(dll);
		dll.clear();
		dll.addAll(s1);
                break;
      case 10:break;
      default: System.out.print("\nINVALID CHOICE!!");
    }
    if(ch!=6&&ch!=5&&ch!=10)
    	System.out.println(dll);
		/*dll.add(10);
		dll.addFirst(10);
		System.out.println(dll);
		
		
		dll.poll();
		dll.pollLast();
		System.out.println(dll);
		
		dll.add(4,10000);
		System.out.println(dll);
		
		dll.remove(dll.indexOf(4));
		System.out.println(dll);
		
		System.out.println(dll.indexOf(10000));
		
		ListIterator itr=dll.listIterator();
		System.out.println(dll);
		
		
		Collections.reverse(dll);
		System.out.println(dll);
		Collections.reverse(dll);
		
		Collections.sort(dll);
		System.out.println(dll);
		
		for(Integer i:dll)
		{
			
		}
		Collections.replaceAll(dll,3,-99);
		System.out.println(dll);
		
		Set<Integer> s1=new HashSet<>(dll);
		dll.clear();
		dll.addAll(s1);
		System.out.println(dll);*/
  }while(ch!=10);
	}
} 

