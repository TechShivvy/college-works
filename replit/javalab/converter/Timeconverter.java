package converter;
public class Timeconverter{
	public static double mtoh(double minute){
		return minute*0.0166;
	}
	public static double stom(double second){
		return second*0.0166;
	}
	public static double mtos(double minute){
		return minute*60;
	}
	public static double htom(double hour){
		return hour*60;
	}
}

