 /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Shivcharan
 */
@WebServlet(urlPatterns = {"/signup"})
public class search extends HttpServlet {

   static final String JDBC_DRIVER="com.mysql.cj.jdbc.Driver";
           static final String DB_URL="jdbc:mysql://localhost:3306/test";
                   static final String USER="root";
                  static final String PASS="ssn";
    protected void service(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try  {
            Class.forName(JDBC_DRIVER);
            
            Connection conn=DriverManager.getConnection(DB_URL, USER,PASS);
           // ...

Statement stmt = conn.createStatement();
//stmt.setString(1, request.getParameter("fname"));


// ...

            String sql="select *from login where fname=\""+request.getParameter("fname") +"\" and pwd=\""+request.getParameter("pwd")+"\"";
            out.println(request.getParameter("fname"));
                                 out.println("1"+request.getParameter("pwd"));

            ResultSet rs=stmt.executeQuery(sql);
                     out.println(request.getParameter("pwd"));

            if(rs.next()){
            

            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet NewServlet</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>logedin </h1>");
            out.println("</body>");
            out.println("</html>");}
            else{
                 out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet NewServlet</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>user doesn't exist </h1>");
            out.println("</body>");
            out.println("</html>");}
            rs.close();
            stmt.close();
            conn.close();
            } catch (ClassNotFoundException ex) { 
           Logger.getLogger(search.class.getName()).log(Level.SEVERE, null, ex);
       } catch (SQLException ex) {
           Logger.getLogger(search.class.getName()).log(Level.SEVERE, null, ex);
       } 
}
}
