import shapes.*;
import java.util.Scanner;
public class Testpackage{
	public static void main(String args[]){
		int x,b,h,r,choice;
		Scanner read=new Scanner(System.in);
		System.out.println("enter the shape whose area and perimater you need: \n 1. square\n 2. triangle\n 3. circle ");
		choice= read.nextInt();
		if(choice==1){
			System.out.println("enter the side length of the square: ");
			x=read.nextInt();
			System.out.println("the area of the square is " +square.sqarea(x)+ " \nthe perimeter of the square is " +square.sqperimeter(x));
		}  
		if(choice==2){
			System.out.println("enter the base and height of the triangle: ");
			b=read.nextInt();
			h=read.nextInt();
			System.out.println("the area of the triangle is " +triangle.triarea(b,h)+ " \nthe perimeter of the triangle is " +triangle.triperimeter(b));
		}
		if(choice==3){
			System.out.println("enter the radius of the circle: ");
			r=read.nextInt();
			System.out.println("the area of the circle is " +circle.carea(r)+ " \nthe perimeter of the circle is " +circle.cperimeter(r));
		}
	}
}
