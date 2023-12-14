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
            yield scrapy.Request(url=new_url,callback=self.parse)