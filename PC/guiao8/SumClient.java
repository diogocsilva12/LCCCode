import java.io.*;
import java.net.*;
import java.util.Scanner;

public class SumClient {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 8000);
            
            // Set up input from server
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            
            // Set up output to server
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            
            // Set up input from user
            Scanner scanner = new Scanner(System.in);
            
            System.out.println("Connected to server. Enter integers (one per line):");
            System.out.println("Press Ctrl+D (Unix) or Ctrl+Z (Windows) followed by Enter to quit");
            
            // Read numbers from user and send to server
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                if (line.isEmpty()) continue;
                
                out.println(line);
                String response = in.readLine();
                System.out.println("Server response: " + response);
            }
            
            // Signal end of input
            socket.shutdownOutput();
            
            // Read final average from server
            String finalResponse = in.readLine();
            System.out.println("Final response: " + finalResponse);
            
            // Close resources
            scanner.close();
            in.close();
            out.close();
            socket.close();
            
        } catch (IOException e) {
            System.err.println("Error in client: " + e.getMessage());
            e.printStackTrace();
        }
    }
}