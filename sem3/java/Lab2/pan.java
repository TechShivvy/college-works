import java.util.*;
class pangram{
  public static void main(String[] args) 
  {
    Scanner scan=new Scanner(System.in);
    System.out.print("Enter a sentence: ");
    String str=scan.nextLine();
    int i,j,L=str.length();
    char c;
    //str=str.toLowerCase();
    //String alp="abcdefghijklmnopqrstuvwxyz";
    boolean c_alp[]=new boolean[26];
    for(i=0;i<L;i++)
    {
      c=str.charAt(i);
      if(c>='A' && c<='Z')
        j=c-'A';
      else if(c>='a' && c<='z')
        j=c-'a';
      else
        continue;
      c_alp[j]=true;
    }
    if (pan(c_alp))
      System.out.print("It is a pangram!");
    else
      System.out.print("It is not a pangram");
    /*for(i=65;i<91;i++)
    {
      alp+=(char)i;
    }
    System.out.print(alp);*/
    /*for(i=0;i<26;i++)
    {
      if(str.indexOf(alp.charAt(i))==-1)
      {
        break;
      }    
    }
    if(i==26)
      System.out.print("YES");
    else
      System.out.print("NO");*/
  }
  static boolean pan(boolean arr[])
  {
    for(int i=0;i<26;i++)
    {
      if(!arr[i])
        return false;
    }
    return true;
  }
}