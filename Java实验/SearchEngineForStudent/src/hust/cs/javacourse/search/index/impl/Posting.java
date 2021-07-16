package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class Posting extends AbstractPosting {


    public Posting(int docId, int freq, List<Integer> positions)
    {
        super(docId, freq,positions);
    }

    public Posting()
    {

    }

    /**
     * 判断二个Posting内容是否相同
     * @param o 要比较的另一个Posting
     * @return 如果内容相等则返回true，否则返回false
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AbstractPosting that = (AbstractPosting) o;

        if (docId != that.getDocId()) return false;
        if (freq != that.getFreq()) return false;
        if (positions.size()!=that.getPositions().size()) return false;
        return positions != null ? positions.containsAll(that.getPositions()) : that.getPositions() == null;
    }

    /**
     * 返回Posting的字符串表示
     *
     * @return 字符串
     */
    @Override
    public String toString() {
        return "Posting{" +
                "docId=" + docId +
                ", freq=" + freq +
                ", positions=" + positions +
                '}';
    }

    /**
     * 返回包含单词的文档id
     *
     * @return 文档id
     */
    @Override
    public int getDocId() {
        return this.docId;
    }

    /**
     * 设置包含单词的文档id
     * @param docId：包含单词的文档id
     */
    @Override
    public void setDocId(int docId) {
        this.docId = docId;
    }

    /**
     * 返回单词在文档里出现的次数
     * @return
     */
    @Override
    public int getFreq() {
        return this.freq;
    }

    /**
     * 设置单词在文档里出现的次数
     * @param freq:单词在文档里出现的次数
     */
    @Override
    public void setFreq(int freq) {
        this.freq = freq;
    }

    /**
     * 返回单词在文档里出现的位置列表
     * @return 位置列表
     */
    @Override
    public List<Integer> getPositions() {
        return this.positions;
    }

    /**
     * 设置单词在文档里出现的位置列表
     * @param positions：单词在文档里出现的位置列表
     */
    @Override
    public void setPositions(List<Integer> positions) {
        this.positions = positions;
    }

    /**
     * 比较两个Posting对象的大小(根据docId)
     * @param o： 另一个Posting对象
     * @return 二个Posting对象的docId的差值
     */
    @Override
    public int compareTo(AbstractPosting o) {
        return this.docId-o.getDocId();
    }

    /**
     * 对内部positions从小到大排序
     */
    @Override
    public void sort() {
        Collections.sort(this.positions);
    }

    /**
     * 写到二进制文件
     *
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try{
            out.writeObject(docId);
            out.writeObject(freq);
            out.writeObject(positions.size());
            for(Integer i:positions)
            {
                out.writeObject(i);
            }
        }catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * 从二进制文件度
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        try{
            this.docId = (Integer)in.readObject();
            this.freq = (Integer)in.readObject();
            int size = (Integer)in.readObject();
            for(int i = 0 ;i<size;i++)
            {
                positions.add((Integer)in.readObject());
            }
        }catch (IOException e)
        {
            e.printStackTrace();
        }catch (ClassNotFoundException e)
        {
            e.printStackTrace();
        }
    }
}
