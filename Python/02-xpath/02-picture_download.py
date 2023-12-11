# import requests
# from lxml import etree
# import os
# if not os.path.exists("C:\\Users\\lenovo\\Desktop\\4k"):
#     os.mkdir("C:\\Users\\lenovo\\Desktop\\4k")
# headers={
#     "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36"
# }
# url = 'https://pic.netbian.com/4kmeinv/'
# page_text = requests.get(url = url,headers = headers).text
# tree = etree.HTML(page_text)
# li_List = tree.xpath('//div[@class="slist"]/ul/li')
# for li in li_List:
#     img_src="https://pic.netbian.com"+li.xpath('./a/img/@src')[0]
#     img_name=li.xpath("./a/img/@alt")[0]+'.jpg'
#     #通用处理中文乱码方案
#     img_name=img_name.encode('iso-8859-1').decode('gbk')
#     print(img_name,img_src)
#     #请求图片并进行持久化存储
#     img_data=requests.get(url=img_src,headers=headers).content
#     img_path="C:\\Users\\lenovo\\Desktop\\4k\\"+img_name
#     with open(img_path,'wb') as fp:
#         fp.write(img_data)
#         print(img_name+"下载成功!")
        
import requests
from lxml import etree
import os
if not os.path.exists('C:\\Users\\lenovo\\Desktop\\4k'):
    os.mkdir('C:\\Users\\lenovo\\Desktop\\4k')
url = 'https://pic.netbian.com/e/search/result/?searchid=4318'
headers={
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36"
}
response = requests.get(url=url,headers=headers)
# 一种解决方案
# response.encoding = 'utf-8'
page_text = response.text
tree = etree.HTML(page_text)
li_list = tree.xpath('//div[@class="slist"]/ul/li')
for li in li_list:
    img_src = 'https://pic.netbian.com'+li.xpath('./a/@href')[0]
    new_response = requests.get(url=img_src, headers=headers).text
    new_tree = etree.HTML(new_response)
    download = 'https://pic.netbian.com'+ new_tree.xpath('//div[@class="photo-pic"]/a/img/@src')[0]
    img_name = new_tree.xpath('//div[@class="photo-pic"]/a/img/@alt')[0]+ '.png'
    # 通用处理中文乱码方案
    img_name = img_name.encode('iso-8859-1').decode('gbk')
    img_data = requests.get(url=download,headers=headers).content
    img_path = 'C:\\Users\\lenovo\\Desktop\\4k\\'+img_name
    with open(img_path,'wb') as fp:
        fp.write(img_data)
        print(img_name,'下载成功！！！')