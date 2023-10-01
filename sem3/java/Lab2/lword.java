import java.util.*;

class lword {
  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    System.out.println("Enter a sentence: ");
    String str = scan.nextLine();
    /*
     * String words[]=str.split(" "); int max=words[0].length(); int
     * ind=0,l,L=words.length; for(int i=1;i<L;i++) { l=words[i].length(); if(l>max)
     * { max=l; ind=i; } }
     */
    str+=" ";
    int ind=0;
    String word="",max="";
    String[] words = new String[100];
    int length=0,L=str.length();
    for(int i=0;i<L;i++) 
    {
      if(str.charAt(i)!=' ')
        word+=str.charAt(i);
      else
      {
        if(!word.equals(""))
        {
          words[length] = word;
          length++;
        }
        word = "";
      }
    }
    max=words[0];
    for(int k=0;k<length;k++)
    {
      if(max.length()<words[k].length())
      {
        max=words[k];
        ind=k;
      }
    }
    System.out.println("\nLongest string is '"+max+ "' , found at index: "+ind);
  }
}