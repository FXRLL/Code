import scrapy
from scrapy.linkextractors import LinkExtractor
from scrapy.spiders import CrawlSpider, Rule


class CrawlspiderSpider(CrawlSpider):
    name = "CrawlSpider"
    # allowed_domains = ["www.xxx.com"]
    start_urls = ["https://www.xxx.com"]
    # 规则解析器->连接提取器   allow=正则表达式 提取链接
    # callback回调进行制定规则解析
    # follow可以将连接提取器继续作用到连接提取器提取到的链接所对应的页面中
    rules = (Rule(LinkExtractor(allow=r"Items/"), callback="parse_item", follow=True),)

    def parse_item(self, response):
        item = {}
        #item["domain_id"] = response.xpath('//input[@id="sid"]/@value').get()
        #item["name"] = response.xpath('//div[@id="name"]').get()
        #item["description"] = response.xpath('//div[@id="description"]').get()
        return item
