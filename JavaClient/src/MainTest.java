public class MainTest
{
    public static void main(String[] _argv)
    {
        IEnvService service = new ClientService(5555, "127.0.0.1");

        while (true)
        {
            String[] sensors = service.requestEnvironmentDataTypes();
            for (String sensor : sensors)
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
