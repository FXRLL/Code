import requests
#UA：User-Agent（请求载体身份表示）
#网站会有UA检测
#UA伪装：让爬虫的请求载体身份标识伪装成浏览器
headers={
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36"
}
myurl="https://www.baidu.com/s?"
#处理url携带的参数,封装到字典中
keyword=input("enter the keyword:")
param={
    "wd":keyword
}
#将参数加到url后面
responce=requests.get(url=myurl,params=param,headers=headers)
page_text=responce.text
#存储内容
with open("E:\Code\Python/01-requests\search_page.html","w",encoding="utf-8")as fp:
    fp.write(page_text)
print("保存成功")