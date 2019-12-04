package rmi;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Date;

public class DateClient
{
    public static void main(String[] _args)
    {
        try
        {
            String adr = "DateService";
            Registry reg = LocateRegistry.getRegistry();
            IRemoteDate dateObject = (IRemoteDate) reg.lookup(adr);
            Date date = dateObject.catchDate();

            IRemoteDate stub = (IRemoteDate) reg.lookup("saySomething");
            stub.saySomething();

            System.out.println("The server date is: " + date);
        } catch (Exception _e)
        {
            _e.printStackTrace();
        }
    }
}
