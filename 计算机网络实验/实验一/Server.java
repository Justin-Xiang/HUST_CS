import java.io.*;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Properties;
import java.io.*;
public class Server{
    public static void main(String[] args) throws  IOException{
        Properties properties = new Properties();
        InputStream inputStream = new BufferedInputStream(new FileInputStream(new File("WebInformation.properties")));
        properties.load(inputStream);
        int port = Integer.parseInt(properties.getProperty("ListenPort"));
        String addr =  properties.getProperty("ListenAddress");
        System.out.println(addr);
        InetAddress address = Inet4Address.getByName(addr);
        ServerSocket listener = new ServerSocket(port,4, address);
        while (true){
            try{
                Socket socket = listener.accept();
                InputStream in = socket.getInputStream();
                Request client = new Request(in);
                Response response = new Response(socket, client);
                response.doGet();
                socket.close();
            }catch (IOException e){
                e.printStackTrace();
            }


        }
    }
}
//public class Server {
//
//
//    public static void main(String[] args) throws IOException {
//        Properties properties = new Properties();
//        InputStream inputStream = new BufferedInputStream(new FileInputStream(new File("WebInformation.properties")));
//        properties.load(inputStream);
//        int port = Integer.parseInt(properties.getProperty("ListenPort"));
//        ServerSocket listener = new ServerSocket(port);
//        while (true) {
//            Socket socket = listener.accept();
//            Thread th = new Thread(new RequestThread(socket));
//            th.start();
//        }
//    }
//}
//
//class RequestThread implements Runnable{
//    private Socket socket;
//
//    public RequestThread(Socket socket){
//        this.socket = socket;
//    }
//    @Override
//    public void run() {
//        //解析请求信息
//        try {
//            InputStream in = socket.getInputStream();
//            Request client = new Request(in);
//            //根据请求报文做出响应
//            Response response = new Response(socket, client);
//            response.doGet();
//
//            socket.close();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//
//    }
//}
