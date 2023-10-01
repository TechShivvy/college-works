import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class ProfileServlet extends HttpServlet{
		// JDBC driver name and database URL
      static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
      static final String DB_URL="jdbc:mysql://localhost:3306/accounts";

      //  Database credentials
      static final String USER = "root";
      static final String PASS = "ssn";
	  public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
		
		response.setContentType("text/html");
		PrintWriter out = response.getWriter();
        
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        
        try{
			// Register JDBC driver
			Class.forName(JDBC_DRIVER);
			//Class.forName("com.mysql.cj.jdbc.Driver");

			// Open a connection
			Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);

			// Execute SQL query                                                                                                    
			Statement stmt = conn.createStatement();
			String sql = "SELECT * FROM details where username='"+username+"'";
			ResultSet rs = stmt.executeQuery(sql);
			if(rs.next())
			{out.println("<html><head><link rel='stylesheet' href='style.css'><title>Profile</title></head><body>"+
			"<div class='button-container' style='position: absolute;top: 0;right: 0;padding: 10px;'>"+
			"<a class='button' href='logout' style='display: inline-block;background-color: blue;color: white;padding: 10px;border-radius: 5px;text-decoration: none;cursor: pointer;'>Logout</a>"+
			"</div>"+
			"<div class='container'>"+
			"<h1 class='page-heading'>Welcome " + username + " to the Profile Page</h1>"+
			"<table>"+
			"<tr><td>User ID:</td><td>" + rs.getString("user_id") + "</td></tr>"+
			"<tr><td>Username:</td><td>" + rs.getString("username") + "</td></tr>"+
			"<tr><td>Email:</td><td>" + rs.getString("email") + "</td></tr>"+
			"<tr><td>Mobile Number:</td><td>" + rs.getString("mobile_number") + "</td></tr>"+
			"<tr><td>Age:</td><td>" + rs.getInt("age") + "</td></tr>"+
			"<tr><td>Gender:</td><td>" + rs.getString("gender") + "</td></tr>"+
			"<tr><td>Bio:</td><td>" + rs.getString("bio") + "</td></tr>"+
			"<tr><td>Name:</td><td>" + rs.getString("name") + "</td></tr>"+
			"<tr><td>Password:</td><td>" + rs.getString("password") + "</td></tr>"+
			"</table></div></body></html>");		}	
			// Clean-up environment
			rs.close();
			stmt.close();
			conn.close();
			// out.println("<li><a href='delete.html'>Delete record</a></li>");
			// out.println("<li><a href='view.html'>View record</a></li>");
			// out.println("<li><a href='search.html'>Search a record</a></li>");
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