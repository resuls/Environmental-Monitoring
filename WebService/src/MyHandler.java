import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class MyHandler extends DefaultHandler
{
    private Wind wind = new Wind();

    private boolean mSpeed = false;
    private boolean mDeg = false;

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes)
            throws SAXException
    {
        if (qName.equalsIgnoreCase("speed"))
        {
            mSpeed = true;
        }
        else if (qName.equalsIgnoreCase("deg"))
        {
            mDeg = true;
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName)
            throws SAXException
    {

    }

    @Override
    public void characters(char[] ch, int start, int length)
            throws SAXException
    {
        float cur = Float.parseFloat(new String(ch, start, length));

        if (mSpeed)
        {
            wind.setSpeed(cur);
            mSpeed = false;
        } else if (mDeg)
        {
            wind.setDeg(cur);
            mDeg = false;
        }
    }

    public Wind getWind()
    {
        return wind;
    }
}
