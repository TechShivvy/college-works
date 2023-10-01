/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import java.sql.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Shivcharan
 */
@WebServlet(urlPatterns = {"/login"})
public class login extends HttpServlet {
    static final String JDBC_URL="com.mysql.cj.jdbc.Driver";
    static final String DB_URL="jdbc:mysql://localhost:3306/ab";
    static final String USER="root";
    static final String PASS="ssn";
    


    protected void service(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try{
            Class.forName(JDBC_URL);
            Connection con = DriverManager.getConnection(DB_URL,USER,PASS);
            PreparedStatement ps = con.prepareStatement("select * from user where name=? and pwd=?");
            ps.setString(1,request.getParameter("name"));
            ps.setString(2,request.getParameter("pwd"));
            ResultSet rs=ps.executeQuery();
            
            if(rs.next()){
            if(rs.getBoolean("isadmin")){
            
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Admin</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<form action=\"admin\">");
            out.println("<input type=\"text\" name=\"pname\"><br>");
            out.println("<input type=\"text\" name=\"type\"><br>");
            out.println("<input type=\"text\" name=\"size\"<br>");
            out.println("<input type=\"text\" name=\"price\"<br>");
            out.println("<input type=\"submit\" value=\"submit\"><br>");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");
            }
            else{
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>User</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<form action=\"user\">");
            out.println("<input type=\"text\" name=\"type\"><br>");
            out.println("<input type=\"text\" name=\"size\"><br>");
            out.println("<input type=\"submit\" value=\"submit\"><br>");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");
            
            }
            }

        }
        catch(Exception e){
            out.println(e);
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
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
