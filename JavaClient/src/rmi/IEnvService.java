package rmi;

import tcp.EnvironmentData;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IEnvService extends Remote
{
    String[] requestEnvironmentDataTypes() throws RemoteException;
    EnvironmentData requestEnvironmentData(String _type) throws RemoteException;
    EnvironmentData[] requestAll() throws RemoteException;
}
