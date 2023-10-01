import java.util.*;
class Stack<E>
{
	 int top;
	 E []data;
	 public Stack (E []arr)
	 { 
	 	data=arr; 
	 }
	 boolean isFull()
	 {
		 if(top==data.length)
		 	return true;
		 else
		 	return false;
	 }
	 boolean isEmpty()
	 {
		 if (top==0)
		 	return true;
		 else
		 	return false;
	 }
	 void push(E element)
	 {
		 if(isFull()==false)
		 {
			 data[top]=element;
			 top++;
		 }
		 else
			 System.out.println("\nStack Overflow. Cannot push the element "+element);
	 }
	 E pop()
	 {
		 if(isEmpty()==false)
		 	return data[--top];
		 else
		 {
			 System.out.println("\nStack Underflow, cannot pop an element");
			 return null;
		 }
	 }
	 void disp()
  	 {
    		if(isEmpty())
		      System.out.print("\nStack empty!");
    		else
    		{
		      int i = top-1;
		      System.out.print("\nStack: ");
		      //System.out.print("top->");
		      while(i >= 0)
		      {
				System.out.print(data[i] + " ");
				i--;
		      }
		}
 	 }
} 

class stack
{
	 public static void main(String[] args)
	 {
	 	 System.out.println("Float: ");
		 Float []a=new Float[4];
		 Stack<Float> sf=new Stack<Float>(a);
		 sf.push(4f); 
		 sf.disp();
		 sf.push(5f); 
		 sf.push(6f);
		 sf.push(10f);
		 sf.disp();
		 sf.push(69f);
		 System.out.println("Popped element is "+sf.pop()); 
		 System.out.println("Popped element is "+sf.pop()); 
		 System.out.println("Popped element is "+sf.pop()); 
		 sf.disp();
		 System.out.println("Popped element is "+sf.pop()); 
		 System.out.println("Popped element is "+sf.pop()); 
		 
		 System.out.println("\n\nInteger: ");
		 Integer []b=new Integer[2];
		 Stack<Integer> si=new Stack<Integer>(b);
		 si.push(1); 
		 si.disp();
		 si.push(3); 
		 si.disp();
		 si.push(5);
		 si.disp();
		 //ls.push(10f);
		 //ls.disp();
		 //ls.push(69f);
		 System.out.println("Popped element is "+si.pop()); 
		 System.out.println("Popped element is "+si.pop()); 
		 System.out.println("Popped element is "+si.pop()); 
		 //System.out.println("Popped element is "+si.pop()); 
		// System.out.println("Popped element is "+si.pop()); 
		 
		 System.out.println("\n\nDouble: ");
		 Double []c=new Double[4];
		 Stack<Double> sd=new Stack<Double>(c);
		 sd.push(8.0); 
		 sd.disp();
		 sd.push(5.5); 
		 sd.push(6.4);
		 sd.push(10.1);
		 sd.disp();
		 sd.push(69.69);
		 System.out.println("Popped element is "+sd.pop()); 
		 System.out.println("Popped element is "+sd.pop()); 
		 System.out.println("Popped element is "+sd.pop()); 
		 sd.disp();
		 System.out.println("Popped element is "+sd.pop()); 
		 System.out.println("Popped element is "+sd.pop()); 
		 
		 
		 
	 }
}
