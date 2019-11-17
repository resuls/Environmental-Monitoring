import java.util.ArrayList;

public class EnvironmentData
{
    private String mName;
    private ArrayList<Integer> mValues;
    private String mTimestamp;

    public EnvironmentData(String _mName, ArrayList<Integer> _values, String _timestamp)
    {
        this.mName = _mName;
        this.mValues = _values;
        this.mTimestamp = _timestamp;
    }

    @Override
    public String toString()
    {
        return "EnvironmentData{" +
                "name='" + mName + '\'' +
                ", values=" + mValues +
                ", timestamp='" + mTimestamp + '\'' +
                '}';
    }
}
