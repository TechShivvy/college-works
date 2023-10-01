import java.util.*;
interface Student
{
	public float[] getMarks();
 	public float calcGPA();
}
abstract class Person
{
  private String name;
  private String address;          
  public Person(String NAME,String ADD)
  {
    name=NAME;
    address=ADD;
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
}
abstract class Employee extends Person
{
	private String empid;
	private String dept;
	private int basic;
	public Employee(String NAME,String ADD,String empid,String dept,int basic)
	{
		super(NAME,ADD);
		this.empid=empid;
		this.dept=dept;
		this.basic=basic;		
	}
	public String getEmpid()
	{
		return empid;
	}
	public String getDept()
	{
		return dept;
	}
	public void setDept(String dept)
	{
		this.dept=dept;
	}
	public int getBasic()
	{
		return basic;				
		 
	}
	public void setBasic(int basic)
	{
		this.basic=basic;
	}
	public float calSalary()
 	{
    		return 1.535f*basic;
  	}  
}

class Faculty extends Employee
{
  private String course;
  private String desig;
  Faculty(String NAME,String ADD,String empid,String dept,int basic,String desgn,String course)
  {
    super(NAME,ADD,empid,dept,basic);
    desig=desgn;								
    this.course=course;
  }
  public String getDesig()
  {
    return desig;
  }
  public void setDesig(String Desig)
  {
    desig=Desig;
  }
  public String getCourse()
  {
    return course;
  }
  public void setCourse(String course)
  {
    this.course=course;
  }
  public float calSalary()
  {
    return 1.535f*getBasic();
  }            
}
class TeachingAssistant extends Employee implements Student
{
	private String project;
	private String course;
	private float[] marks=new float[10];
	TeachingAssistant(String NAME,String ADD,String empid,String dept,int basic,String project,String course,float[] marks)
	{
		super(NAME,ADD,empid,dept,basic);
		this.course=course;
		this.project=project;
		/*for(int i=0;i<5;i++)
		{
			this.marks[i]=marks[i];
		}*/
		this.marks=marks;
	}
	public String getCourse()
  	{
    		return course;
 	}
  	public void setCourse(String course)
  	{
   		this.course=course;
  	}
	public String getProject()
  	{
    		return project;
 	}
 	public float[] getMarks()
 	{
 		return marks;
 	}
 	public float calcGPA()
 	{
 		float sum=0;
		for(int i=0;i<marks.length;i++)
		{
			sum+=(marks[i]/10);
		}
		return sum;														
 	}
}
class TestInheritance
{
  public static void main(String[] args)
  {
    Scanner scan=new Scanner(System.in);
    String name,add,empid,dept,desig,course,proj;
    int basic;
    float[] marks= new float[3];
    int ch=1;
    switch(ch)
    {
      case 1: System.out.println("\n>>>>>>>>> FACULTY <<<<<<<<<\n");
              
              System.out.print("Enter Name: ");
	      name=scan.nextLine();
	      System.out.print("Enter Add: ");
	      add=scan.nextLine();
	      System.out.print("Enter Empid: ");
	      empid=scan.nextLine();
	      System.out.print("Enter Dept: ");
	      dept=scan.nextLine();
	      System.out.print("Enter basic: ");
	      basic=scan.nextInt();
	      scan.nextLine();
              System.out.print("Enter desig: ");
    	      desig=scan.nextLine();
	      System.out.print("Enter course: ");
	      course=scan.nextLine();
              Faculty f=new Faculty(name,add,empid,dept,basic,desig,course);
              System.out.println("\nName:\t"+f.getName() +"\nAdd:\t"+f.getAddress()+"\nEmpid:\t"+f.getEmpid()+"\nDept:\t"+f.getDept()+"\nSalary:\t"+f.calSalary()+"\ndesig:\t"+f.getDesig()+"\nCourse:\t"+f.getCourse());
              System.out.print("\nEnter New Add: ");
              add=scan.nextLine();
              f.setAddress(add);
              System.out.print("Enter new Course: ");
              course=scan.nextLine();
              f.setCourse(course);
              System.out.print("Enter new Dept: ");
              dept=scan.nextLine(); 
              f.setDept(dept);
              System.out.print("Enter new Desig: ");
              desig=scan.nextLine();
              f.setDesig(desig);
              System.out.print("Enter new basic Pay: ");
              basic=scan.nextInt();
              f.setBasic(basic);
              scan.nextLine();	
              System.out.println("\nUpdated:\n\n\nName:\t"+f.getName() +"\nAdd:\t"+f.getAddress()+"\nEmpid:\t"+f.getEmpid()+"\nDept:\t"+f.getDept()+"\nSalary:\t"+f.calSalary()+"\ndesig:\t"+f.getDesig()+"\nCourse:\t"+f.getCourse());
      case 2:  System.out.println("\n\n>>>>>>>>> TEACH ASSIGN <<<<<<<<<\n");
	       System.out.print("Enter Name: ");
	       name=scan.nextLine();
	       System.out.print("Enter Add: ");
	       add=scan.nextLine();
	       System.out.print("Enter Empid: ");
	       empid=scan.nextLine();
	       System.out.print("Enter Dept: ");
	       dept=scan.nextLine();
	       System.out.print("Enter basic: ");
	       basic=scan.nextInt();
	       scan.nextLine();
      	       System.out.print("Enter course: ");
	       course=scan.nextLine();
      	       System.out.print("Enter proj: ");
	       proj=scan.nextLine();
	       for(int i=0;i<3;i++)
    	       {
    	      		System.out.print("Enter mark"+(i+1)+": ");
    	      		marks[i]=scan.nextFloat();
	       }
              TeachingAssistant t=new TeachingAssistant(name,add,empid,dept,basic,proj,course,marks);  
              System.out.println("\nName:\t"+t.getName() +"\nAdd:\t"+t.getAddress()+"\nEmpid:\t"+t.getEmpid()+"\nDept:\t"+t.getDept()+"\nSalary:\t"+t.calSalary()+"\nProject:"+t.getProject()+"\nCourse:\t"+t.getCourse()+"\nmarks:\t"+Arrays.toString(t.getMarks())+"\nCGPA:\t"+t.calcGPA());
              scan.nextLine();
              System.out.print("\nEnter New Add: ");
              add=scan.nextLine();
              t.setAddress(add);
              System.out.print("Enter new Course: ");
              course=scan.nextLine();
              t.setCourse(course);
              System.out.print("Enter new Dept: ");
              dept=scan.nextLine(); 
              t.setDept(dept);
              System.out.print("Enter new basic Pay: ");
              basic=scan.nextInt();
              t.setBasic(basic);
              System.out.println("\nUpdated:\n\nName:\t"+t.getName() +"\nAdd:\t"+t.getAddress()+"\nEmpid:\t"+t.getEmpid()+"\nDept:\t"+t.getDept()+"\nSalary:\t"+t.calSalary()+"\nProject:"+t.getProject()+"\nCourse:\t"+t.getCourse()+"\nmarks:\t"+Arrays.toString(t.getMarks())+"\nCGPA:\t"+t.calcGPA());
              break;
      default:System.out.println("\nInvalid Input!\n");
    }
  }
}
