import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

//解析浏览器请求
public class Request {
    private String method; //请求方法
    private String version; //协议版本
    private String requestURL;
    private String requestURI; //请求的URI地址
    private String host; //请求的主机信息
    private String connection; //HTTP请求连接状态信息
    private String agent; //代理
    private String language; //对应Accept-Language
    private String encoding; //请求的编码方式
    private String charset; //请求的字符串编码
    private String accept; //对应Accept
    private int contentLength = 0;

    private InputStream reader;

    public Request(InputStream reader) throws  IOException{
        this.reader = reader;
        this.getRequest();
    }

    public Request(){

    }

    public void getRequest() throws  IOException{
        //解析请求
        String line = readLine(reader, 0 );
        System.out.println(line);
        parser(line);
        do{
            line = readLine(reader, 0);
            System.out.println(line);
            parser(line);
        }while(!line.equals("\r\n"));
        //System.out.println(toString());
        if("POST".equalsIgnoreCase(method)){
            //System.out.println(readLine(reader, contentLength));
        }

    }

    private static String readLine(InputStream is, int contentLe) throws IOException {
        ArrayList<Byte> lineByteList = new ArrayList<Byte>();
        byte readByte;
        int total = 0;
        if (contentLe != 0) {
            do {
                readByte = (byte) is.read();
                lineByteList.add(Byte.valueOf(readByte));
                total++;
            } while (total < contentLe);//消息体读还未读完
        } else {
            do {
                readByte = (byte) is.read();
                if(readByte == -1)
                    break;
                lineByteList.add(Byte.valueOf(readByte));
            } while (readByte != 10);   //换行符 char(10)
        }

        byte[] tmpByteArr = new byte[lineByteList.size()];
        for (int i = 0; i < lineByteList.size(); i++) {
            tmpByteArr[i] = ((Byte) lineByteList.get(i)).byteValue();
        }
        lineByteList.clear();

        String tmpStr = new String(tmpByteArr);
        //System.out.print(tmpStr);
        return tmpStr;

    }
    //根据请求报文的特征,按行解析,每行开头描述了该行代表的内容
    private void parser(String s) {
        if (s.startsWith("GET")) {
            String method = "Get";
            this.setMethod(method);

            int index = s.indexOf("HTTP");
            String uri = s.substring(4, index - 1);
            this.setRequestURI(uri);



            String version = s.substring(index);
            this.setVersion(version);
        } else if (s.startsWith("POST")) {
            String method = "POST";
            this.setMethod(method);

            int index = s.indexOf("HTTP");
            @SuppressWarnings("unused")
            String uri = s.substring(3 + 1, index - 1);// 用index-1可以去掉连接中的空格

            String version = s.substring(index);
            this.setVersion(version);

        } else if (s.startsWith("Accept:")) {
            String accept = s.substring("Accept:".length() + 1);
            this.setAccept(accept);

        } else if (s.startsWith("User-Agent:")) {
            String agent = s.substring("User-Agent:".length() + 1);
            this.setAgent(agent);

        } else if (s.startsWith("Host:")) {
            String host = s.substring("Host:".length() + 1);
            this.setHost(host);

        } else if (s.startsWith("Accept-Language:")) {
            String language = s.substring("Accept-Language:".length() + 1);
            this.setLanguage(language);

        } else if (s.startsWith("Accept-Charset:")) {
            String charset = s.substring("Accept-Charset:".length() + 1);
            this.setCharset(charset);
        } else if (s.startsWith("Accept-Encoding:")) {
            String encoding = s.substring("Accept-Encoding:".length() + 1);
            this.setEncoding(encoding);

        } else if (s.startsWith("Connection:")) {
            String connection = s.substring("Connection:".length() + 1);
            this.setConnection(connection);
        }

    }

    public String getMethod() {
        return method;
    }

    public void setMethod(String method) {
        this.method = method;
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public String getRequestURL() {
        return requestURL;
    }

    public void setRequestURL(String requestURL) {
        this.requestURL = requestURL;
    }

    public String getRequestURI() {
        return requestURI;
    }

    public void setRequestURI(String requestURI) {
        this.requestURI = requestURI;
    }

    public String getHost() {
        return host;
    }

    public void setHost(String host) {
        this.host = host;
    }

    public String getConnection() {
        return connection;
    }

    public void setConnection(String connection) {
        this.connection = connection;
    }

    public String getAgent() {
        return agent;
    }

    public void setAgent(String agent) {
        this.agent = agent;
    }

    public String getLanguage() {
        return language;
    }

    public void setLanguage(String language) {
        this.language = language;
    }

    public String getEncoding() {
        return encoding;
    }

    public void setEncoding(String encoding) {
        this.encoding = encoding;
    }

    public String getCharset() {
        return charset;
    }

    public void setCharset(String charset) {
        this.charset = charset;
    }

    public int getContentLength() {
        return contentLength;
    }

    public void setContentLength(int contentLength) {
        this.contentLength = contentLength;
    }

    public InputStream getReader() {
        return reader;
    }

    public void setReader(InputStream reader) {
        this.reader = reader;
    }

    public String getAccept() {
        return accept;
    }

    public void setAccept(String accept) {
        this.accept = accept;
    }

    @Override
    public String toString() {
        return "HTTP请求重要信息如下：\n" +
                "method = " + method + '\n' +
                "requestURL = " + requestURL + '\n' +
                "requestURI = " + requestURI + '\n' +
                "host = " + host  +
                "connection = " + connection +
                "agent = " + agent +
                "language = " + language +
                "accept = " + accept;
    }
}
