import shapes.*;
import java.util.Scanner;
class TestPackage
{
	public static void main(String args[])
	{
		double a,r,s1,s2,s3;
		int ch;
		Scanner scan=new Scanner(System.in);
		do
		{
			System.out.print("\nChoose the shape:\n1.Square\n2.Triangle\n3.Circle\n4.Exit\nChoice: ");
			ch= scan.nextInt();
			if(ch==1){
				System.out.print("\nEnter the side length of the square: ");
				a=scan.nextDouble();
				System.out.println("\nArea of the square: " +square.area(a)+ " \nPerimeter of the square: " +square.pm(a));
			}  
			if(ch==2){
				System.out.print("\nEnter the 3 sides of the triangle: ");
				s1=scan.nextDouble();
				s2=scan.nextDouble();
				s3=scan.nextDouble();
				System.out.println("\nArea of the triangle: " +triangle.area(s1,s2,s3)+ " \nPerimeter of the triangle: " +triangle.pm(s1,s2,s3));
			}
			if(ch==3){
				System.out.print("\nEnter the radius of the circle: ");
				r=scan.nextDouble();
				System.out.println("\nArea of the circle: " +circle.area(r)+ " \nCircumference of the circle: " +circle.circum(r));
		}
		}while(ch!=4);
	}
	
}
