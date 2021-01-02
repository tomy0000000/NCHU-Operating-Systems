import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;
import java.util.Arrays;

public class ForkJoinSort implements mergeSortArray {
    // creat forkjoin pool
    private ForkJoinPool pool;
    
    // write the forkjointask with RecursiveAction
    private class SortTask extends RecursiveAction {
        private static final int THRESHOLD = 4;
        private int[] numbers;
        private int from;
        private int to;
    
        // initialize
        public SortTask(int[] numbers, int from, int to) {
            this.numbers = numbers;
            this.from = from;
            this.to = to;
        }
        
        // write the code to do sum
        @Override
        protected void compute() {
            if ((to - from) < THRESHOLD) {
                Arrays.sort(this.numbers, from, to);
                return;
            }
            int new_mid = (to + from) / 2;
            pool.invoke(new SortTask(this.numbers, from , new_mid));
            pool.invoke(new SortTask(this.numbers, new_mid + 1, to));
            Arrays.sort(numbers, from, to);
        }
    }
    
    // initialize
    public ForkJoinSort() {
        pool = new ForkJoinPool();
    }
    
    // invoke the task to pool
    public void sort(int[] numbers) {
        pool.invoke(new SortTask(numbers, 0, numbers.length));
    }
}
