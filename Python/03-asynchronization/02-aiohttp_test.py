import aiohttp
import asyncio
urls=[
    "1","2","3"
]
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36'
}
async def get_page(url):
    async with aiohttp.ClientSession() as session:
        #get(),post()
        #headers,params/data,proxy=""
        async with await session.get(url) as response:
            #text()返回字符串形式的响应数据
            #read()返回二进制形式的响应数据
            #json()返回的是json对象
            page_text = await response.text()
            print(page_text)
#后面和asyncoio操作一致