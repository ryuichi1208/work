import pandas as pd
from pandas import Series,DataFrame
import numpy as np
from datetime import datetime
import time
import json
import requests
import csv
import sys, codecs

//現在時刻取得
date = datetime.now().strftime("%Y/%m/%d %H:%M:%S")

//Zaif取引所APIの定形処理
response = requests.get('https://api.zaif.jp/api/1/last_price/btc_jpy')
if response.status_code != 200:
    raise Exception('return status code is {}'.format(response.status_code))
res_dict = json.loads(response.text)
btc_price = res_dict['last_price']
#[現在時刻、売買価格]のリストを作成
btc_list = [date, btc_price]

//CSV出力
f = open("/var/www/html/zaif/btc.csv", "a")
writer = csv.writer(f, lineterminator='\n')
writer.writerow(btc_list)
f.close()


