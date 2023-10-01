import java.util.*;
class Person
{
  private int aadhar;
  private String name;
  private String address;
  private char gender;            
  public Person(int aadh,String NAME,String ADD,char gen)
  {
    aadhar=aadh;
    name=NAME;
    address=ADD;
    gender=gen;
  }
  public String getName()
  {
    return name;
  }
  public String getAddress()
  {
    return address;
  }
  public void setAddress(String ADD)
  {
    address=ADD;
  }
  public char getGender()
  {
    return gender;                            
  }
}
class Student extends Person{
  private String program;
  private int year;
  private float totalmark;
  public Student(int aadh,String NAME,String ADD,char gen,String prog,int yr,float total)
  {
    super(aadh, NAME, ADD, gen);
    program=prog;
    year=yr;
    totalmark=total;
  }
  public String getProgram()
  {
    return program;
  }
  public int getYear()
  {
    return year;
  }
  public float getTotal()
  {
    return totalmark;
  }
  public void setYear(int yr)
  {
    year=yr;                                  
  }
  public void setTotal(float tot)
  {
    totalmark=tot;
  }
  public float calGPA()
  {
    return totalmark/10;
  }
}
class Faculty extends Person
{
  private String dept;
  private String desig;
  private float basicpay;
  Faculty(int aadh,String NAME,String ADD,char gen,String designation,String Dept,float pay)
  {
    super(aadh, NAME, ADD, gen);
    desig=designation;
    dept=Dept;
    basicpay=pay;
  }
  public String getDesig()
  {
    return desig;
  }
  public void setDesig(String Desig)
  {
    desig=Desig;
  }
  public void setBasic(float pay)
  {
    basicpay=pay;
  }              
  public float getBasic()
  {
    return basicpay;
  }   
  public float calSalary()
  {
    return 1.535f*basicpay;
  }            
}  
class TestInheritance
{
  public static void main(String[] args)
  {
    Scanner scan=new Scanner(System.in);
    int adar,ch;
    String name,add;
    char g;
    System.out.print("\n1.Student\n2.Faculty\nEnter your choice(1,2): ");
    ch=scan.nextInt(); System.out.println("\n>>>>>>>>> GENERAL <<<<<<<<<\n");
    System.out.print("Enter aadhar ID: ");
    adar=scan.nextInt();scan.nextLine();
    System.out.print("Enter Name: ");
    name=scan.nextLine();
    System.out.print("Enter Add: ");
    add=scan.nextLine();
    System.out.print("Enter Gender: ");
    g=scan.nextLine().charAt(0);
    switch(ch)
    {
      case 1: System.out.println("\n>>>>>>>>> STUDENT <<<<<<<<<\n");
              System.out.print("Enter Program: ");
              String program=scan.nextLine();
              System.out.print("Enter year: ");
              int year=scan.nextInt();
              System.out.print("Enter Total: ");
              float total=scan.nextFloat();
              scan.nextLine();
              Student s=new Student(adar,name,add,g,program,year,total);
              System.out.println("\nName:\t"+s.getName() +"\nAdd:\t"+s.getAddress()+"\nGender:\t"+s.getGender()+"\nProgram:"+s.getProgram()+"\nYear:\t"+s.getYear()+"\nTotal:\t"+s.getTotal()+"\nCGPA:\t"+s.calGPA());
              System.out.print("\nEnter New Add:");
              add=scan.nextLine();
              s.setAddress(add);
              System.out.print("Enter new year: ");
              year=scan.nextInt();
              s.setYear(year);
              System.out.print("Enter new total: ");
              total=scan.nextFloat();
              s.setTotal(total);
              scan.nextLine();
              System.out.println("\nUpdated:\n\nName:\t"+s.getName() +"\nAdd:\t"+s.getAddress()+"\nGender:\t"+s.getGender()+"\nProgram:"+s.getProgram()+"\nYear:\t"+s.getYear()+"\nTotal:\t"+s.getTotal()+"\nCGPA:\t"+s.calGPA());
              break;
      case 2: System.out.println("\n>>>>>>>>> FACULTY <<<<<<<<<\n");
              System.out.print("Enter Desig: ");
              String designation=scan.nextLine();
              System.out.print("Enter Dept: ");
              String dept=scan.nextLine(); 
              System.out.print("Enter Basic Pay: ");
              float pay=scan.nextFloat();
              scan.nextLine(); 
              Faculty f=new Faculty(adar,name,add,g,designation,dept,pay);    
              System.out.println("\nName:\t"+f.getName() +"\nAdd:\t"+f.getAddress()+"\nGender:\t"+f.getGender()+"\nDesig:\t"+f.getDesig()+"\nB Pay:\t"+f.getBasic()+"\nSalary:\t"+f.calSalary());
              System.out.print("\nEnter New Add: ");
              add=scan.nextLine();
              f.setAddress(add);
              System.out.print("Enter new Desig: ");
              designation=scan.nextLine();
              f.setDesig(designation);
              System.out.print("Enter new basic Pay: ");
              pay=scan.nextFloat();
              f.setBasic(pay);
              System.out.println("\nUpdated:\n\nName:\t"+f.getName() +"\nAdd:\t"+f.getAddress()+"\nGender:\t"+f.getGender()+"\nDesig:\t"+f.getDesig()+"\nB Pay:\t"+f.getBasic()+"\nSalary:\t"+f.calSalary());
              break;
      default:System.out.println("\nInvalid Input!\n");
    }
  }
}