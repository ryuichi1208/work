import pandas as pd
from pandas import Series,DataFrame
import numpy as np
from datetime import datetime
import time
import json
import requests
import csv
import matplotlib.pyplot as plt
from matplotlib.pylab import rcParams
%matplotlib inline
import seaborn as sns
sns.set_style('whitegrid')
rcParams['figure.figsize'] = 20, 10
from matplotlib.dates import DateFormatter

//CSVファイルの読み込み
btc_df = pd.read_csv("/var/www/html/zaif/btc.csv", names = ("date", "BTC price"))

//チャート作成期間の指定
btc_df = btc_df[-864:-1]

//チャート用date列へ変換
date_df = btc_df["date"].str[10:16]
btc_df = pd.concat([date_df, btc_df["BTC price"]], axis=1)

//BTC価格算出(検討：BTC以外にも対応する)
rm = btc_df.set_index("date").rolling(window=24).mean()
rstd = btc_df.set_index("date").rolling(window=24).std()
upper_band = rm + rstd * 2
lower_band = rm - rstd * 2

//チャート形式で作成
ax = btc_df.set_index("date").plot()
rm.columns = ["Rolling mean"]
rm.plot(ax=ax, color="#8FBC8F")
upper_band.columns = ["Upper band"]
upper_band.plot(ax=ax, color="#F4A460")
lower_band.columns = ["Lower band"]
lower_band.plot(ax=ax, color="#F4A460")
plt.legend(loc='best',
           fontsize=14,
           borderaxespad=0.,)
plt.tick_params(labelsize=14)
plt.savefig("/var/www/html/zaif/btc.png")
