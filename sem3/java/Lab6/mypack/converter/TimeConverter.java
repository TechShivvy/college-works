package mypack.converter;
public class TimeConverter{
	public static double MtoH(double minute){
		return minute*0.0166;
	}
	public static double StoM(double second){
		return second*0.0166;
	}
	public static double MtoS(double minute){
		return minute*60;
	}
	public static double HtoM(double hour){
		return hour*60;
	}
}

