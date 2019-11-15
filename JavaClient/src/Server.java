import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Server
{
    public static void main(String[] args) throws IOException
    {
        final int portNumber = 5555;
        boolean active = true;
        System.out.println("Creating server socket on port " + portNumber);
        ServerSocket serverSocket = new ServerSocket(portNumber);

        System.out.println("Listening...");
        Socket client = serverSocket.accept();

        while (active)
        {
            BufferedReader inputBR = new BufferedReader(new InputStreamReader(client.getInputStream()));
            String message = inputBR.readLine();
            System.out.println("Message: " + message);

            PrintWriter out = new PrintWriter(client.getOutputStream(), true);
            out.println("echo " + message);
        }

        client.close();
        serverSocket.close();
    }
}
