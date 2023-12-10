import requests
import json
myurl="https://movie.douban.com/j/chart/top_list"
param={
    'type': '11',
    'interval_id': '100:90',
    'action': '',
    'start': '0',
    'limit': '20'
}
headers={
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36"
}
response=requests.get(url=myurl,params=param,headers=headers)
list_data=response.json()
fp=open("C:/Users/lenovo/Desktop/movie_rank.json","w",encoding="utf-8")
json.dump(list_data,fp=fp,ensure_ascii=False)
print("保存成功")