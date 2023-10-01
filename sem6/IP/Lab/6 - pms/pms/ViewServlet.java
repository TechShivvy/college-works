import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class ViewServlet extends HttpServlet{
		// JDBC driver name and database URL
      static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
      static final String DB_URL="jdbc:mysql://localhost:3306/hospital";

      //  Database credentials
      static final String USER = "root";
      static final String PASS = "ssn";
	  public void doGet(HttpServletRequest request, HttpServletResponse response)
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
			String sql = "SELECT * FROM patient";
			ResultSet rs = stmt.executeQuery(sql);
			out.println("<html><head><link rel='stylesheet' href='style.css'><title>View DB</title></head><body>");
			out.println("<div class='container'>");
			out.println("<h1 class='page-heading'>Patient Database</h1>");
			out.println("<table>");
            out.print("<tr>");
            out.print("<th>ID</th>");
            out.print("<th>AGE</th>");
            out.print("<th>NAME</th>");
            out.print("<th>GENDER</th>");
            out.print("<th>ADDRESS</th>");
            out.print("<th>M. Status</th>");
            out.print("<th>DOV</th>");
            out.print("</tr>");
			Boolean yes=false;
			// Extract data from result set
			while(rs.next()){
				yes=true;
				//Retrieve by column name
				String name = rs.getString("name");
				int age = rs.getInt("age");
				String id = rs.getString("id");
				String gender = rs.getString("gender");
                String add = rs.getString("address");
                String ms = rs.getString("marstat");
                String dov = rs.getString("dov");                                                                                              
				// Display values
				out.print("<tr><td>"+id +"</td>");
				out.print("<td>" + age +"</td>");
                out.print("<td>" + name +"</td>");
				out.print("<td>" + gender +"</td>");
                out.print("<td>" + add +"</td>");
				out.print("<td>" + ms+"</td>");
                out.print("<td>" + dov+"</td></tr>");
				
				// out.print(", First: " + first );
				// out.println(", Last: " + last + "<br>");
			}
			out.println("</table></div></body></html>");
			if(!yes)
				out.println("<tr><td colspan='7' style='text-align: center'><i>No records to display</i></td></tr>");
			// Clean-up environment
			rs.close();
			stmt.close();
			conn.close();
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