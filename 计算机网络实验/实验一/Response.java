import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Properties;

public class Response {
    private String root; //服务器根目录
    private String localURI;
    private Socket responseSocket;
    private Request clientRequest;

    Response(Socket clienter, Request clientRequest){
        this.responseSocket = clienter;
        this.clientRequest = clientRequest;
    }

    //根据解析的合法地址发送报文
    public void doGet() throws IOException{
        if(parseURI()){
            //SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//设置日期格式
            //System.out.println(df.format(new Date()) +"   ");// new Date()为获取当前系统时间
            if(clientRequest.getRequestURI().equals("/favicon.ico")){
                return;
            }
            System.out.println("请求成功！");
            System.out.println(clientRequest.toString());
            System.out.println("请求文件："+clientRequest.getRequestURI());
            System.out.println("请求来源地址："+this.responseSocket.getInetAddress().getHostAddress());
            System.out.println("请求来源名称："+this.responseSocket.getInetAddress().getHostName());
            System.out.println("请求来源端口："+this.responseSocket.getPort());
            //System.out.println(this.responseSocket.getInetAddress().getHostName() + "   " + localURI);
            if(localURI != null){
                OutputStream out = responseSocket.getOutputStream();
                //返回应答消息,并结束应答
                out.write("HTTP/1.0 200 OK\r\n".getBytes());
                out.write("\r\n".getBytes());;// 根据 HTTP 协议, 空行将结束头信息
                @SuppressWarnings("resource")
                InputStream input = new BufferedInputStream(new FileInputStream(localURI));
                //静态网页,将本地文件作为消息体传送
                byte[] data = new byte[1024];
                @SuppressWarnings("unused")
                int length = -1;
                out.flush();
                while((length = input.read(data)) != -1){
                    out.write(data);
                    out.flush();
                }
            }
        }
        else{
            OutputStream out = responseSocket.getOutputStream();
            //返回应答消息,并结束应答
            out.write("HTTP/1.0 404 NOT FOUND\r\n".getBytes());
            out.write("\r\n".getBytes());;// 根据 HTTP 协议, 空行将结束头信息
            out.write("<h1>404 NOT FOUND</h1>".getBytes());
            out.flush();
        }

    }

    private boolean parseURI() throws IOException {
            Properties  properties = new Properties();
            InputStream in = new BufferedInputStream(new FileInputStream(new File("WebInformation.properties")));
            properties.load(in);
            this.root = properties.getProperty("MainMenu");
            StringBuffer sb = new StringBuffer(root);
            String uri = clientRequest.getRequestURI();
            if(uri.length()>1){
                String fileType = uri.substring(uri.lastIndexOf(".")+1,uri.length());
                List<String> TypeList = Arrays.asList("html", "ico", "gif","jpg","mp4");
                if(!TypeList.contains(fileType))
                {
                    System.out.println("请求失败！");
                    System.out.println("抱歉！文件类型暂不支持！");
                    return false;
                }
            }
            switch (uri){
                case "/index.html":
                case "/index.jpg":
                case "/mp4.html":
                case "/index.mp4":
                case "/index.gif":
                case "/pic.html":{
                    sb.append(uri);
                    localURI = sb.toString();
                    break;
                }
                case "/":{
                    sb.append("/index.html");
                    localURI = sb.toString();
                    break;
                }
                case "/favicon.ico":{
                    localURI = null;
                    break;
                }
                default:{
                    System.out.println("请求失败！");
                    System.out.println("你所请求的文件不存在！");
                    return false;
                }
            }
            return true;

    }

}
