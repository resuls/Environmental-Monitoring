package servlet;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Random;

@WebServlet(
        name = "Session servlet",
        description = "a small test servlet",
        urlPatterns = {"/test"}
)
public class SessionServlet extends HttpServlet
{
    private String last;

    public void init() throws ServletException
    {
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        // Set response content type
        response.setContentType("text/html");

        String browser = "";
        String userAgent = request.getHeader("User-Agent");

        if (userAgent.contains("Edge/"))
        {
            browser = "Edge";

        } else if (userAgent.contains("Safari/") && userAgent.contains("Version/"))
        {
            browser = "Safari";

        } else if (userAgent.contains("OPR/") || userAgent.contains("Opera/"))
        {
            browser = "Opera";

        } else if (userAgent.contains("Chrome/"))
        {
            browser = "Chrome";

        } else if (userAgent.contains("Firefox/"))
        {
            browser = "Firefox";
        }

        PrintWriter out = response.getWriter();

        String magicNumber = request.getParameter("magic");

        out.println("<h1>");
        out.println("You are currently using ");
        out.println(browser);
        out.println(" (magic number: " + magicNumber + "). Last time you visited, ");
        out.println("your magic number was " + ((last == null) ? "NONE" : last) + "!");
        out.println("</h1>");

        last = magicNumber;
    }

    public void destroy()
    {
    }
}