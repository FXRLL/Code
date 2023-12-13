from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver import ActionChains

# # 无头浏览器
# from selenium.webdriver.chrome.options import Options
# chrome_options = Options()
# chrome_options.add_argument('--headless')
# chrome_options.add_argument('--disable-gpu')

# #规避被检测的风险
# from selenium.webdriver import ChromeOptions
# option = ChromeOptions()
# option.add_experimental_option('excludeSwitches',['enable-automation'])

from lxml import etree
from time import sleep
#实例化并发起请求
bro=webdriver.Chrome()
bro.get("https://www.bilibili.com/")
tree=etree.HTML(bro.page_source)
# 获取指定标签内容
sometext=tree.xpath('//*[@id="i_cecream"]/div[2]/main/div[2]/div/div[1]/div[2]/div/div[2]/div/div/h3/a/text()')
print(sometext[0])
sleep(2)
# 执行js程序
bro.execute_script("window.scrollTo(0,document.body.scrollHeight)")
sleep(2)
# 动作链
# action = ActionChains(bro)
# action.click_and_hold(bro.find_element(#))
# action.move_by_offset(50,0).perform()
# 切换作用域
# bro.switch_to.frame("iframeaRseult")
# 定位特定标签
search_input=bro.find_element(By.XPATH,'//*[@id="nav-searchform"]/div[1]/input')
search_input.send_keys("风信然")
btn=bro.find_element(By.XPATH,'//*[@id="nav-searchform"]/div[2]')
# 点击操作
btn.click()
sleep(2)
# 回退
bro.back()
sleep(2)
# 前进
bro.forward()
# 退出
bro.quit()
