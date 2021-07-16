package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.index.impl.Term;
import hust.cs.javacourse.search.index.impl.TermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleScanner;
import hust.cs.javacourse.search.util.Config;
import hust.cs.javacourse.search.util.StringSplitter;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.Locale;
import java.util.Queue;

public class TermTupleScanner extends AbstractTermTupleScanner {
    public TermTupleScanner(BufferedReader input)
    {
        super(input);
    }

    Queue<AbstractTermTuple> buffer = new LinkedList<>();
    int pos = 0;

    /**
     * 获得下一个三元组
     * @return 下一个三元组 如果到了流的末尾 返回null
     * @throws IOException
     */
    @Override
    public AbstractTermTuple next() throws IOException {
        if(buffer.isEmpty())
        {
            String string = input.readLine();
            if(string == null)
            {
                return null;
            }
            while(string.trim().length()==0)
            {
                string = input.readLine();;
                if(string == null)
                {
                    return null;
                }
            }
            StringSplitter splitter = new StringSplitter();
            splitter.setSplitRegex(Config.STRING_SPLITTER_REGEX);
            for(String word: splitter.splitByRegex(string))
            {
                TermTuple termTuple = new TermTuple();
                termTuple.curPos = pos;
                if(Config.IGNORE_CASE)
                {
                    termTuple.term = new Term(word.toLowerCase());
                }
                else
                {
                    termTuple.term = new Term(word);
                }
                buffer.add(termTuple);
                pos++;
            }
        }
        return buffer.poll();
    }
}
