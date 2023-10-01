/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;

/**
 *
 * @author Shivcharan
 */
@WebServlet(urlPatterns = {"/Add"})
public class Add extends HttpServlet {
    static final String JDBC = "com.mysql.jdbc.Driver";
    static final String DB = "jdbc:mysql://localhost:3306/luffy";
    static final String USER = "root";
    static final String PASS = "ssn";

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            Class.forName(JDBC);
            Connection con = DriverManager.getConnection(DB,USER,PASS);
            PreparedStatement ps = con.prepareStatement("Insert into zoro values(?,?)");
            ps.setString(1,request.getParameter("name"));
            ps.setInt(2,Integer.valueOf(request.getParameter("age")));
            ps.executeUpdate();
            ps.close();
            con.close();
            out.println("Inserted");
        }
        catch(Exception e){
            out.println(e);
        }
    }
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            Class.forName(JDBC);
            Connection con = DriverManager.getConnection(DB,USER,PASS);
            PreparedStatement ps = con.prepareStatement("select * from zoro where name=?");
            ps.setString(1,request.getParameter("name"));
            ResultSet rs = ps.executeQuery();
            while(rs.next()){
                out.println(rs.getString("name")+" ");
                out.println(rs.getInt("age")+"<br>");
            }
            rs.close();
            ps.close();
            con.close();
        }
        catch(Exception e){
            out.println(e);
        }
    }

}
