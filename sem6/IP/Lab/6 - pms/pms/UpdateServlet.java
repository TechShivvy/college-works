import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class UpdateServlet extends HttpServlet{
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
		String title = "Database Result";
		try {
			// Register JDBC driver
			Class.forName(JDBC_DRIVER);
			//Class.forName("com.mysql.cj.jdbc.Driver");

			// Open a connection
			Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);

			// Execute SQL query                                                                                                    
			Statement stmt = conn.createStatement();
			String addy=request.getParameter("address").trim();
			String id=request.getParameter("id").trim();
			if(!addy.isEmpty())
			{
				String sql = "update patient set address='"+addy + "' where ID='"+id+"'";
            	stmt.executeUpdate(sql);
			}
			// Clean-up environment
			stmt.close();
			conn.close();
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
            out.println("<h1>Successfully Updated!</h1>");
            out.println("<form action='view'>");
            out.println("    <input type='submit' value='View'>");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");
		} 
		catch(SQLException se) {
         //Handle errors for JDBC
         se.printStackTrace();
		} 
		catch(Exception e) {
         //Handle errors for Class.forName
         e.printStackTrace();
		} 
		finally {
		/*  //finally block used to close resources
         try {
            if(stmt!=null)
               stmt.close();
         } catch(SQLException se2) {
         } // nothing we can do
         try {
            if(conn!=null)
            conn.close();
         } catch(SQLException se) {
            se.printStackTrace();
         } //end finally try */
		} //end try
   }
} 