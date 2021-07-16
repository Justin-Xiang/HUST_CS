package hust.cs.javacourse.search.query.impl;

import hust.cs.javacourse.search.index.AbstractPosting;
import hust.cs.javacourse.search.index.AbstractPostingList;
import hust.cs.javacourse.search.index.AbstractTerm;
import hust.cs.javacourse.search.index.impl.Index;
import hust.cs.javacourse.search.query.AbstractHit;
import hust.cs.javacourse.search.query.AbstractIndexSearcher;
import hust.cs.javacourse.search.query.Sort;
import hust.cs.javacourse.search.util.Config;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

public class IndexSearcher extends AbstractIndexSearcher {
    /**
     * 从指定索引文件打开索引 加载到index对象里
     * @param indexFile ：指定索引文件
     */
    @Override
    public void open(String indexFile) {
        this.index = new Index();
        index.load(new File(indexFile));
    }

    /**
     * 根据单个检索词进行搜索
     * @param queryTerm ：检索词
     * @param sorter ：排序器
     * @return 命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm, Sort sorter) {
        if (Config.IGNORE_CASE) {
            queryTerm.setContent(queryTerm.getContent().toLowerCase());
        }
        AbstractPostingList indexSearchResult = index.search(queryTerm);
        if (indexSearchResult == null) {
            return new Hit[0];
        }
        List<AbstractHit> result = new ArrayList<>();
        for (int i = 0; i < indexSearchResult.size(); i++) {
            AbstractPosting posting = indexSearchResult.get(i);
            AbstractHit hit = new Hit(posting.getDocId(), index.getDocName(posting.getDocId()));
            hit.getTermPostingMapping().put(queryTerm, posting);
            hit.setScore(sorter.score(hit));
            result.add(hit);
        }

        sorter.sort(result);
        AbstractHit[] returnResult = new AbstractHit[result.size()];
        return result.toArray(returnResult);
    }

    /**
     * 根据两个检索词进行搜索
     * @param queryTerm1 ：第1个检索词
     * @param queryTerm2 ：第2个检索词
     * @param sorter ：    排序器
     * @param combine ：   多个检索词的逻辑组合方式
     * @return 命中结果数组
     */
    @Override
    public AbstractHit[] search(AbstractTerm queryTerm1, AbstractTerm queryTerm2, Sort sorter, LogicalCombination combine) {
        AbstractPostingList indexSearchResult1 = index.search(queryTerm1);
        AbstractPostingList indexSearchResult2 = index.search(queryTerm2);
        if (indexSearchResult1 == null && indexSearchResult2 == null) {
            return new Hit[0];
        }

        List<AbstractHit> result = new ArrayList<>();
        if (combine == LogicalCombination.AND) {
            if (indexSearchResult1 == null || indexSearchResult2 == null) {
                return new Hit[0];
            }

            for (int i = 0; i < indexSearchResult1.size(); i++) {
                int docId = indexSearchResult1.get(i).getDocId();
                int sub_index = indexSearchResult2.indexOf(docId);
                if (sub_index != -1) {
                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1, indexSearchResult1.get(i));
                    hit.getTermPostingMapping().put(queryTerm2, indexSearchResult2.get(sub_index));
                    hit.setScore(sorter.score(hit));
                    result.add(hit);
                }
            }
        } else if (combine == LogicalCombination.OR) {
            if (indexSearchResult1 == null) {
                return search(queryTerm2, sorter);
            }
            if (indexSearchResult2 == null) {
                return search(queryTerm1, sorter);
            }

            for (int i = 0; i < indexSearchResult1.size(); i++) {

                int docId = indexSearchResult1.get(i).getDocId();
                int sub_index = indexSearchResult2.indexOf(docId);
                if (sub_index == -1) {

                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1, indexSearchResult1.get(i));
                    hit.setScore(sorter.score(hit));
                    result.add(hit);
                } else {

                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm1, indexSearchResult1.get(i));
                    hit.getTermPostingMapping().put(queryTerm2, indexSearchResult2.get(sub_index));
                    hit.setScore(sorter.score(hit));
                    result.add(hit);
                }
            }
            for (int i = 0; i < indexSearchResult2.size(); i++) {
                int docId = indexSearchResult2.get(i).getDocId();
                int sub_index = indexSearchResult1.indexOf(docId);
                if (sub_index == -1) {
                    // 只有当1中不存在的时候才添加
                    AbstractHit hit = new Hit(docId, index.getDocName(docId));
                    hit.getTermPostingMapping().put(queryTerm2, indexSearchResult2.get(i));
                    hit.setScore(sorter.score(hit));
                    result.add(hit);
                }
            }
        }
        sorter.sort(result);
        AbstractHit[] returnResult = new AbstractHit[result.size()];
        return result.toArray(returnResult);
    }
}
