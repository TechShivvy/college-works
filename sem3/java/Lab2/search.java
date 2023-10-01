import java.util.*;
class search{
  public static void main(String[] args) {
    System.out.print("\nEnter the no of elements: ");
    Scanner scan=new Scanner(System.in);
    int n=scan.nextInt();
    int a[]=new int[n];
    for(int i=0;i<n;i++)
    {
      System.out.print("Enter a element: ");
      a[i]=scan.nextInt();
    }
    System.out.print("\nEntered array: ");
    display(a,n);
    System.out.print("\nEnter the element to be searched: ");
    int ele=scan.nextInt();
    System.out.println("\nLinear:"); 
    int i=lsearch(a,ele,n);
    if(i!=-1)
      System.out.println("Element is found at index: "+i);
    else
      System.out.println("Element is not there!");
    for (i = 0; i <n; i++)   
    {  
      for (int j = i + 1; j < n; j++)   
      {  
        int tmp = 0;  
        if(a[i]>a[j])   
        {  
          tmp = a[i];  
          a[i] = a[j];  
          a[j] = tmp;  
        }  
      }  
    }
    System.out.print("\nArray after sorting: ");
    display(a,n);
    System.out.println("\nBinary:");  
    bsearch(a,0,n-1,ele);
  }
  static int lsearch(int a[],int x,int n)
  {
    for(int i=0;i<n;i++)
    {
      if(a[i]==x)
        return i;
    }
    return -1;
  }
  static void bsearch(int a[], int first, int last, int key){  
   int mid = (first + last)/2;  
   while( first <= last ){  
      if ( a[mid] < key ){  
        first = mid + 1;     
      }else if ( a[mid] == key ){  
        System.out.println("Element is found at index: " + mid);  
        break;  
      }else{  
         last = mid - 1;  
      }  
      mid = (first + last)/2;  
   }  
   if ( first > last ){  
      System.out.println("Element is not found!");  
   }  
 }
 static void display(int a[],int n)
 {
   for(int i=0;i<n;i++)
   {
     System.out.print(a[i]+" ");
   }
   System.out.println("");
 }  
}