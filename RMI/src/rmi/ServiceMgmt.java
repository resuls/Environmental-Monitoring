package rmi;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class ServiceMgmt extends UnicastRemoteObject
{
    private static EnvDataManServer server;
    private static Registry reg;

    public ServiceMgmt() throws RemoteException
    {
        super();
        server = new EnvDataManServer();
        reg = LocateRegistry.createRegistry(Registry.REGISTRY_PORT);
    }

    public static void main(String[] _args)
    {
        try
        {
            ServiceMgmt service = new ServiceMgmt();

            Scanner in = new Scanner(System.in);
            int choice;
            do
            {
                printMenu();
                choice = in.nextInt();

                if (choice == 1)
                {
                    start();
                }
                else if (choice == 2)
                {
                    stop();
                }
                else
                {
                    quit();
                }
            } while (true);

        } catch (RemoteException | NotBoundException e)
        {
            e.printStackTrace();
        }
    }

    private static void printMenu()
    {
        System.out.println("1. Start server.");
        System.out.println("2. Stop server.");
        System.out.println("3. Quit.");
        System.out.print("Enter your choice: ");
    }

    private static void start() throws RemoteException
    {
        reg.rebind("envMan", server);
        System.out.println("Server started...");
    }

    private static void stop() throws RemoteException, NotBoundException
    {
        reg.unbind("envMan");
        UnicastRemoteObject.unexportObject(server, true);
        System.out.println("Server stopped...");
    }

    private static void quit()
    {
        System.exit(0);
    }
}
