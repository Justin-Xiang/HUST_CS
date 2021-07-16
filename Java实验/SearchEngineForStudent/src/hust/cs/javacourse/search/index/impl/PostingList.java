package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class PostingList extends AbstractPostingList {
    /**
     * 添加Posting 要求不能有内容重复的posting
     *
     * @param posting：Posting对象
     */
    @Override
    public void add(AbstractPosting posting) {
        if(contains(posting))
        {
            return;
        }
        list.add(posting);
    }

    /**
     * 获得PostingList的字符串表示
     *
     * @return PostingList的字符串表示
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        boolean flag = false;
        for(AbstractPosting posting:list)
        {
            if(flag)
            {
                builder.append("->");
            }
            flag = true;
            builder.append(posting.toString());
        }
        builder.append("\n");
        return builder.toString();
    }

    /**
     * 添加Posting列表，要求不能有内容重复的Posting
     *
     * @param postings：Posting列表
     */
    @Override
    public void add(List<AbstractPosting> postings) {
        for(AbstractPosting abstractPosting:postings)
        {
            add(abstractPosting);
        }
    }

    /**
     * 返回指定下标位置的Posting
     *
     * @param index ：下标
     * @return 指定下标位置的Posting
     */
    @Override
    public AbstractPosting get(int index) {
        return list.get(index);
    }

    /**
     * 返回指定Posting对象的下标
     * @param posting：指定的Posting对象
     * @return
     */
    @Override
    public int indexOf(AbstractPosting posting) {
        return list.indexOf(posting);
    }

    /**
     * 返回指定文档id的Posting对象的下标
     * @param docId ：文档id
     * @return 如果找到则返回下标 否则返回-1
     */
    @Override
    public int indexOf(int docId) {
        for(int i = 0;i<list.size();i++)
        {
            if(list.get(i).getDocId() == docId)
            {
                return i;
            }
        }
        return -1;
    }

    /**
     * 是否包含指定Posting对象
     * @param posting： 指定的Posting对象
     * @return 如果包含返回true 否则返回false
     */
    @Override
    public boolean contains(AbstractPosting posting) {
        return list.contains(posting);
    }

    /**
     * 删除指定下标的Posting对象
     * @param index：指定的下标
     */
    @Override
    public void remove(int index) {
        list.remove(index);
    }

    /**
     * 删除指定的Posting对象
     * @param posting ：定的Posting对象
     */
    @Override
    public void remove(AbstractPosting posting) {
        list.remove(posting);
    }

    /**
     * 返回PostingList的大小
     * @return PostingList的大小
     */
    @Override
    public int size() {
        return list.size();
    }

    /**
     * 清除PostingList
     */
    @Override
    public void clear() {
        list.clear();
    }

    /**
     * PostingList是否为空
     *
     * @return 为空返回true 否则返回false
     */
    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    /**
     * 根据文档id的大小对PostingList进行从小到大的排序
     */
    @Override
    public void sort() {
        Collections.sort(list);
    }


    /**
     * 写到二进制文件
     * @param out :输出流对象
     */
    @Override
    public void writeObject(ObjectOutputStream out) {
        try{
            out.writeObject(list.size());
            for(AbstractPosting posting:list)
            {
                posting.writeObject(out);
            }
        }catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    /**
     * 从二进制文件读
     * @param in ：输入流对象
     */
    @Override
    public void readObject(ObjectInputStream in) {
        try{
            int size = (Integer)in.readObject();
            for(int i = 0;i<size;i++)
            {
                AbstractPosting posting = new Posting();
                posting.readObject(in);
                list.add(posting);
            }
        }catch (IOException|ClassNotFoundException e)
        {
            e.printStackTrace();
        }
    }
}
