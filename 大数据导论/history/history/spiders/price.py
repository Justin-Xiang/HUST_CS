# -*- coding: utf-8 -*-
import scrapy
import ast
import json
from history.items import HistoryItem
import re


class PriceSpider(scrapy.Spider):
    name = 'price'
    allowed_domains = ['buff.163.com']

    def start_requests(self):
        # 从本地json文件中获取武器类型
        f1 = open('G:\\test\\allWeaponsEn.json', 'r', encoding='utf-8')
        for weapons in ast.literal_eval(f1.read()).keys():
            file = open('G:\\BigData\\order\\order\\spiders\\Skins\\' + weapons + '.json', 'r', encoding='utf-8')
            list_ = ast.literal_eval(file.read())
            for weapon in list_:
                ID = weapon['id']
                base_url = 'https://buff.163.com/api/market/goods/price_history/buff?game=csgo&goods_id=' + \
                        str(ID) + '&currency=CNY&days=90'
                yield scrapy.Request(base_url, callback=self.parse_item)

    def parse_item(self, response):
        # 获取网站json
        text = response.text
        text = json.loads(text)
        for skin in text['data']['price_history']:  # 获取属性
            item = HistoryItem()
            item['id'] = re.findall('goods_id=(.+)&currency', response.url)[0]
            item['date'] = str(skin[0])[:10]
            item['price'] = skin[1]
            yield item

    def parse_url(self, response):
        text = response.text
        text = json.loads(text)
        total_page = int(text['data']['total_page'])
        id = re.findall('id=(.+)&', response.url)[0]
        for i in range(1, total_page + 1):
            url = 'https://buff.163.com/api/market/goods/price_history/buff?game=csgo&goods_id=' + id + '&page_num=' + str(i) +\
                  '&sort_by=default'
            # print('++++++++++++' + url + '++++++++++++++++')
            yield scrapy.Request(url=url, callback=self.parse_item)
