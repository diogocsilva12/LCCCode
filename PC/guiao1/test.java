
class MyThread extends Thread{
    public void run(){
        for(long i = 0; i < 4000000000L; i++);
        System.out.println("Na thread");
    }
}

class MyRunnable implements Runnable {
    public void run(){
        //for(long i = 0; i < 4000000000L; i++);
        try { Thread.sleep(3000); } catch(InterruptedException e){ }
        System.out.println("Na thread");
    }
}

class test{
    public static void main(String[] args) throws InterruptedException {
        MyThread t = new MyThread();
        t.start();
        System.out.println("No main");
        t.join();

        MyRunnable r = new MyRunnable();
        Thread t1 = new Thread(new MyRunnable());
        t1.start();
        System.out.println("No main");
        t1.join();//bloqueia que a thread main espera que a thread t e t1 termine...
    }
}
