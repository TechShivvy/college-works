package mypack.converter;
public class DistanceConverter{
	public static double KtoM(double kilometer){
		return kilometer*0.621;
	}
	public static double MtoK(double mile){
		return mile*1.609;
	}
	public static double MetoK(double meter){
		return meter/1000;
	}
	public static double KtoMe(double kilometer){
		return kilometer*1000;
	}
}

