/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import  java.io.*;
import java.util.*;
import java.sql.*;
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Shivcharan
 */
@WebServlet(urlPatterns = {"/ab1"})
public class ab1 extends HttpServlet {

    static final String DB_DRIVER="com.mysql.jdbc.Driver";
    static final String DB_URL="jdbc:mysql://localhost:3306/ab";
    static final String USER="root";
    static final String PASS="ssn";
    protected void service(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            
            Class.forName(DB_DRIVER);
            Connection con = DriverManager.getConnection(DB_URL,USER,PASS);
            PreparedStatement ps=con.prepareStatement("insert into absins values(?,?)");
            ps.setString(1,request.getParameter("name"));
            ps.setString(2,request.getParameter("age"));
            ps.executeUpdate();
            out.println("<h1>Inserted</h1>");
            Statement st = con.createStatement();
            ResultSet rs = st.executeQuery("select * from absins");
            if(rs.next()){
                out.println("<html>");
                out.println("<head>");
                out.println("</head>");
                out.println("<body>");
                out.println("<div>");
                out.println("<form action=\"filter\">");
                out.println("<input type=\"text\" name=\"age\">");
                out.println("<input type=\"submit\" value=\"filter search\">");
                out.println("</form>");
                out.println("</div>");
                out.println("<div>");
                out.println("<form action=\"view\">");
                out.println("<input type=\"submit\" value=\"fulltable\">");
                out.println("</form>");
                out.println("</div>");
                out.println("</body>");
                out.println("</html>");
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
