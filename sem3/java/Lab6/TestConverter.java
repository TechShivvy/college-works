import java.util.Scanner;
import mypack.converter.*;
class TestConverter
{
    public static void main(String args[]) 
    {
        double km, m, mile, hr, min, sec;
        int choice;
        Scanner read = new Scanner(System.in);
        System.out.print("Conversions available:\n1.Miles to Kilometers\n2.Kilometer to Meter\n3. Kilometers to Miles\n4.Meter to Kilometer\n5.Hours to Minutes\n6.Minutes to Hours\n7.Seconds to Minutes\n8. Minutes to Seconds\n9.Exit\n");
        do {
            System.out.print("\nEnter your choice:");
            choice = read.nextInt();
            if (choice == 1) {
                System.out.print("\nmiles: ");
                mile = read.nextDouble();
                System.out.println("kilometers: " + DistanceConverter.MtoK(mile));
            }
            if (choice == 2) {
                System.out.print("\nkilometer: ");
                km = read.nextDouble();
                System.out.println("meters: " + DistanceConverter.KtoMe(km));
            }
            if (choice == 3) {
                System.out.print("\nkilometers: ");
                km = read.nextDouble();
                System.out.println("miles: " + DistanceConverter.KtoM(km));
            }
            if (choice == 4) {
                System.out.print("\nmeter: ");
                m = read.nextDouble();
                System.out.println("kilometer: " + DistanceConverter.MetoK(m));
            }
            if (choice == 5) {
                System.out.print("\nhours: ");
                hr = read.nextDouble();
                System.out.println("minutes: " + TimeConverter.HtoM(hr));
            }
            if (choice == 6) {
                System.out.print("\nminutes: ");
                min = read.nextDouble();
                System.out.println("hours; " + TimeConverter.MtoH(min));
            }
            if (choice == 7) {
                System.out.print("\nseconds: ");
                sec = read.nextDouble();
                System.out.println("minutes: " + TimeConverter.StoM(sec));
            }
            if (choice == 8) {
                System.out.print("\nminutes: ");
                min=read.nextDouble();
                System.out.println("seconds: "+TimeConverter.MtoS(min));
            }
        }while(choice<=8);
    }
}
		
		

