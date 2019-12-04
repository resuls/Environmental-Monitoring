package tcp;

public interface IEnvService
{
    String[] requestEnvironmentDataTypes();
    EnvironmentData requestEnvironmentData(String _type);
    EnvironmentData[] requestAll();
}
