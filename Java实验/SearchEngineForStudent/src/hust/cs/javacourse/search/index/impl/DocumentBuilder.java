package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractDocument;
import hust.cs.javacourse.search.index.AbstractDocumentBuilder;
import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.parse.impl.LengthTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.PatternTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.StopWordTermTupleFilter;
import hust.cs.javacourse.search.parse.impl.TermTupleScanner;

import java.io.*;

public class DocumentBuilder extends AbstractDocumentBuilder {

    /**
     * 由解析文本文档得到的TermTupleStream构造Document对象
     * @param docId             : 文档id
     * @param docPath           : 文档绝对路径
     * @param termTupleStream   : 文档对应的TermTupleStream
     * @return Document对象
     * @throws IOException
     */
    @Override
    public AbstractDocument build(int docId, String docPath, AbstractTermTupleStream termTupleStream)throws IOException {

        AbstractDocument document = new Document(docId,docPath);
        AbstractTermTuple termTuple = termTupleStream.next();
        while(termTuple!=null)
        {
            document.addTuple(termTuple);
            termTuple = termTupleStream.next();
        }
        termTupleStream.close();
        return document;

    }

    /**
     * 由给定的file 构造Document对象
     * @param docId     : 文档id
     * @param docPath   : 文档绝对路径
     * @param file      : 文档对应File对象
     * @return Document对象
     */
    @Override
    public AbstractDocument build(int docId, String docPath, File file) {
        AbstractDocument document = null;
        AbstractTermTupleStream ts = null;
        try{
            ts = new TermTupleScanner(new BufferedReader((new InputStreamReader((new FileInputStream(file))))));
            ts = new StopWordTermTupleFilter(ts); //停用词过滤器
            ts = new PatternTermTupleFilter(ts);  //正则表达式过滤器
            ts = new LengthTermTupleFilter(ts);   //单词长度过滤器
            document = build(docId,docPath,ts);
        }catch (IOException e)
        {
            e.printStackTrace();
        }finally {

            ts.close();
        }
        return document;
    }
}
