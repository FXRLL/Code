import scrapy


class CodeSpider(scrapy.Spider):
    name = "code"
    # allowed_domains = ["www.xxx.com"]
    start_urls = ["https://www.xxx.com"]
    # url模板
    url = 'www.https://www.xxx.com/?page=%doiafjoaifjeoaifjeoaf'
    page_num=2
    def parse(self, response):
        li_list=response.xpath("")
        for li in li_list:
            img_name=li.xpath("").extract_first()
            print(img_name)
        if self.page_num <=10:
            new_url = format(self.url%self.page_num)
            self.page_num+=1
            # 手动发起请求，如果符合条件则再次反复调用parse
            yield scrapy.Request(url=new_url,callback=self.parse,)  # meta={'key':value}请求传参，可以把参数传入回调函数
                                                                    # 回调函数调用时 item=response.meta['key']，然后正常执行便能让item再加上回调函数的新value
                                                                    # 有点类似于把若干二级函数接到了主函数上