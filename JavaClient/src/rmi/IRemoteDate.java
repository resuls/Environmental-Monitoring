package rmi;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Date;

public interface IRemoteDate extends Remote
{
    Date catchDate() throws RemoteException;
    void saySomething() throws RemoteException;
}
