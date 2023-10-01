/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 *
 * @author Shivcharan
 */
public class Add extends HttpServlet {

    /**
     * Processes requests for both HTTP <code>GET</code> and <code>POST</code>
     * methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     * 
     */
    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost:3306/Patient_Details";

    static final String USER = "root";
    static final String PASSWORD = "ssn";
    
    protected void processRequest(HttpServletRequest req, HttpServletResponse res)
            throws ServletException, IOException {
        res.setContentType("text/html");
        PrintWriter out = res.getWriter();
        String title = "Add Record";

        out.println( 
        "<!DOCTYPE html>\n<html>\n<head>\n<title>"+title+"</title>\n<meta charset='UTF-8'>\n</head>"
        );

        try{
            Class.forName(JDBC_DRIVER);

            Connection con = DriverManager.getConnection(DB_URL,USER,PASSWORD);

            PreparedStatement stm = con.prepareStatement("insert into patient values(?,?,?)");
            stm.setString(1,req.getParameter("name"));
            stm.setInt(2,Integer.valueOf(req.getParameter("age")));
            stm.setDate(3,java.sql.Date.valueOf(req.getParameter("dateofvisit")));

            stm.executeUpdate();

            stm.close();
            con.close();

            out.println("<body>");
            out.println("<h1>Patient Management System</h1><aside><ul><li><a href='http://localhost:8888/PMSystem/add.html'>    Add Record</a></li><li><a href='http://localhost:8888/PMSystem/update.html'> Update Record</a></li><li><a href='http://localhost:8888/PMSystem/delete.html'> Delete Record</a></li><li><a href='http://localhost:8080/sabari/View'>        View Record</a></li><li><a href='http://localhost:8888/PMSystem/search.html'> Search a Record</a></li></ul></aside>");
            out.println("Added record Successfully");
            out.println("</body>");
            out.println("</html>");
        }
        catch(SQLException e){
            System.out.println(e);
            out.println("<body>Database Error</body>");
            out.println("</html>");
        }
        catch(Exception e){
            System.out.println(e);
            out.println("<body>Addition of record Unsuccesfull</body>");
            out.println("</html>");
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
