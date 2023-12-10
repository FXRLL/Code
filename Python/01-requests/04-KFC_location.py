import requests
import json
myurl="https://www.kfc.com.cn/kfccda/ashx/GetStoreList.ashx?op=keyword"
city=input("请输入所查询城市：")
param={
    'cname':'' ,
    'pid':'' ,
    'keyword': city,
    'pageIndex': '1',
    'pageSize': '10',
}
headers={
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36"
}
response=requests.post(url=myurl,data=param)
city_text=response.text
print(city_text)