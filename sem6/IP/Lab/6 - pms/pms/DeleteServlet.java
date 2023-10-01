import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class DeleteServlet extends HttpServlet{
		// JDBC driver name and database URL
      static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
      static final String DB_URL="jdbc:mysql://localhost:3306/hospital";

      //  Database credentials
      static final String USER = "root";
      static final String PASS = "ssn";
	  public void doPost(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
   
		// Set response content type
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
        
		try {
			// Register JDBC driver
			//Class.forName("com.mysql.cj.jdbc.Driver");
			Class.forName(JDBC_DRIVER);
            Statement stmt=null;
			// Open a connection
			Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             
			// Execute SQL query 
			stmt = (Statement) conn.createStatement();
            String sql = "delete from  patient where ID='"+request.getParameter("id")+"'";
            stmt.executeUpdate(sql);
            
            // Close all the connections
            stmt.close();
            conn.close();
  
            // Get a writer pointer 
            // to display the successful result
            
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Success</title>");
            out.println("<style>");
            out.println("body {");
            out.println("    font-family: Arial, sans-serif;");
            out.println("    text-align: center;");
            out.println("}");
            out.println("h1 {");
            out.println("    margin-top: 50px;");
            out.println("}");
            out.println("</style>");
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Successfully Deleted!</h1>");
            out.println("<form action='view'>");
            out.println("    <input type='submit' value='View'>");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");
        }
        catch (Exception e) {
            
            e.printStackTrace();
        }
    }
} 