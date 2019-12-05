package servlet;

import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(
        name = "Info servlet",
        description = "a small test servlet",
        urlPatterns = {"/test"}
)
public class InfoServlet extends HttpServlet
{
    public void init() throws ServletException
    {
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        // Set response content type
        response.setContentType("text/html");

        PrintWriter out = response.getWriter();

        String a = request.getParameter("hello");

        if (a != null)
        {
            out.println("<h1>" + a + "</h1>");
        }
        else
        {
            out.println("<table>");
            out.println(String.format("<tr><th>Client IP: </th><td>%s</td></tr>", request.getRemoteAddr()));
            out.println(String.format("<tr><th>Browser: </th><td>%s</td></tr>", request.getHeader("User-Agent")));
            out.println(String.format("<tr><th>MIME: </th><td>%s</td></tr>", request.getHeader("Accept")));
            out.println(String.format("<tr><th>Client Protocol: </th><td>%s</td></tr>", request.getProtocol()));
            out.println(String.format("<tr><th>Port: </th><td>%s</td></tr>", request.getRemotePort()));
            out.println(String.format("<tr><th>Server name: </th><td>%s</td></tr>", request.getServerName()));
            out.println("</table>");
        }
    }

    public void destroy()
    {
    }
}