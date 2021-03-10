# -*- coding: utf-8 -*-
import scrapy
import ast
import json
from buff_test.items import BuffTestItem


class PistolSpider(scrapy.Spider):
    name = 'pistol'
    allowed_domains = ['buff.163.com']

    def start_requests(self):
        # 从本地json文件中获取武器类型
        f = open(r'G:\BigData\buff_test\buff_test\spiders\allWeaponsEn.json', 'r')
        types = ast.literal_eval(f.read())
        types = types[self.name]
        for weapon in types:
            base_url = 'https://buff.163.com/api/market/goods?game=csgo' + '&category=' + weapon
            yield scrapy.Request(base_url, callback=self.parse_url)

    def parse_item(self, response):
        # 获取网站json
        text = response.text
        text = json.loads(text)
        for skin in text['data']['items']:  # 获取属性
            item = BuffTestItem()
            item['name'] = skin['name']
            item['id'] = skin['id']
            item['exterior'] = skin['goods_info']['info']['tags']['exterior']['localized_name']
            item['quality'] = skin['goods_info']['info']['tags']['quality']['localized_name']
            item['rarity'] = skin['goods_info']['info']['tags']['rarity']['localized_name']
            item['weapon'] = skin['goods_info']['info']['tags']['weapon']['localized_name']
            item['buy_max_price'] = skin['buy_max_price']
            item['buy_num'] = skin['buy_num']
            item['sell_min_price'] = skin['sell_min_price']
            item['sell_num'] = skin['sell_num']
            item['sell_reference_price'] = skin['sell_reference_price']
            yield item

    def parse_url(self, response):
        text = response.text
        text = json.loads(text)
        total_page = text['data']['total_page']
        weapon = text['data']['items'][0]['goods_info']['info']['tags']['weapon']['internal_name']
        for i in range(1, total_page + 1):
            url = 'https://buff.163.com/api/market/goods?game=csgo&page_num=' + str(i) + '&category=' + weapon
            # print('++++++++++++' + url + '++++++++++++++++')
            yield scrapy.Request(url=url, callback=self.parse_item)

