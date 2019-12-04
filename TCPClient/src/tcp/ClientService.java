package tcp;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;

public class ClientService implements IEnvService
{
    private final String mHost;
    private final int mPortNumber;
    private Socket mSocket;

    public ClientService(int _mPortNumber, String _mHost)
    {
        this.mHost = _mHost;
        this.mPortNumber = _mPortNumber;
        try
        {
            connect();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    private void connect() throws IOException
    {
        System.out.println("Creating socket to '" + mHost + "' on port " + mPortNumber);
        mSocket = new Socket(mHost, mPortNumber);
    }

    private void sendMessage(String _message)
    {
        try
        {
            PrintWriter out = new PrintWriter(mSocket.getOutputStream(), true);
            out.println(_message);
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    private String receiveMessage()
    {
        try
        {
            BufferedReader br = new BufferedReader(new InputStreamReader(mSocket.getInputStream()));
            return br.readLine();
        } catch (IOException e)
        {
            e.printStackTrace();
            return "404";
        }
    }

    private String sendRequest(String _request)
    {
        sendMessage(_request);
        return receiveMessage();
    }

    @Override
    public String[] requestEnvironmentDataTypes()
    {
        String resp = sendRequest("getSensortypes()");
        return resp.split(";");
    }

    @Override
    public EnvironmentData requestEnvironmentData(String _type)
    {
        String resp = sendRequest("getSensor(" + _type + ")");
        String[] sp = resp.split("\\|");
        ArrayList<Integer> values = new ArrayList<>();
        String[] vals = sp[1].split(";");

        for (String s : vals)
        {
            values.add(Integer.parseInt(s));
        }

        return new EnvironmentData(_type, values, sp[0]);
    }

    @Override
    public EnvironmentData[] requestAll()
    {
        String resp = sendRequest("getAllSensors()");
        String[] sp = resp.split("\\|");
        EnvironmentData[] environmentData = new EnvironmentData[sp.length - 1];

        int iterator = 0;

        for (int i = 1; i < sp.length; i++)
        {
            String[] type = sp[i].split(";");
            ArrayList<Integer> values = new ArrayList<>();

            for (int j = 1; j < type.length; j++)
            {
                values.add(Integer.parseInt(type[j]));
            }

            environmentData[iterator++] = new EnvironmentData(type[0], values, sp[0]);
        }

        return environmentData;
    }
}