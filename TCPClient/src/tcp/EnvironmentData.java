package tcp;

import java.io.Serializable;
import java.util.ArrayList;

public class EnvironmentData implements Serializable
{
    private String mName;
    private ArrayList<Integer> mValues;
    private String mTimestamp;

    public EnvironmentData(String _name, ArrayList<Integer> _values, String _timestamp)
    {
        this.mName = _name;
        this.mValues = _values;
        this.mTimestamp = _timestamp;
    }

    public String getName()
    {
        return mName;
    }

    public ArrayList<Integer> getValues()
    {
        return mValues;
    }

    public void setValues(ArrayList<Integer> _values)
    {
        this.mValues = _values;
    }

    public String getTimestamp()
    {
        return mTimestamp;
    }

    public void setTimestamp(String _timestamp)
    {
        this.mTimestamp = _timestamp;
    }

    @Override
    public String toString()
    {
        return "tcp.EnvironmentData{" +
                "name='" + mName + '\'' +
                ", values=" + mValues +
                ", timestamp='" + mTimestamp + '\'' +
                '}';
    }
}
