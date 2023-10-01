import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class LoginServlet extends HttpServlet{
    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
    static final String DB_URL="jdbc:mysql://localhost:3306/accounts";

    //  Database credentials
    static final String USER = "root";
    static final String PASS = "ssn";

    public void service(HttpServletRequest request, HttpServletResponse response) 
    throws ServletException, IOException {

        // Get user credentials from the request body
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        // request.setAttribute("username",username);
        // request.setAttribute("password",password);

        // Check if the user credentials are valid (you can implement this logic using a database or other means)
        RequestDispatcher rd=request.getRequestDispatcher("validate");
        rd.include(request,response);
        boolean isValidCredentials = (boolean) request.getAttribute("validate");
        System.out.println("LoginServlet: doPost method called");
        if (isValidCredentials) {
            // response.setStatus(HttpServletResponse.SC_OK);
            // response.getWriter().write("success");
            // Store the username in session
            HttpSession session = request.getSession();
            session.setAttribute("username", username);

            // Redirect to ProfileServlet on successful login
            // response.sendRedirect("ProfileServlet");
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            
            out.println("<html><head><link rel='stylesheet' href='homepage.css''><title>Success</title></head><body>");
            out.println("<div class='container'>");
            out.println("<h1>Welcome " + username + "</h1>");
            out.println("<ul>");
            out.println("<li><a href='profile'>Profile</a></li>");
            out.println("<li><a href='logout'>Logout</a></li>");
            // out.println("<li><a href='delete.html'>Delete record</a></li>");
            // out.println("<li><a href='view.html'>View record</a></li>");
            // out.println("<li><a href='search.html'>Search a record</a></li>");
            out.println("</ul>");
            out.println("</div></body></html>");

        } else {
            // Return an error response with status code 401 Unauthorized
            // response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            // response.getWriter().write("failure");
            // response.setStatus(401);
            response.sendRedirect("login.html?error=Invalid credentials");
        }
    }
    
    // private boolean validateCredentials(String username, String password) {
    //     // You can implement this logic to validate the user credentials using a database or other means
    //     // For demonstration purposes, we'll hardcode the credentials
    //     return username.equals("admin") && password.equals("password");
    // }
}