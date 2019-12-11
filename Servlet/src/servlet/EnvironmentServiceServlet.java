package servlet;

import tcp.ClientService;
import tcp.EnvironmentData;
import tcp.IEnvService;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

@WebServlet(
        name = "Session servlet",
        description = "a small test servlet",
        urlPatterns = {"/test"}
)
public class EnvironmentServiceServlet extends HttpServlet
{
    public void init() throws ServletException
    {
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        PrintWriter out = response.getWriter();

        // Set response content type
        response.setContentType("text/html");

        // Refresh every 5 seconds.
        response.addHeader("Refresh", "5");

        out.println("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css\">\n");
        IEnvService service = null;
        try
        {
            service = new ClientService(5555, "127.0.0.1");

            EnvironmentData[] data = service.requestAll();

            out.println("<h1>C++ Server Environment Data</h1><br>");
            printTable(out, data);
        }
        catch (Exception e)
        {
            out.println("<h1>C++ server offline.</h1>");
        }
        finally
        {
            if (service != null)
                ((ClientService)service).disconnect();
        }

        out.println("<br>");

        String adr = "envMan";
        Registry reg = LocateRegistry.getRegistry();
        try
        {
            rmi.IEnvService iEnvService = (rmi.IEnvService) reg.lookup(adr);

            rmi.EnvironmentData[] data = iEnvService.requestAll();

            out.println("<h1>RMI Server Environment Data</h1><br>");
            printTable(out, data);
        }
        catch (Exception e)
        {
            out.println("<h1>RMI server offline.</h1>");
        }
    }

    public void destroy()
    {
    }

    private void printTable(PrintWriter _out, EnvironmentData[] _data)
    {
        _out.println("<div class='table-responsive-xl'>");
        _out.println("<table class='table table-bordered'>");
        _out.println("<tr>");
        _out.println("<th scope='col'>Timestamp</th>");
        _out.println("<th scope='col'>Sensor</th>");
        _out.println("<th scope='col'>Value</th>");
        _out.println("</tr>");
        for (EnvironmentData d : _data)
        {
            _out.println("<tr>");
            _out.println("<td>" + d.getTimestamp() + "</td>");
            _out.println("<td>" + d.getName() + "</td>");
            _out.println("<td>" + d.getValues() + "</td>");
            _out.println("</tr>");
        }
        _out.println("</table>");
        _out.println("</div>");
    }

    private void printTable(PrintWriter _out, rmi.EnvironmentData[] _data)
    {
        _out.println("<div class='table-responsive-xl'>");
        _out.println("<table class='table table-bordered'>");
        _out.println("<tr>");
        _out.println("<th scope='col'>Timestamp</th>");
        _out.println("<th scope='col'>Sensor</th>");
        _out.println("<th scope='col'>Value</th>");
        _out.println("</tr>");
        for (rmi.EnvironmentData d : _data)
        {
            _out.println("<tr>");
            _out.println("<td>" + d.getTimestamp() + "</td>");
            _out.println("<td>" + d.getName() + "</td>");
            _out.println("<td>" + d.getValues() + "</td>");
            _out.println("</tr>");
        }
        _out.println("</table>");
        _out.println("</div>");
    }
}