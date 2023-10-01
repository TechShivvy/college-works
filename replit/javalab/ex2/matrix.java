import java.util.*;
class matrix{
  public static void main(String[] args) 
  {
    Scanner scan=new Scanner(System.in);
    System.out.print("Enter the no of rows and cols for matrix 1: ");
    int r1=scan.nextInt();
    int c1=scan.nextInt();
    int A[][]=new int[r1][c1];
    int i,j;
    //System.out.println(r+" "+c);
    System.out.println("Enter the elements: ");
    for(i=0;i<r1;i++)
    {
      for(j=0;j<c1;j++)
      {
        A[i][j]=scan.nextInt();
      }
    }
    display(r1,c1,A);
    System.out.print("Enter the no of rows and cols for matrix 2: ");
    int r2=scan.nextInt();
    int c2=scan.nextInt();
    int B[][]=new int[r2][c2];
    //System.out.println(r+" "+c);
    System.out.println("Enter the elements: ");
    for(i=0;i<r2;i++)
    {
      for(j=0;j<c2;j++)
      {
        B[i][j]=scan.nextInt();
      }
    }
    display(r2,c2,B);
    System.out.println("\nAddition: ");
    if(r1==r2&&c1==c2)
      add(r1,c1,A,B);
    else
      System.out.println("Cant add these!");
    System.out.println("\nSubtraction: ");
    if(r1==r2&&c1==c2)
      sub(r1,c1,A,B);
    else
      System.out.println("Cant sub these!");
    System.out.println("\nMultiplication: ");
    if(c1==r2)
      mul(r1,c1,c2,A,B);
    else
      System.out.print("Cant add these!\n");
  }
  static void add(int r,int c,int A[][], int B[][])
  {
    int C[][]=new int[r][c];
    for(int i=0;i<r;i++)
    {
      for(int j=0;j<c;j++)
      {
        C[i][j]=A[i][j]+B[i][j];
      }
    }
    display(r,c,C);
  }
  static void sub(int r,int c,int A[][], int B[][])
  {
    int C[][]=new int[r][c];
    for(int i=0;i<r;i++)
    {
      for(int j=0;j<c;j++)
      {
        C[i][j]=A[i][j]-B[i][j];
      }
    }
    display(r,c,C);
  }
  static void mul(int r1,int c1,int c2,int A[][], int B[][])
  {
    int C[][]=new int[r1][c2];
    for(int i=0;i<r1;i++)
    {
      for(int j=0;j<c2;j++)
      {
        C[i][j]=0;
        for(int k=0;k<c1;k++)
        {
          C[i][j]+=A[i][k]*B[k][j];
        }
      }
    }
    display(r1,c2,C);
  }
  static void display(int r,int c,int A[][])
  {
    System.out.println("\nMatrix: ");
    for(int i=0;i<r;i++)
    {
      for(int j=0;j<c;j++)
      {
        System.out.print(A[i][j]+"\t");
      }System.out.println("");
    }
    System.out.println("");
  }
}