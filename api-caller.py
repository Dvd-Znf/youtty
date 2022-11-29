import sys
import json
import requests
import key_name
import subprocess

from key_name import api_key
from os.path import expanduser
home = expanduser("~")
kitten_bool = False

history = open(home + "/.youtty/data/history","w")
kitten = open(home + "/.youtty/data/kitten","r")
value = kitten.read()
if(value == '1'):
    kitten_bool = True
    kitten.close()

URL = "https://youtube.googleapis.com/youtube/v3/search?part=snippet&q=" + sys.argv[1] + "&type=video&key=" + api_key
response = requests.get(url = URL)
data = response.json()

for i in range(3):
    print(data["items"][i]['id']['videoId'])
    print(data["items"][i]['snippet']['title'])
    if(kitten_bool):
        subprocess.run(["kitty", "+kitten","icat","--align","left",data["items"][i]['snippet']['thumbnails']['high']['url']])
    if(input('Does this look right?(Y/n)') == 'Y'):
        history.write(data["items"][i]['id']['videoId'] + "\n")
        history.close
        break

if(kitten_bool):
    kitten = open(home + "/.youtty/data/kitten","w")
    kitten.write("0")
    kitten.close()