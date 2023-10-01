import java.util.*;
interface Shape
{
  String color=new String("red");
  /*Shape()
  {
    color="red";
  }
  Shape(String col)
  {
    color=col;
  }
  String getColor()
  {
    return color;
  }
  void setColor(String col)
  {
    color=col;
  }*/
  
  abstract float getRadius();
  abstract float getLength();
  abstract float getWidth();
  abstract float getSide();

  abstract void setRadius(float r);
  abstract void setLength(float l);
  abstract void setWidth(float w);
  abstract void setSide(float s);
  abstract float getArea();
  abstract float getPerimeter();
}
class Circle implements Shape
{
  protected float radius;
  Circle()
  {
    radius=1.0f;
  }
  Circle(float r)
  {
    radius=r;
  }
  Circle(float r,String col)
  {
    color=col;
    radius=r;
  }
  float getRadius()
  {
    return radius;
  }
  void setRadius(float r)
  {
    radius=r;
  }
  float getArea()
  {
    return (float)Math.PI*radius*radius;
  }
  float getPerimeter()
  {
    return (float)Math.PI*radius*2f;
  }
}
class Rectangle implements Shape
{
  protected float width,length;
  Rectangle()
  {
    width=1.0f;
    length=1.0f;
  }
  Rectangle(float w,float l)
  {
    width=w;
    length=l;
  }
  Rectangle(float w,float l,String col)
  {
    color=col;
    width=w;
    length=l;
  }
  float getWidth()
  {
    return width;
  }
  void setWidth(float w)
  {
    width=w;
  }
  float getLength()
  {
    return length;
  }
  void setlength(float l)
  {
    length=l;
  }
  float getArea()
  {
    return length*width;
  }
  float getPerimeter()
  {
    return 2*(length+width);
  }
}
class Square extends Rectangle
{
  Square()
  {
    super();
  }
  Square(float side)
  {
    length=width=side;
  }
  Square(float side,String col)
  {
    length=width=side;
    color=col;
  }
  float getSide()
  {
    return length;
  }
  void setSide(float side)
  {
    length=width=side;
  }
}
class TestShape
{
  public static void main(String[] args)
  {
    Scanner scan=new Scanner(System.in);
    Shape[] s=new Shape[3];
    s[0]=new Circle();
    s[1]=new Rectangle(2,5);
    s[2]=new Square(10,"black");
    for(int i=0;i<3;i++)
    { System.out.println("\nDeafult:");
      if(i==0)
      {
        System.out.println("\nCircle:\n");
        System.out.println("Radius:\t"+((Circle)s[0]).getRadius());
      }
      else if(i==1)
      {
        System.out.println("\nRectangle:\n");
        System.out.println("Length:\t"+s[1].getLength());
        System.out.println("Width:\t"+s[1].getWidth());
      } 
      else
      {
        System.out.println("\nSquare:\n");
        System.out.println("Side:\t"+s[2].getSide());
      }
      System.out.println("Color:\t"+s[i].getColor());
      System.out.println("Area:\t"+s[i].getArea());
      System.out.println("Perimeter:\t"+s[i].getPerimeter());
    }
    for(int i=0;i<3;i++)
    { 
      System.out.println("\nUpdation:");
      if(i==0)
      {
        System.out.println("\nCircle:\n");
        System.out.print("Enter new Radius: ");
        s[0].setRadius(scan.nextFloat());
        scan.nextLine();
        System.out.print("Enter new Color: ");
        s[0].setColor(scan.nextLine());
        System.out.println("\nRadius:\t"+s[0].getRadius());
      }
      else if(i==1)
      {
        System.out.println("\nRectangle:\n");
        System.out.print("Enter new Length: ");
        s[1].setLength(scan.nextFloat());
        scan.nextLine();
        System.out.print("Enter new Width: ");
        s[1].setWidth(scan.nextFloat());
        scan.nextLine();
        System.out.print("Enter new Color: ");
        s[1].setColor(scan.nextLine());
        System.out.println("\nLength:\t"+s[1].getLength());
        System.out.println("Width:\t"+s[1].getWidth());
      } 
      else
      {
        System.out.println("\nSquare:\n");
        System.out.print("Enter new Side: ");
        s[2].setSide(scan.nextFloat());
        scan.nextLine();
        System.out.print("Enter new Color: ");
        s[2].setColor(scan.nextLine());
        System.out.println("\nSide:\t"+s[2].getSide());
      }
      System.out.println("Color:\t"+s[i].getColor());
      System.out.println("Area:\t"+s[i].getArea());
      System.out.println("Perimeter:\t"+s[i].getPerimeter());
    }
  }
}
