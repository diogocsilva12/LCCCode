class Incrementer  extends Thread{
    int I;
    Counter c;
    Incrementer(int I, Counter c){
        this.I = I;
        this.c = c;
    }

    public void run(){
        for(int i = 0; i < I; i++){
            c.increment();
        }
    }
}

class Counter{
    private int c;
    public synchronized  void increment(){
        c++;
    }
    public synchronized int value(){
        return c;
    }
}

public class prog2 {
    public static void main(String[] args) throws InterruptedException{
        int N = Integer.parseInt(args[0]);
        int I = Integer.parseInt(args[1]);
        Counter c = new Counter();
        Thread[] a = new Thread[N];
        for(int i = 0; i < N; i++){
            a[i] = new Incrementer(I,c);
            a[i].start();
        }
        for(int i = 0; i < N; i++){
            a[i].join();
        }
        System.out.println(c.value());
    }
}

