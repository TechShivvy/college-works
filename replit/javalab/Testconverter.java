import java.util.Scanner;
import converter.*;
class Testconverterpackage {
    public static void main(String args[]) {
        double km, m, mile, hr, min, sec;
        int choice;
        Scanner read = new Scanner(System.in);
        System.out.println("conversions available:\n1. miles to kilometers\n2. kilometer to meter\n3. kilometers to miles\n4. meter to kilometer\n5. hours to minutes\n6. minutes to hours\n7. seconds to minutes\n8. minutes to seconds\n9. convert another value\n10. exit");
        do {
            System.out.println("enter your choice:");
            choice = read.nextInt();
            if (choice == 1) {
                System.out.println("miles: ");
                mile = read.nextDouble();
                System.out.println("kilometers: " + Distanceconverter.mtok(mile));
            }
            if (choice == 2) {
                System.out.println("kilometer: ");
                km = read.nextDouble();
                System.out.println("meters: " + Distanceconverter.ktome(km));
            }
            if (choice == 3) {
                System.out.println("kilometers: ");
                km = read.nextDouble();
                System.out.println("miles: " + Distanceconverter.ktom(km));
            }
            if (choice == 4) {
                System.out.println("meter: ");
                m = read.nextDouble();
                System.out.println("kilometer: " + Distanceconverter.metok(m));
            }
            if (choice == 5) {
                System.out.println("hours: ");
                hr = read.nextDouble();
                System.out.println("minutes: " + Timeconverter.htom(hr));
            }
            if (choice == 6) {
                System.out.println("minutes: ");
                min = read.nextDouble();
                System.out.println("hours; " + Timeconverter.mtoh(min));
            }
            if (choice == 7) {
                System.out.println("seconds: ");
                sec = read.nextDouble();
                System.out.println("minutes: " + Timeconverter.stom(sec));
            }
            if (choice == 8) {
                System.out.println("minutes: ");
                min=read.nextDouble();
                System.out.println("seconds: "+Timeconverter.mtos(min));
            }
        }while(choice<=9);
    }
}
		
		

