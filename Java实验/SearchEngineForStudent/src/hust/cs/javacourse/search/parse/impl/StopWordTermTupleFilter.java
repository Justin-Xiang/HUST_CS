package hust.cs.javacourse.search.parse.impl;

import hust.cs.javacourse.search.index.AbstractTermTuple;
import hust.cs.javacourse.search.parse.AbstractTermTupleFilter;
import hust.cs.javacourse.search.parse.AbstractTermTupleStream;
import hust.cs.javacourse.search.util.StopWords;

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.Arrays;

public class StopWordTermTupleFilter extends AbstractTermTupleFilter {
    /**
     * 构造函数
     *
     * @param input ：Filter的输入，类型为AbstractTermTupleStream
     */
    public StopWordTermTupleFilter(AbstractTermTupleStream input) {
        super(input);
    }

    /**
     * 获得下一个三元组
     * @return 下一个三元组 如果到了流的末尾 返回null
     * @throws IOException
     */
    @Override
    public AbstractTermTuple next() throws IOException {
        AbstractTermTuple termTuple = input.next();
        if(termTuple == null)
        {
            return null;
        }
        while(Arrays.asList(StopWords.STOP_WORDS).contains(termTuple.term.getContent()))
        {
            termTuple = input.next();
            if(termTuple == null)
            {
                return null;
            }
        }
        return termTuple;
    }
}
