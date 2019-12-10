package tcp;

import java.io.IOException;

public class MainTest
{
    public static void main(String[] _argv) throws IOException
    {
        IEnvService service = new ClientService(5555, "127.0.0.1");

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
    }
}
