import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.MultipartConfig;
import javax.servlet.annotation.WebServlet;
import java.util.*;

@WebServlet("/upload")
@MultipartConfig()
public class ProcessServlet extends HttpServlet {
  public void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {

    // Retrieve form data
    String salut = request.getParameter("salutations");
String name = request.getParameter("participantName");
String uName = request.getParameter("username");
String email = request.getParameter("email");
String pwd = request.getParameter("password");
String dob = request.getParameter("dob");
String[] lang = request.getParameterValues("languagesKnown");
String addl=request.getParameter("additionalExpertise");

Part filePart = request.getPart("photo");
String fileName = filePart.getSubmittedFileName();
long fileSize = filePart.getSize();
String fileType = filePart.getContentType();

// Generate a unique filename for the uploaded image
String filename = UUID.randomUUID().toString() + ".jpg";

// Save the uploaded file to disk
String uploadDir = getServletContext().getRealPath("/images");
    File uploadDirFile = new File(uploadDir);
    if (!uploadDirFile.exists()) {
        uploadDirFile.mkdir();
    }
    File file = new File(uploadDir + File.separator + filename);
    try (InputStream inputStream = filePart.getInputStream();
         OutputStream outputStream = new FileOutputStream(file)) {
        byte[] buffer = new byte[1024];
        int bytesRead;
        while ((bytesRead = inputStream.read(buffer)) != -1) {
            outputStream.write(buffer, 0, bytesRead);
        }
    }

// byte[] fileBytes = new byte[(int) fileSize];
// InputStream inputStream = filePart.getInputStream();
// int read;
// int offset = 0;
// while ((read = inputStream.read(fileBytes, offset, fileBytes.length - offset)) >= 0) {
//     offset += read;
// }
// String base64Image = Base64.getEncoder().encodeToString(fileBytes);


// Generate response
response.setContentType("text/html");
PrintWriter out = response.getWriter();
out.println("<html><head><title>Form Response</title></head>");
out.println("<style> table { border-collapse: collapse; margin: auto; }");
out.println("td, th { border: 2px solid black; text-align: left; padding: 8px; } </style>");
out.println("</head><body>");
out.println("<table>");
out.println("<tr><th>Field</th><th>Value</th></tr>");
// out.println("<table border='1' align='center' style='border-collapse:collapse;'>");
// out.println("<tr><th style='text-align:left;'>Field</th><th style='text-align:left;'>Value</th></tr>");
out.println("<tr><td>Salutations</td><td>" + salut + "</td></tr>");
out.println("<tr><td>Name</td><td>" + name + "</td></tr>");
out.println("<tr><td>Username</td><td>" + uName + "</td></tr>");
out.println("<tr><td>Password</td><td>" + pwd + "</td></tr>");
out.println("<tr><td>Email</td><td>" + email + "</td></tr>");
out.println("<tr><td>DOB</td><td>" + dob + "</td></tr>");
out.println("<tr><td>Languages Known</td><td>");
if (lang != null) {
    for (String language : lang) {
        out.println(language + "<br>");
    }
}
out.println("</td></tr>");
out.println("<tr><td>Additional Expertise</td><td>" + addl + "</td></tr>");
out.println("<tr><td>File Name</td><td>" + fileName + "</td></tr>");
out.println("<tr><td>File Size</td><td>" + fileSize + " bytes</td></tr>");
out.println("<tr><td>File Type</td><td>" + fileType + "</td></tr>");
//out.println("<tr><td>Photo</td><td><img src='data:" + fileType + ";base64," + Base64.getEncoder().encodeToString(filePart.getInputStream().readAllBytes()) + "'/></td></tr>");
//out.println("<tr><td>Photo</td><td><img src='data:" + fileType + ";base64," + Base64.getEncoder().encodeToString(IOUtils.toByteArray(filePart.getInputStream())) + "'/></td></tr>");
// out.println("<tr><td>Photo</td><td><img src='data:" + fileType + ";base64," + base64Image + "'/></td></tr>");
out.println("<tr><td>Photo</td><td><img width=\"70%\" alt=\"filename\" src='images/" + filename + "'/></td></tr>");
out.println("</table>");
out.println("</body></html>");

  }
}
