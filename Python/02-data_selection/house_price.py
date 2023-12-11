import requests
from lxml import etree
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36'
}
url = 'https://anqiu.58.com/ershoufang/'
page_text = requests.get(url = url,headers = headers).text
tree = etree.HTML(page_text)
div_List = tree.xpath('//section[@class = "list"]/div')
fp = open("C:\\Users\\lenovo\\Desktop\\house_price.txt","w",encoding="utf-8")
for div in div_List:
    title = div.xpath('./a/div[2]//div/h3/text()')[0]
    price = div.xpath('./a/div[2]/div[2]/p[1]/span[1]/text()')[0]
    fp.write(title+'\n')
    fp.write(price+"万\n")
    print(title)
    print(price+"万")