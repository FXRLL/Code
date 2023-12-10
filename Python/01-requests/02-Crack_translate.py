import requests
headers={
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36"
}
post_url="https://fanyi.baidu.com/sug"
keyword=1
while(True):
    keyword=input("enter the keyword:")
    #post请求参数处理
    word={
        "kw":keyword
    }
    responce=requests.post(url=post_url,data=word)
    obj=responce.json()
    print(obj)