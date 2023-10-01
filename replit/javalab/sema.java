import java.util.concurrent.Semaphore;

class SharedQueue {
  int item;

  static Semaphore semCon = new Semaphore(0);
  static Semaphore semProd = new Semaphore(1);

  void get() {
    try {
      semCon.acquire();
    } catch (InterruptedException e) {
      System.out.println("Thread panicked");
    }
    
    System.out.println("Consumed " + item);
    
    semProd.release();
  }

  void put(int item) {
    try {
      semProd.acquire();
    } catch (InterruptedException e) {
      System.out.println("Thread panicked");
    }

    this.item = item;
    System.out.println("Produced " + item);
    
    semCon.release();
  }
}

class Producer implements Runnable {
  SharedQueue q;

  Producer(SharedQueue q) {
    this.q = q;
    new Thread(this, "Producer").start();
  }

  public void run() {
    for (int i = 0; i < 10; i++)
      q.put((int)(Math.random() * 100));
  }
}

class Consumer implements Runnable {
  SharedQueue q;

  Consumer(SharedQueue q) {
    this.q = q;
    new Thread(this, "Consumer").start();
  }

  public void run() {
    for (int i = 0; i < 10; i++)
      q.get();
  }
}

class sema {
  public static void main(String args[]) {
    SharedQueue q = new SharedQueue();
    
    new Consumer(q);
    new Producer(q);
  }
}

/* 
Cooperation synchronization - Between producer & cosumer threads
Competitive synchronization - Between threads of same type
*/