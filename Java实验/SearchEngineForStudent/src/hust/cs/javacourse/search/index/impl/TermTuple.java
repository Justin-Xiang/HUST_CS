package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.AbstractTermTuple;

public class TermTuple extends AbstractTermTuple {

    public TermTuple()
    {

    }

    public TermTuple(AbstractTerm term, int curPos)
    {
        this.term = term;
        this.curPos = curPos;
    }

    /**
     * 判断二个三元组内容是否相同
     * @param o 要比较的另外一个三元组
     * @return 如果内容相等，返回true;否则返回false
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AbstractTermTuple that = (AbstractTermTuple) o;

        if (freq != that.freq) return false;
        if (curPos != that.curPos) return false;
        return term != null ? term.equals(that.term) : that.term == null;
    }

    /**
     * 返回三元组的字符串表示
     * @return 三元组的字符串表示
     */
    @Override
    public String toString() {
        return "AbstractTermTuple{" +
                "term=" + term +
                ", freq=" + freq +
                ", curPos=" + curPos +
                '}';
    }
}
