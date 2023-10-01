import shapes.*;
import java.util.Scanner;
public class Testpackage{
	public static void main(String args[]){
		int choice;
    double r,s,s1,s2,s3;
		Scanner sc=new Scanner(System.in);
		System.out.print("Enter the shape whose area and perimeter you need: \n 1.Square\n 2.Triangle\n 3.Circle ");
		choice= sc.nextInt();
		if(choice==1){
      Square S=new Square(); 
			System.out.print("\nEnter the side length of the square: ");
			S.x=sc.nextDouble();
			System.out.print("\nArea of the square is " +S.sqarea()+ " \nPerimeter of the square is " +S.sqperimeter());
		}  
		if(choice==2){
			System.out.print("\nEnter the sides of the triangle: ");
      triangle t=new triangle();
			t.s1=sc.nextDouble();
      t.s2=sc.nextDouble();
      t.s3=sc.nextDouble();
			System.out.print("\nArea of the triangle is " +t.triarea()+ " \nPerimeter of the triangle is " +t.triperimeter());
		}
		if(choice==3){
			System.out.print("\nEnter the radius of the circle: ");
      circle c=new circle();
			c.r=sc.nextDouble();
			System.out.print("\nArea of the circle is " +c.carea()+ " \nPerimeter of the circle is " +c.cperimeter());
		}
	}
}
