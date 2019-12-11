public class UsingString
{
    private float mLatitude;
    private float mLongitude;

    public UsingString(String _xml)
    {
        String[] splitted = _xml.split("<");
        String[] lat = splitted[2].split(">");
        String[] lon = splitted[4].split(">");

        mLatitude = Float.parseFloat(lat[1]);
        mLongitude = Float.parseFloat(lon[1]);
    }

    @Override
    public String toString()
    {
        return "WSG{" +
                "mLatitude=" + mLatitude +
                ", mLongitude=" + mLongitude +
                '}';
    }
}
