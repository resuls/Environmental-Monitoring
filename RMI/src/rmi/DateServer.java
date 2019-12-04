package rmi;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Date;

public class DateServer extends UnicastRemoteObject implements IRemoteDate
{
    public DateServer() throws RemoteException
    {
        super();
    }

    public static void main(String[] _args)
    {
        try
        {
            DateServer ds = new DateServer();
            Registry reg = LocateRegistry.createRegistry(Registry.REGISTRY_PORT);
            reg.rebind("DateService", ds);
            reg.rebind("saySomething", ds);

            System.out.println("Server is waiting for queries...");
        } catch (Exception _e)
        {
            _e.printStackTrace();
        }
    }

    public Date catchDate()
    {
        return new Date();
    }

    @Override
    public void saySomething() throws RemoteException
    {
        System.out.println("Cookies!");
    }
}