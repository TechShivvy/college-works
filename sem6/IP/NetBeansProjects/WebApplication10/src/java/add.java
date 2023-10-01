/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.DriverManager;
import java.util.logging.Level;
import java.sql.*;
import java.util.logging.Logger;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Shivcharan
 */
@WebServlet(urlPatterns = {"/add"})
public class add extends HttpServlet {

    static final String JDBC_DRIVER="com.mysql.cj.jdbc.Driver";
    static final String DB_URL="jdbc:mysql://localhost:3306/luffy";
    static final String USER="root";
    static final String pwd="ssn";
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            Class.forName(JDBC_DRIVER);
            Connection con=DriverManager.getConnection(DB_URL, USER, pwd);
            PreparedStatement ps=con.prepareStatement("select * from zoro where name=? and age=?");
            ps.setString(1,request.getParameter("uname"));
            ps.setInt(2,Integer.valueOf(request.getParameter("pwd")));  
            ResultSet rs=ps.executeQuery();
            if(rs.next()){
//            out.println("Name"+rs.getString("name")+"Age"+rs.getInt("age")+"<br>");
//            out.println("Login success");
                if(rs.getInt("isAdmin")==1)
                {
                    out.print("admin")
                }
                else
                {
                    out.print("cust")
                }
            }
            else
            {
                out.println("<form action='add' method='GET'>"+
                "<input type='text' name='uname' id='uname'>"+
                "<input type='password' name='pwd' id='pwd'>"+
                "<input type='submit' value='Submit'>"+
                "</form>"+
                "<p>Invalid Login Credentials</p>");
                
            }
            
        } catch (ClassNotFoundException ex) {
            Logger.getLogger(add.class.getName()).log(Level.SEVERE, null, ex);
        } catch (SQLException ex) {
            Logger.getLogger(add.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    

}
