package servlet;

import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(
        name = "VIS-Test-Servlet",
        description = "a small test servlet",
        urlPatterns = {"/"}
)
public class HelloWorldServlet extends HttpServlet
{
    private int vCount;

    public void init() throws ServletException
    {
        vCount = 0;
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException
    {
        // Set response content type
        response.setContentType("text/html");

        PrintWriter out = response.getWriter();
        out.println("<h1>" + ++vCount + "</h1>");
    }

    public void destroy()
    {
    }
}