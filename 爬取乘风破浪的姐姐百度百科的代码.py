import pandas as pd
import requests
import re
import numpy as np
from pyquery import PyQuery as pq
import matplotlib.pyplot as plt

#添加头，防止反爬虫
headers = {
    'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.116 Safari/537.36'
}
r = requests.get('https://baike.baidu.com/item/乘风破浪的姐姐', headers=headers)
r.encoding=r.apparent_encoding

doc=pq(r.text)
data=doc('.lemma-summary .para')
div=data('div:nth-child(3)')
str1=str(div)

results=re.findall('href="(.*?)".*?>(.*?)</a>',str1,re.S) #正则表达式截取str中 href=''和 人名部分
results=np.array(results) #将结果转换成numpy数组

url=results[:,0]            #获取每个人信息对应的url地址
name=results[:,1]           #获取每个人的名字
ename=[]                    #选手的英文名
constellation=[]            #选手的星座
height=[]                   #选手的身高
birthday=[]                 #选手的出生日期


for i in range(30):
    URL='''https://baike.baidu.com'''+url[i]
    r_of_each=requests.get(URL,headers=headers)
    doc_of_each=pq(r_of_each.text)
    div_of_each_l=doc_of_each('.basicInfo-block.basicInfo-left')      #定位到该节点，查询该节点的信息
    div_of_each_r=doc_of_each('.basicInfo-block.basicInfo-right')


    #获取所有选手的星座，网页上没有的设为未知
    if i==2:
        constellation_of_each = re.search("星.*?座</dt>\n<.*?>\n(.*?)\n</dd>", str(div_of_each_l) + str(div_of_each_r),re.S)
    else:
        constellation_of_each=re.search("星.*?座</dt>\n<.*?>\n<.*?>(.*?)</a>",str(div_of_each_l)+str(div_of_each_r),re.S) #选手星座
    constellation.append(constellation_of_each.group(1)) if constellation_of_each else constellation.append('未知')


    #删去多余节点
    div_of_each_l.find('sup').remove()
    div_of_each_l.find('a').remove()
    div_of_each_r.find('sup').remove()
    div_of_each_r.find('a').remove()

    #获取所有选手的身高（cm），网页上没有的设为未知
    height_of_each = re.search("身.*?高</dt>\n<.*?>\n(.*?)\n</dd>", str(div_of_each_l) + str(div_of_each_r), re.S)
    height.append(height_of_each.group(1)) if height_of_each else height.append('未知')

    #获取所有选手的英文名，网页上没有的设为none
    ename_of_each=re.search('.*?外文名</dt>\n<.*?>\n(.*?)\n</dd>',str(div_of_each_l),re.S)  #选手英文名
    ename.append(ename_of_each.group(1)) if ename_of_each else ename.append('none')

    #获取所有选手的出生日期，网页上缺少该信息的设为未知
    birthday_of_each = re.search("出生日期</dt>\n<.*?>\n(.*?)\n</dd>", str(div_of_each_l) + str(div_of_each_r), re.S)
    birthday.append(birthday_of_each.group(1)) if birthday_of_each else birthday.append('未知')


#用DataFrame格式存取选手信息

# 显示所有行(参数设置为None代表显示所有行，也可以自行设置数字)
# pd.set_option('display.max_columns',None)
# 显示所有列
# pd.set_option('display.max_rows',None)
# 设置数据的显示长度，默认为50
# pd.set_option('max_colwidth',200)
# 禁止自动换行(设置为Flase不自动换行，True反之)
# pd.set_option('expand_frame_repr', False)

df=pd.DataFrame({
    'Name':name,
    'Ename':ename,
    'Height':height,
    'Constellation':constellation,
    'Birthday':birthday
},index=range(1,31))

#将文件存入本地csv文件中

df.to_csv('D:\\information\\Information.csv',encoding='utf-8')

#读取文件
df=pd.read_csv('D:\\information\\Information.csv')


#将身高数据可视化：

#删除身高项为未知的数据
df_height=df.copy()
df_height=df_height[-df_height.Height.isin(['未知'])]
h=list(df_height['Height'])
height=[x[0:3] for x in h]
plt.rcParams['font.sans-serif']=['SimHei']
#将身高分为三个范围
labels=['小于165cm','165~170cm','大于170cm']

counter1 = counter2 = counter3 = 0
for each in height:
    if int(each)<165:
        counter1+=1
    elif int (each)>170:
        counter3+=1
    else:
        counter2+=1

sizes=[counter1,counter2,counter3]
#画出身高分布饼状图
plt.pie(sizes,labels=labels,autopct='%1.1f%%',shadow=False,startangle=150)
plt.title('身高分布图')
plt.show()


#出生年份可视化
df_birthday=df.copy()

#删除出生日期项为未知的数据
b=df_birthday[-df_birthday.Birthday.isin(['未知'])]
birthday=list(b['Birthday'])
#删除出生日期不含年份的数据
length=len(birthday)
for i in range(len(birthday)):
    if '年' in birthday[i]:
        birthday.append(birthday[i])
birthday=birthday[length:]
#获取年份信息
for i in range(len(birthday)):
    birthday[i]=birthday[i][0:4]

year=list(set(birthday))
year.sort()

year_num=[]
for i in range(len(year)):
    counter=0
    for each in birthday:
        if(each == year[i]):
            counter+=1
    year_num.append(counter)
#画出出生年份柱状图
plt.bar(year,year_num)
plt.title('出生年份柱状图')
plt.show()