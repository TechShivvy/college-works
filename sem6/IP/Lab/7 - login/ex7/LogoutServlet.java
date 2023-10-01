import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class LogoutServlet extends HttpServlet{
    public void service(HttpServletRequest request, HttpServletResponse response) 
    throws ServletException, IOException {
        HttpSession session = request.getSession();
        session.invalidate();
        
        // response.setContentType("text/html");
        // PrintWriter out = response.getWriter();
        // out.println("<html><head><link rel='stylesheet' href='homepage.css'><title>Logout</title></head><body>");
        // out.println("<div class='container'>");
        // out.println("<h1>Successfully Logged out</h1>");
        // out.println("<ul>");
        // out.println("<li><a href='login'>Login</a></li>");
        // out.println("</ul>");
        // out.println("</div></body></html>");
        response.sendRedirect("login.html?invalidate=Successfully Logged out");
    }
}