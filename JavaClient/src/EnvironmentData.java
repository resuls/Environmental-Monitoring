import java.util.ArrayList;

public class EnvironmentData
{
    private String name;
    private ArrayList<Integer> values;
    private String timestamp;

    public EnvironmentData(String name, ArrayList<Integer> values, String timestamp)
    {
        this.name = name;
        this.values = values;
        this.timestamp = timestamp;
    }

    public String getName()
    {
        return name;
    }

    public ArrayList<Integer> getValues()
    {
        return values;
    }

    public String getTimestamp()
    {
        return timestamp;
    }

    @Override
    public String toString()
    {
        return "EnvironmentData{" +
                "name='" + name + '\'' +
                ", values=" + values +
                ", timestamp='" + timestamp + '\'' +
                '}';
    }
}
