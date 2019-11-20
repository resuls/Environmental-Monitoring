package rmi;

import tcp.EnvironmentData;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Random;

public class EnvDataManServer extends UnicastRemoteObject implements IEnvService
{
    protected EnvDataManServer() throws RemoteException
    {
        super();
    }

    public static void main(String[] _args)
    {
        try
        {
            EnvDataManServer edms = new EnvDataManServer();
            Registry reg = LocateRegistry.createRegistry(Registry.REGISTRY_PORT);
            reg.rebind("envMan", edms);

            System.out.println("Server is waiting for queries...");
        } catch (Exception _e)
        {
            _e.printStackTrace();
        }
    }

    private void updateValues(EnvironmentData _data)
    {
        ArrayList<Integer> values = new ArrayList<>();
        Random rand = new Random();
        for (int i = 0; i < 3; i++)
        {
            values.add(rand.nextInt(101));
        }
        _data.setValues(values);
    }

    @Override
    public String[] requestEnvironmentDataTypes() throws RemoteException
    {
        return new String[]{"air", "light", "noise"};
    }

    @Override
    public EnvironmentData requestEnvironmentData(String _type) throws RemoteException
    {
        EnvironmentData air = new EnvironmentData("air", new ArrayList<>(),
                Long.toString(System.currentTimeMillis()));
        updateValues(air);
        return air;
    }

    @Override
    public EnvironmentData[] requestAll() throws RemoteException
    {
        EnvironmentData air = new EnvironmentData("air", new ArrayList<>(),
                Long.toString(System.currentTimeMillis()));
        updateValues(air);

        return new EnvironmentData[]{air};
    }
}
