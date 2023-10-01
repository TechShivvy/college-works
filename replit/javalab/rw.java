import java.time.*;
import java.util.*;

class SharedData {
  static String buffer = "Hello world";
  static int readers = 0;
  static int writers = 0;

  public static void read(int id) {
    Instant start = Instant.now();
    while (writers == 1) {
    }
    ;
    readers++;
    System.out.println("[R" + id + "]: Read '" + buffer + "' after waiting for "
        + Duration.between(start, Instant.now()).toMillis() + " ms.");
    readers--;
  }

  public static void write(int id) {
    Instant start = Instant.now();
    while (readers > 0 || writers > 0) {
    }
    ;
    writers++;
    String newBuffer = genString();
    buffer = newBuffer;
    System.out.println("[W" + id + "]: Wrote '" + newBuffer + "' after waiting for "
        + Duration.between(start, Instant.now()).toMillis() + " ms.");
    writers--;
  }

  private static String genString() {
    int leftLimit = 97; // letter 'a'
    int rightLimit = 122; // letter 'z'
    int l = 10;
    Random random = new Random();
    StringBuilder buffer = new StringBuilder(l);

    for (int i = 0; i < l; i++) {
      int randomLimitedInt = leftLimit + (int) (random.nextFloat() * (rightLimit - leftLimit + 1));
      buffer.append((char) randomLimitedInt);
    }

    return buffer.toString();
  }
}

class Runner implements Runnable {
  int id;
  int mode;

  Runner(int id, int mode) {
    this.id = id;
    this.mode = mode;
  }

  public void run() {
    try {
      Thread.sleep((long) (Math.random() * 100));

      if (this.mode > 0)
        SharedData.read(this.id);
      else
        SharedData.write(this.id);
    } catch (InterruptedException e) {
      System.out.println("Thread " + this.id + " panicked.");
    }

  }
}

public class rw {
  public static void main(String[] args) {
    int[] rw = { -1, 1, 1, 1, -1, -1, 1, 1, -1, 1, 1, 1, -1, -1, 1, 1, 1, 1, -1, 1, 1 };
    for (int i = 0; i < rw.length; i++) {
      Runnable r = new Runner(i, rw[i]);
      new Thread(r).start();
    }
  }
}