import java.util.*;
class dll
{
	public static void main(String[] args)
	{
    char ch;
		Scanner scan=new Scanner(System.in);;
		LinkedList<Integer> dll= new LinkedList<>();
System.out.println("a.	Insert element on both sides\nb.	Delete element on both sides\nc.	Insert an element at a particular position\nd.	Delete a particular element\ne.	Search for a particular element\nf.	Display list in forward order and backward order\ng.	Sort the elements in LinkedList\nh.	Replace one element in the list with another list\ni.	Remove duplicate elements\nj. Exit");

  do{
    System.out.print("\nEnter choice: ");
    ch=(scan.nextLine()).charAt(0);
		/*int[] a1=new int[]{1,2,3,4,4,3,2,1,5,6};
		for (int i : a1)
		{
		    dll.add(i);
		}*/
    int ele;
    switch(ch)
    {
      case 'a': System.out.print("\nEnter the element: ");
                ele=scan.nextInt();
                scan.nextLine(); 
                dll.add(ele);
		            dll.addFirst(ele);
                break;
      case 'b': if(dll.poll()==null||dll.pollLast()==null)
                {
                  System.out.print("\nNot enof elements to remove!");
                }
                break;
      case 'c': System.out.print("\nEnter index and element: ");
              try{
          dll.add(scan.nextInt(),scan.nextInt());}
          catch(IndexOutOfBoundsException e)
          {
            System.out.print("\nINVALID INDEX!");
          }
          scan.nextLine();
                break;
      case 'd': System.out.print("\nEnter element to remove: ");
                dll.remove(scan.nextInt());
                scan.nextLine();
                break;
      case 'e': System.out.print("\nEnter element to search: ");
            int index=scan.nextInt();
            scan.nextLine();
              String str=dll.indexOf(index)==-1?"Element is not there in the list":"Element is found at: "+index;
                System.out.println(str);
                break;
      case 'f': System.out.print("\n Front: "+dll);
		            Collections.reverse(dll);
                System.out.print("\n Reverse: "+dll);
                Collections.reverse(dll);
                break;
      case 'g': Collections.sort(dll);
                break;
      case 'h': Collections.replaceAll(dll,scan.nextInt(),scan.nextInt());
                scan.nextLine();
                break;
      case 'i': 	Set<Integer> s1=new HashSet<>(dll);
		dll.clear();
		dll.addAll(s1);
                break;
      default: System.out.print("\nINVALID CHOICE!!");
    }
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
  }while(ch!='j');
	}
} 
