import requests
url = 'http://v16m-default.akamaized.net/df4da18be0d3ad517c41678c26f93097/6578af87/video/tos/alisg/tos-alisg-ve-0051c001-sg/oEimDGE37tXrDnB0Awf2isAoUVIUL57xA9uyrB/?mime_type=video_mp4'
headers={
    "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36"
}
video_data = requests.get(url=url,headers=headers).content
with open("C:\\Users\\lenovo\\Desktop\\video.mp4","wb")as fp:
    fp.write(video_data)
    print("finish")