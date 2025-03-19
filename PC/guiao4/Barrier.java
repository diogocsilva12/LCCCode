public class Barrier {
    private final int n;
    private int count = 0;
    private final Object lock = new Object();

    public Barrier(int n) {
        if (n <= 0) throw new IllegalArgumentException("N deve ser positivo");
        this.n = n;
    }

    public void await() throws InterruptedException {
        synchronized (lock) {
            count++;
            
            if (count < n) {
                // Esta thread não é a última, então deve esperar
                lock.wait();
            } else {
                // Esta é a última thread, notifica todas as outras
                lock.notifyAll();
            }
        }
    }
}



