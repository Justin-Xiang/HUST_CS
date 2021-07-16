package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.query.AbstractHit;

import java.util.Map;

public class Hit extends AbstractHit {
    public Hit()
    {

    }
    public Hit(int docId,String docPath)
    {
        super(docId,docPath);
    }
    public Hit(int docId,String docPath,Map<AbstractTerm,AbstractPosting>termAbstractPostingMapping)
    {
        super(docId,docPath,termAbstractPostingMapping);
    }

    /**
     * 获得文档id
     * @return 文档id
     */
    @Override
    public int getDocId() {
        return docId;
    }

    /**
     * 获得文档绝对路径
     * @return
     */
    @Override
    public String getDocPath() {
        return docPath;
    }

    /**
     * 获得文档内容
     * @return
     */
    @Override
    public String getContent() {
        return content;
    }

    /**
     * 设置文档内容
     * @param content ：文档内容
     */
    @Override
    public void setContent(String content) {
        this.content = content;
    }

    /**
     * 获得文档得分
     * @return
     */
    @Override
    public double getScore() {
        return score;
    }

    /**
     * 设置文档得分
     * @param score ：文档得分
     */
    @Override
    public void setScore(double score) {
        this.score = score;
    }

    /**
     * 获得命中的单词和对应的Posting键值对
     * @return 命中的单词和对应的Posting键值对
     */
    @Override
    public Map<AbstractTerm, AbstractPosting> getTermPostingMapping() {
        return termPostingMapping;
    }

    /**
     * 获得命中结果的字符串表示 用于显示搜索结果
     * @return 命中结果的字符串表示
     */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append("\n------------------------");
        builder.append("\n\ndocId: ").append(docId).append("\n\ndocPath: ").append(docPath).append("\n\ncontent: ").append(content).append("\n\nscore: ").append(score).append("\n\n");
        for(Map.Entry<AbstractTerm,AbstractPosting>entry:termPostingMapping.entrySet()){
            builder.append(entry.getKey().getContent()).append("\t---->\t").append(entry.getValue()).append("\n");

        }
        return builder.toString();
    }

    /**
     * 比较两个命中结果的大小 根据score比较
     * @param o     ：要比较的名字结果
     * @return 二个命中结果得分的差值
     */
    @Override
    public int compareTo(AbstractHit o) {
        return (int)(getScore()-o.getScore());
    }
}
