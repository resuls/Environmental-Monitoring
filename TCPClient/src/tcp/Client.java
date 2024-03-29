package tcp;

import java.io.*;
import java.net.ConnectException;
import java.net.Socket;

public class Client
{
    public static void main(String[] _args) throws IOException
    {
        final String host = "127.0.0.1";
        final int portNumber = 5555;
        System.out.println("Creating socket to '" + host + "' on port " + portNumber);
        Socket socket = null;

        try
        {
            socket = new Socket(host, portNumber);
        }
        catch (ConnectException e)
        {
            System.out.println(e.getMessage());
            return;
        }

        while (true)
        {
            System.out.print("Message: ");
            BufferedReader inputBR = new BufferedReader(new InputStreamReader(System.in));
            String input = inputBR.readLine();

            if ("exit".equalsIgnoreCase(input))
            {
                socket.close();
                break;
            }

            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            out.println(input);

            BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            System.out.println(br.readLine());
        }
    }
}
