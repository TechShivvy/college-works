import java.util.*;
class palin{
  public static void main(String[] args) 
  {
    Scanner scan=new Scanner(System.in);
    System.out.print("Enter a word: ");
    String str=scan.nextLine();
    int l=str.length(),key=0;
    for(int i=0;i<l/2;i++)
    {
      if(str.charAt(i)!=str.charAt(l-1-i))
      {
        key=1;
        break;
      }
    }
    /*String rev="";
    int l=str.length();
    for(int i=l-1;i>-1;i--)
    {
      rev+=str.charAt(i);
    }
    if(str.equals(rev))
      System.out.println("\nIts a palindrome!");
    else
      System.out.println("\nIts not a palindrome!")*/
    if(key==0)
      System.out.println("\nIts a palindrome!");
    else
      System.out.println("\nIts not a palindrome!");
  }
}