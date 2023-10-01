import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Servlet extends HttpServlet {
   static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";  
	static final String DB_URL="jdbc:mysql://localhost:3306/country";

	//  Database credentials
	static final String USER = "root";
	static final String PASS = "ssn";
   	public void doGet(HttpServletRequest request, HttpServletResponse response)
      throws ServletException, IOException {
      // Retrieve the query string from the AJAX request
      String query = request.getParameter("q");
      try 
      {// Register JDBC driver
			Class.forName(JDBC_DRIVER);
			Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);                                                                             
			Statement stmt = conn.createStatement();
			
         String sql = "SELECT country_name FROM country where country_name like '"+query+"%' order by country_name asc";

         // Query the database to retrieve country names that match the partial text entered by the user
         // String sql = "SELECT name FROM countries WHERE name LIKE ? ORDER BY name ASC";
         // PreparedStatement statement = connection.prepareStatement(sql);
         // statement.setString(1, query + "%");
         ResultSet rs = stmt.executeQuery(sql);

         // Create a JSON object containing the matched country names
         StringBuilder json = new StringBuilder();
         json.append("[");
         boolean first = true;
         while (rs.next()) {
            if (!first) {
               json.append(",");
            }
            json.append("\"");
            json.append(rs.getString("country_name"));
            json.append("\"");
            first = false;
         }
         json.append("]");

         // Set the response content type to JSON and write the JSON object to the response
         response.setContentType("application/json");
         response.setCharacterEncoding("UTF-8");
         response.getWriter().write(json.toString());

      } catch (Exception e) {
         // Handle database errors
        //  throw new ServletException("Database error", ex);
		e.printStackTrace();
      }

   }
}
