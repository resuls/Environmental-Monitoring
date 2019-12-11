public class Wind
{
    private float mSpeed;
    private float mDeg;

    public void setSpeed(float _speed)
    {
        this.mSpeed = _speed;
    }

    public void setDeg(float _deg)
    {
        this.mDeg = _deg;
    }

    @Override
    public String toString()
    {
        return "Wind{" +
                "mSpeed=" + mSpeed +
                ", mDeg=" + mDeg +
                '}';
    }
}