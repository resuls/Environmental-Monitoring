import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainTest
{
    public static void main(String[] _args)
    {
        String xml = "<wgs84><latitude>48.31</latitude><longitude>14.29</longitude></wgs84>";
        UsingString str = new UsingString(xml);
        System.out.println(str);
        System.out.println();

        SAXParserFactory factory = SAXParserFactory.newInstance();
        MyHandler handler = new MyHandler();
        String xml2 = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?><wind><speed>48.31</speed><deg>14.29</deg></wind>";
        try
        {
            SAXParser saxParser = factory.newSAXParser();
            saxParser.parse(new ByteArrayInputStream(xml2.getBytes()), handler);
        } catch (SAXException | ParserConfigurationException | IOException e)
        {
            e.printStackTrace();
        }
        Wind wind = handler.getWind();
        System.out.println(wind);
    }
}