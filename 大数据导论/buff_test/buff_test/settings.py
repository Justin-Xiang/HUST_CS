# -*- coding: utf-8 -*-

# Scrapy settings for buff_test project
#
# For simplicity, this file contains only settings considered important or
# commonly used. You can find more settings consulting the documentation:
#
#     https://docs.scrapy.org/en/latest/topics/settings.html
#     https://docs.scrapy.org/en/latest/topics/downloader-middleware.html
#     https://docs.scrapy.org/en/latest/topics/spider-middleware.html

BOT_NAME = 'buff_test'

SPIDER_MODULES = ['buff_test.spiders']
NEWSPIDER_MODULE = 'buff_test.spiders'


# Crawl responsibly by identifying yourself (and your website) on the user-agent
USER_AGENT = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/80.0.3987.163 ' \
             'Safari/537.36 Edg/80.0.361.111'

# Obey robots.txt rules
ROBOTSTXT_OBEY = False

# Configure maximum concurrent requests performed by Scrapy (default: 16)
#CONCURRENT_REQUESTS = 32

# Configure a delay for requests for the same website (default: 0)
# See https://docs.scrapy.org/en/latest/topics/settings.html#download-delay
# See also autothrottle settings and docs
DOWNLOAD_DELAY = 3
# The download delay setting will honor only one of:
#CONCURRENT_REQUESTS_PER_DOMAIN = 16
#CONCURRENT_REQUESTS_PER_IP = 16

# Disable cookies (enabled by default)
COOKIES_ENABLED = False

# Disable Telnet Console (enabled by default)
#TELNETCONSOLE_ENABLED = False

# Override the default request headers:
DEFAULT_REQUEST_HEADERS = {
   'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
   'Accept-Language': 'en',
   'cookie': '_ntes_nuid=2a87a2ec5b71b3eba4d699d7fca14963; Device-Id=hB72ChKlhrB6JibF3mtD; _ga=GA1.2.1096138588.1586255682; _gid=GA1.2.465224196.1586255682; Locale-Supported=zh-Hans; game=csgo; NTES_YD_SESS=CCr5zB_usHvHQ3aM5Vle7Jg_FGhl0NnVhk1c.zRjbbU2JYRBJ0rMWQ7ctF.UswkeKCurj_iIyizDiaiHnP474c3sLkZdepgjktTn9aeJjyberMqXAUyifjwU0w3mqb67J_qeOQUG1VoVQp.zDzm8xpfgtxitN_Q2PesEFo7WGWWntXgIATM29nQyZdwASY4s.udnkPzMJ6MUpxLYrQHiULmjanvZx37h9Uez4TIo7cFvf; S_INFO=1586481786|0|3&80##|15527657001; P_INFO=15527657001|1586481786|1|netease_buff|00&99|zhj&1586308940&netease_buff#zhj&330700#10#0#0|&0|null|15527657001; session=1-x_pIf6u6VfYz3t3yZ0AWrIsPd-uvOh26fG9k7OGO4aHq2044446391; csrf_token=ImVlYzljNTJhNzZjMTYwMWQyNmJiNTllNzJmY2FkOGY4NjM3MDMwMmIi.EXFdoA.pKKIXFGhLk5-ZTQP6f9A_M1wcaY'}

# 修改编码为utf-8
FEED_EXPORT_ENCODING = 'utf-8'
# Enable or disable spider middlewares
# See https://docs.scrapy.org/en/latest/topics/spider-middleware.html
#SPIDER_MIDDLEWARES = {
#    'buff_test.middlewares.BuffTestSpiderMiddleware': 543,
#}

# Enable or disable downloader middlewares
# See https://docs.scrapy.org/en/latest/topics/downloader-middleware.html
#DOWNLOADER_MIDDLEWARES = {
#    'buff_test.middlewares.BuffTestDownloaderMiddleware': 543,
#}

# Enable or disable extensions
# See https://docs.scrapy.org/en/latest/topics/extensions.html
#EXTENSIONS = {
#    'scrapy.extensions.telnet.TelnetConsole': None,
#}

# Configure item pipelines
# See https://docs.scrapy.org/en/latest/topics/item-pipeline.html
#ITEM_PIPELINES = {
#    'buff_test.pipelines.BuffTestPipeline': 300,
#}

# Enable and configure the AutoThrottle extension (disabled by default)
# See https://docs.scrapy.org/en/latest/topics/autothrottle.html
#AUTOTHROTTLE_ENABLED = True
# The initial download delay
#AUTOTHROTTLE_START_DELAY = 5
# The maximum download delay to be set in case of high latencies
#AUTOTHROTTLE_MAX_DELAY = 60
# The average number of requests Scrapy should be sending in parallel to
# each remote server
#AUTOTHROTTLE_TARGET_CONCURRENCY = 1.0
# Enable showing throttling stats for every response received:
#AUTOTHROTTLE_DEBUG = False

# Enable and configure HTTP caching (disabled by default)
# See https://docs.scrapy.org/en/latest/topics/downloader-middleware.html#httpcache-middleware-settings
#HTTPCACHE_ENABLED = True
#HTTPCACHE_EXPIRATION_SECS = 0
#HTTPCACHE_DIR = 'httpcache'
#HTTPCACHE_IGNORE_HTTP_CODES = []
#HTTPCACHE_STORAGE = 'scrapy.extensions.httpcache.FilesystemCacheStorage'
