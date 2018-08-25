#!/usr/bin/env python
# -*- coding:utf-8 -*-

import tweepy
import datetime

class Listener(tweepy.StreamListener):
    def on_status(self, status):
        status.created_at += datetime.timedelta(hours=9)

        #favo when reply
        if str(status.in_reply_to_screen_name)==Twitter_ID and str(status.user.screen_name)!=Twitter_ID:
            print(str(datetime.datetime.today()))
            api.create_favorite(status.id)
        return True

    def on_error(self, status_code):
        print('Error code:' + str(status_code))
        return True

    def on_timeout(self):
        print('Timeout error')
        return True



consumer_key = ""#access s and get consumer key
consumer_secret = ""
access_token = ""
access_secret = ""
Twitter_ID = ""#Your TwitterID(Don't need @)

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_secret)
api = tweepy.API(auth)

listener = Listener()
stream = tweepy.Stream(auth, listener)
stream.userstream()
