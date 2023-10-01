import java.util.*;

class string
{
	public static void main(String args[])
	{
		ArrayList<String> list=new ArrayList<String>();
		int ch=0;
		Scanner scan=new Scanner(System.in);
    
    list.add("hello");
			list.add("haha");
			list.add("shivcharan");
			list.add("shajith");
			list.add("srini");
			list.add("sid");
			list.add("shivcharan");			
    System.out.println("\nList: "+list);
		
    System.out.println("1. Append - add at end\n2. Insert – add at particular index\n3. Find the index of a particular element (Search)\n4. Display the list\n5. List all string starts with given letter\n6. List of all string contains the Substring\n7. Sort the elements in ArrayList\n8. Remove a particular element\n9. Replace one string with another string in ArrayList\n10. Remove duplicate elements\n11. Clear List\n12. Exit");		
						
		do
		{
			System.out.print("\nEnter ur choice: ");
			//ch++;
			
			ch=scan.nextInt();
			scan.nextLine();
			switch(ch)
			{
				case 1: System.out.print("\nEnter String: ");
					list.add(scan.nextLine());
					//System.out.println(list);			
					break;
				case 2: System.out.print("\nEnter index and String: ");
          try{
          list.add(scan.nextInt(),scan.next());}
          catch(IndexOutOfBoundsException e)
          {
            System.out.print("\nINVALID INDEX!");
          }
					break;
				case 3: System.out.print("\nEnter String to search: ");
					String str=scan.nextLine();
					int i;
					/*for(i=0;i<list.size();i++)
					{
						if(list.get(i).equals(str))
						{
							System.out.println("\n"+str+" found at "+i+" index");
							break;
						}
					}
					if(i==list.size())
						System.out.println("\n"+str+" is not in the list");*/
					if(list.contains(str))
						System.out.println("\n"+str+" found at "+list.indexOf(str)+" index");
					else
						System.out.println("\n"+str+" is not in the list");		
					break;
				case 4:;
        /* for(i=0;i<list.size();i++)
          System.out.println("\nList: ");
					{
						System.out.print(list.get(i)+"\t");	
					}*/
					for(String s:list)
					{
						System.out.println(s+" ");
					}
					System.out.println();
					break;
				case 5: System.out.print("\nEnter the letter ");
					char l=scan.next().charAt(0);
					for(i=0;i<list.size();i++)
					{
						if(list.get(i).charAt(0)==l)
						{
							System.out.println(list.get(i));
						}
					}
					break;
				case 6: System.out.print("\nEnter the substring ");
					String sub=scan.nextLine();
					/*for(i=0;i<list.size();i++)
					{
						if(list.get(i).contains(sub))
						{
							System.out.println(list.get(i));
						}
					}*/
					for(String s:list)
					{
						if(s.contains(sub))
						{
							System.out.println(s);
						}
					}
					break;
				case 7: Collections.sort(list);
					break;
				case 8: System.out.print("\nEnter the value to remove ");
					list.remove(scan.nextLine());
					break;
				case 9: System.out.print("\nEnter String to be replaced: ");
				        str=scan.nextLine();
					System.out.print("Enter replacement: ");
					String rstr=scan.nextLine();
					/*for(i=0;i<list.size();i++)
					{
						if(list.get(i).equals(str))
						{
							list.set(i,rstr);
							break;
						}
					}*/
					for(String s:list)
					{
						if(s.equals(str))
						{
							list.set(list.indexOf(s),rstr);
						}
					}
					break;
				case 10:System.out.println("\nList withour Duplicates:");
        /*ArrayList<String> newList = new ArrayList<String>();
  
        // Traverse through the first list
        for (String element : list) {
  
            // If this element is not present in newList
            // then add it
            if (!newList.contains(element)) {					
  
                newList.add(element);
            }
        }
        System.out.println(newList);*/
        				/*for(int j=0;j<list.size();j++)
        				{
        					for(i=j+1;i<list.size();i++)
        					{
        						if(list.get(j)==list.get(i))
        							list.remove(i--);
        					}
        				}*/
        				Set<String> slist=new HashSet<String>(list);
        				list.clear();
        				list.addAll(slist);
					break;
          case 11: list.clear();
                    break;
          case 12:break;
          default: System.out.print("\nINVALID CHOICE!!");
			}
			//ch=11;
      if(ch!=4&&ch!=12)
			{
        System.out.println("\nList: "+list);
      }
    }while(ch!=12);
	}
}

