# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# https://docs.scrapy.org/en/latest/topics/items.html

import scrapy


class BuffTestItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    buy_max_price = scrapy.Field()
    buy_num = scrapy.Field()
    exterior = scrapy.Field()  # 外观（即磨损）
    quality = scrapy.Field()  # 类别（普通，StatTrak等）
    rarity = scrapy.Field()  # 品质（隐秘，军规级等）
    id = scrapy.Field()  # 皮肤id
    sell_min_price = scrapy.Field()
    sell_num = scrapy.Field()
    sell_reference_price = scrapy.Field()
    name = scrapy.Field()
    weapon = scrapy.Field()
    pass
