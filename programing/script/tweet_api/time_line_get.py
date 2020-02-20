#coding: UTF-8
from requests_oauthlib import OAuth1Session
import json
import settings

twitter = OAuth1Session(settings.CONSUMER_KEY, settings.CONSUMER_SECRET, settings.ACCESS_TOKEN, settings.ACCESS_TOKEN_SECRET)

params = {}
req = twitter.get("https://api.twitter.com/1.1/statuses/home_timeline.json", params = params)

timeline = json.loads(req.text)

for tweet in timeline:
  print tweet["text"]
