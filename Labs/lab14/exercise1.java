import java.lang.Thread;

public class exercise1 implements Runnable {
    public static int c = 0;
    public static Object a = new Object();
    private boolean inc;

    public exercise1(boolean inc) {
        this.inc = inc;
    }

    public void run(){
        synchronized(a) {
            for(int i = 0;i < 25000000;i++) {
                if (this.inc) {
                    c++;
                } else {
                    c--;
                }
            }
        }
    }

    public static void main(String[] args){
        exercise1 r1 = new exercise1(true);
        Thread t1 = new Thread(r1);
        t1.start();
        exercise1 r2 = new exercise1(true);
        Thread t2 = new Thread(r2);
        t2.start();
        exercise1 r3 = new exercise1(false);
        Thread t3 = new Thread(r3);
        t3.start();
        exercise1 r4 = new exercise1(false);
        Thread t4 = new Thread(r4);
        t4.start();
        try {
            t1.join();
            t2.join();
            t3.join();
            t4.join();
        } catch(InterruptedException e){}
        System.out.println(c);
    }
}
