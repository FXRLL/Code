# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html


# useful for handling different item types with a single interface
from itemadapter import ItemAdapter
import pymysql

class FirstPipeline:
    # 专门用来处理item类型对象
    # 该方法接受爬虫文件提交的item对象
    # 该方法每接收到一个item就会被调用一次
    fp = None
    # 重写父类方法：该方法只在开始爬虫的时候调用一次
    def open_spider(self,spider):
        print("开始爬虫...")
        self.fp = open("C:\\Users\\lenovo\\Desktop\\news.txt",'w',encoding='utf-8')
    def process_item(self, item, spider):
        text_data = item['text_data']
        self.fp.write(text_data+'\n')
        # 多个管道时，return非常重要，没有return时只会传给一个管道，有return才能按照优先级传给多个管道
        return item
    def close_spider(self,spider):
        print("爬虫结束！")
        self.fp.close()
        
# class mysqlPipeline:
#     conn = None
#     cursor = None
#     def open_spider(self,spider):
#         self.conn = pymysql.Connect(host="127.0.0.1",port=3306,user='root',passwold='123456',charset="utf-8")
#     def process_item(self, item, spider):
#         self.cursor = self.conn.cursor()
#         try:
#             self.cursor.execute('insert into ...牛魔')
#             self.conn.commit()
#         except Exception as e:
#             print(e)
#             self.conn.rollback()
#             return item
#     def close_spider(self,spider):
#         self.cursor.close()
#         self.conn.close()