import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.Random;

public class exampleSort {
    public static void main(String[] args) {
    
        int[] numbers = new int[100];
    
        Random random = new Random();
        for (int i = 0; i < 100; i++) {
            numbers[i] = random.nextInt(100);
        }
        for(int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }
        System.out.println();
    
        // creat fork join object
        mergeSortArray sum = new ForkJoinSort();
        // print result
        sum.sort(numbers);
        for(int i = 0; i < numbers.length; i++) {
            System.out.print(numbers[i] + " ");
        }
        System.out.println();
    }
}
