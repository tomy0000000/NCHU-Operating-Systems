public class Lab2 implements Runnable {
    
    static int count = 0;

    public void run() {
        for (int i=1; i<=250000; i++) {
            count += 1;
        }

        System.out.println(Thread.currentThread().getName() + ":" + count);
    }

    public static void main(String[] args) {

        Thread threads[] = new Thread[4];

        for (int i=0; i<4; i++) {
            threads[i] = new Thread(new Lab2());
            threads[i].start();
            try {
                threads[i].join();
            } catch (InterruptedException ie) {
                System.err.println(ie);
            }
        }

        // for (int i=0; i<4; i++) {
        // }

        System.out.println("count: " + count);
    }
}

