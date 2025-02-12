



class Printer extends Thread{
    int I;
    Printer(int I){
        this.I = I;
    }
    public void run(){
        for(int i = 0; i < I; i++){
            System.out.println(i);
        }
    }
}

public class prog1 {
    public static void main(String[] args) throws InterruptedException{
        int N = Integer.parseInt(args[0]);
        int I = Integer.parseInt(args[1]);


        Thread[] a = new Thread[N];
        for(int i = 0; i < N; i++){
            a[i] = new Printer(I);
            a[i].start();
        }
        for(int i = 0; i < N; i++){
            a[i].join();
        }

        System.out.println("Fim");
        
    }
}
