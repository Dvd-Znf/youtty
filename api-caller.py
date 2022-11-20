import sys
import json
import requests
import key_name

from key_name import api_key
from os.path import expanduser
home = expanduser("~")

history = open(home + "/.youtty/data/history","w")


URL = "https://youtube.googleapis.com/youtube/v3/search?part=snippet&q=" + sys.argv[1] + "&type=video&key=" + api_key
response = requests.get(url = URL)
data = response.json()

for i in range(3):
    print(data["items"][i]['id']['videoId'])
    print(data["items"][i]['snippet']['title'])
    print(data["items"][i]['snippet']['thumbnails']['high']['url'])
    if(input('Does this look right?(Y/n)') == 'Y'):
        history.write(data["items"][i]['id']['videoId'] + "\n")
        history.close
        break