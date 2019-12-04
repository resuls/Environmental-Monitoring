package rmi;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class EnvDataManClient
{
    public static void main(String[] _args)
    {
        try
        {
            String adr = "envMan";
            Registry reg = LocateRegistry.getRegistry();
            IEnvService service = (IEnvService) reg.lookup(adr);

            while (true)
            {
                String[] mSensors = service.requestEnvironmentDataTypes();
                for (String sensor : mSensors)
                {
                    EnvironmentData dataO = service.requestEnvironmentData(sensor);
                    System.out.print(dataO);
                    System.out.println();
                    System.out.println("*****************************");
                }

                System.out.println();
                System.out.println();
                EnvironmentData[] dataOs = service.requestAll();

                for (EnvironmentData dataO : dataOs)
                {
                    System.out.println(dataO);
                }

                System.out.println("*****************************");

                try
                {
                    Thread.sleep(1000);
                } catch (Exception _e)
                {
                    _e.printStackTrace();
                }
            }
        } catch (Exception _e)
        {
            _e.printStackTrace();
        }
    }
}
