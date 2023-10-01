/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;

/**
 *
 * @author Shivcharan
 */
public class View extends HttpServlet {


    static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost:3306/Patient_Details";

    static final String USER = "root";
    static final String PASSWORD = "ssn";

    
    protected void processRequest(HttpServletRequest requ, HttpServletResponse res)
            throws ServletException, IOException {
        res.setContentType("text/html");
        PrintWriter out = res.getWriter();
        String title = "View Records";

        out.println(
                "<!DOCTYPE html>\n<html>\n<head>\n<title>" + title
                        + "</title>\n<meta charset='UTF-8'>\n<link rel=\"stylesheet\" href=\"styles.css\">\n</head>");

        try {
            Class.forName(JDBC_DRIVER);

            Connection con = DriverManager.getConnection(DB_URL, USER, PASSWORD);

            Statement stm = con.createStatement();
            String sql;
            sql = "select * from patient";

            ResultSet rs = stm.executeQuery(sql);

            out.println(
                    "<body><h2>Patient Records</h2><table><thead><tr><th>Name</th><th>Age</th><th>Date of Visit</th></tr></thead>");
            out.println(
                    "<h1>Patient Management System</h1><aside><ul><li><a href='http://localhost:8080/sabari/add.html'>    Add Record</a></li><li><a href='http://localhost:8888/PMSystem/update.html'> Update Record</a></li><li><a href='http://localhost:8888/PMSystem/delete.html'> Delete Record</a></li><li><a href='http://localhost:8888/PMSystem/View'>        View Record</a></li><li><a href='http://localhost:8888/PMSystem/search.html'> Search a Record</a></li></ul></aside>");
            out.println("<tbody>");

            while (rs.next()) {
                out.println("<tr>");
                out.print("<td>" + rs.getString("NAME") + "</td>");
                out.print("<td>" + rs.getInt("AGE") + "</td>");
                out.print("<td>" + rs.getDate("DOB") + "</td>");
                out.println("</tr>");
            }

            rs.close();
            stm.close();
            con.close();

            out.println("</tbody>");
            out.println("</body>\n</html>");
        } catch (SQLException e) {
            System.out.println(e);
            out.println("<body>Database Error</body>");
            out.println("</html>");
        } catch (Exception e) {
            System.out.println(e);
            out.println("<body>Viewing of record Unsuccesfull</body>");
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
