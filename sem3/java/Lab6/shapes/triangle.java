package shapes;
public class triangle{
	public static double area(double s1,double s2,double s3)
	{
	    	double S = (s1 + s2 + s3)/2;
	    	return Math.sqrt(S * (S - s1) * (S - s2) * (S - s3));
	}
	public static double pm(double s1,double s2,double s3)
	{
		return (s1+s2+s3);
	}
}

		
