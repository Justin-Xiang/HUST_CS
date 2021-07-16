package hust.cs.javacourse.search.index.impl;

import hust.cs.javacourse.search.index.AbstractTerm;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class Term extends AbstractTerm {

    public Term(){

    }

    public Term(String content)
    {
        super(content);
    }

    /**
     * 判断两个Term内容是否相同
     * @param o 要比较的另一个Term
     * @return 如果内容相等返回true 否则返回false
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        AbstractTerm that = (AbstractTerm) o;

        return content != null ? content.equals(that.getContent()) : that.getContent() == null;
    }

    /**
     * 返回Term的字符串表示
     * @return 字符串表示
     */
    @Override
    public String toString() {
        return this.content;
    }

    /**
     * 返回Term内容
     * @return Term的内容
     */
    @Override
    public String getContent() {
        return this.content;
    }

    /**
     * 设置Term的内容
     * @param content：Term的内容
     */
    @Override
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * 比较两个Term的大小(按字典序)
     * @param o： 要比较的Term对象
     * @return 两个Term对象的字典序差值
     */
    @Override
    public int compareTo(AbstractTerm o) {
        return this.content.compareTo(o.getContent());
    }

    @Override
    public void writeObject(ObjectOutputStream out) {
        try{
            out.writeObject(this.content);
        }catch (IOException e)
        {
            e.printStackTrace();
        }

    }

    @Override
    public void readObject(ObjectInputStream in) {
    try{
        this.content = (String)in.readObject();
    }catch (IOException | ClassNotFoundException e)
    {
        e.printStackTrace();
    }
    }
}
