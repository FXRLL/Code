import scrapy
from first.items import FirstItem

class CodeSpider(scrapy.Spider):
    # 爬虫源文件唯一标识
    name = "code"
    # 允许的域名：限定start_urls列表里哪些url可以请求发送
    # allowed_domains = ["www.baidu.com"]
    # 该列表中存放的url可以被自动进行请求的发送
    start_urls = ["https://www.baidu.com"]
    # 用于数据解析：response参数表示的是请求成功后对应的响应对象
    def parse(self, response):
        all_data=[]
        li_list=response.xpath('//*[@id="hotsearch-content-wrapper"]/li')
        for li in li_list:
            # 这里返回的是列表，而且列表元素一定是Selector类型的对象
            text_data=li.xpath("./a/span[2]/text()")[0].extract()
            print(text_data)
            # #需要封装成字典
            # dic={
            #     "data":text_data
            # }   
            # all_data.append(dic) 
        # return all_data
            item = FirstItem()
            item['text_data'] = text_data
            yield item
    
    
    
    
    # 持久化存储
        # 基于终端指令
            # 要求：只可以将parse方法的返回值存储到本地的文本文件中
            # 格式：json csv xml等，比较有限
            # scrapy crawl xxx -o filePath
        # 基于管道
            # 在item类中定义相关的属性
            # 将解析之后的数据封装到item类型的对象
            # 将item类型的对象提交到管道
            # 在管道类process_item中要将接收到的item类型对象存储
            # 在配置文件中手动开启管道