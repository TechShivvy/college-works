class GenericMax
{
  public static <T extends Comparable> void maximum(T a[])
  { 
  	T max=a[0];
    	for(int i=1;i<a.length;i++)
      	{
      		if(max.compareTo(a[i])<0)
        		max=a[i];
        }
    	System.out.println("Max: "+max);      
  }
}


class MaxVal
{
  public static void main(String arg[])
  {
      int ch=1;
      while(ch!=4)
      {
	      switch(ch)
		{
		  case 1:
		  	  Integer ai[]=new Integer[]{1,2,3,0,-1,7,3,5};
		  	  System.out.print("Integer: [1,2,3,0,-1,7,3,5]\n");
		  	  // System.out.println(ai);
		   	  GenericMax.maximum(ai);
		   	  break;
		  case 2: Float af[]=  new Float[]{1.2f,1.3f,1.4f,1.33f,1f,1.5f,1.43f};
		   	  System.out.println("Float: [1.2,1.3,1.4,1.33,1,1.5,1.43]");
		          GenericMax.maximum(af);
		   	  break;
		  case 3: Double ad[]= new Double[]{1.2,1.3,1.5,1.4,1.7,1.8,0.0,5.0,1.1};
		   	  System.out.println("Double: [1.2,1.3,1.5,1.4,1.7,1.8,0.0,5.0,1.1]");
		   	  GenericMax.maximum(ad);
		          break; 
		}
		ch++;
	}
  }   
}
