import java.util.concurrent.locks.*;
import java.util.concurrent.locks.ReentrantLock;
import java.util.LinkedList;
import java.util.Queue;
import java.lang.Thread;

public class exercise2 {
    public static Lock lock = new ReentrantLock();
    public static Condition threadcond = lock.newCondition();
    public static Condition full = lock.newCondition();
    public static Condition empty = lock.newCondition();
    public static int product = 0;
    
    public static void main(String[] args){
        getproduct a = new getproduct();
        setproduct b = new setproduct();
        getproduct c = new getproduct();
        setproduct d = new setproduct();
        Thread consume = new Thread(a);
        Thread produce = new Thread(b);
        Thread consume2 = new Thread(c);
        Thread produce2 = new Thread(d);
        produce.start();
        consume.start();
        consume2.start();
        produce2.start();
        try {
            consume.join();
            produce.join();
            consume2.join();
            produce2.join();
        } catch(InterruptedException e) {}
    }

    static class setproduct implements Runnable {
        public void run() {
            lock.lock();
            try {
                for(int i = 0; i < 10; i++) {
                    while(product==10) {
                        try {
                            System.out.println("full");
                            empty.await();
                        } catch(InterruptedException e) {e.printStackTrace();}
                    }
                    product++;
                    System.out.println("producer: "+product);
                    full.signal();
                }
            }
            finally {
                lock.unlock();
            }
        }
    }

    static class getproduct implements Runnable {
        public void run() {
            lock.lock();
            try {
                for(int i = 0; i < 10; i++) {
                    while(product==0) {
                        try {
                            System.out.println("empty");
                            full.await();
                        } catch(InterruptedException e) {e.printStackTrace();}
                    }
                    product--;
                    System.out.println("consumer: "+product);
                    empty.signal();
                }
            }
            finally {
                lock.unlock();
            }
        }
    }
}

