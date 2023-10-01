package shapes;
public class triangle{
  double s1,s2,s3;
	double triarea(){
    double S = (s1 + s2 + s3)/2;
    return Math.sqrt(S * (S - s1) * (S - s2) * (S - s3));
	}
	double triperimeter(){
		return (s1+s2+s3);
	}
}

		
