/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

/**
 *
 * @author Shivcharan
 */
@WebServlet(urlPatterns = {"/task/*"})
public class Task extends HttpServlet {

    static final String JDBC_DRIVER="com.mysql.cj.jdbc.Driver";
    static final String DB_URL="jdbc:mysql://localhost:3306/models";
    static final String USER="root";
    static final String PASS="ssn";
    
    @Override
    protected void doDelete(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        System.out.println("Delete:");
        try{
            /* TODO output your page here. You may use following sample code. */
//            out.println("<!DOCTYPE html>");
//            out.println("<html>");
//            out.println("<head>");
//            out.println("<title>Servlet Task</title>");            
//            out.println("</head>");
//            out.println("<body>");
//            out.println("<h1>Servlet Task at " + request.getContextPath() + "</h1>");
//            out.println("</body>");
//            out.println("</html>");
            Class.forName(JDBC_DRIVER);
            Connection conn = DriverManager.getConnection(DB_URL,USER,PASS);
            
            String pathInfo = request.getPathInfo(),taskId;
            PreparedStatement stmt=conn.prepareStatement("DELETE FROM tasks");;
            if (pathInfo != null && pathInfo.length() > 1) {
                // Remove the leading slash (/) from the pathInfo
                taskId = pathInfo.substring(1);
                stmt=conn.prepareStatement("DELETE FROM tasks where id=?");
                stmt.setInt(1,Integer.valueOf(pathInfo.substring(1)));
            }
            stmt.executeUpdate();
            response.setStatus(HttpServletResponse.SC_OK);
        }
        catch(Exception e)
        {
            out.println(e);
        }
    }
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        System.out.println("Insert:");
        try{
            Class.forName(JDBC_DRIVER);
            Connection conn = DriverManager.getConnection(DB_URL,USER,PASS);
            
            String taskId = request.getParameter("id");
            String taskText = request.getParameter("text");
            PreparedStatement stmt=conn.prepareStatement("INSERT into tasks values(?,?)");
            stmt.setInt(1,Integer.valueOf(taskId));
            stmt.setString(2,taskText);
            stmt.executeUpdate();
            response.setStatus(HttpServletResponse.SC_OK);
            stmt.close();
            conn.close();
        }
        catch(Exception e)
        {
            out.print(e);
        }
    }
protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        System.out.println("GET:");
        try{
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Servlet Task</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Servlet SGTask at " + request.getContextPath() + "</h1>");
            out.println("</body>");
            out.println("</html>");
        }
        catch(Exception e)
        {
            out.print(e);
        }
    }
}
