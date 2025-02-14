import sys
import json
import requests
import key_name
import subprocess
import os


from key_name import api_key
from os.path import expanduser
home = expanduser("~")
kitten_bool = False

if(api_key == "Youtube DATA key goes here!!!"):
    print('You probably forgot to add a youtube data api key\nYou can change the curent API key by using the --change-key flag')
    print('You can also still use youtty by passing the --no-key flag')
    print('This will use yt-dlp ytsearch which will remove some features like: Thumbnail preview, Video Selection, etc...')
    print('It could also lead to unwanted behaivior\nSo use --no-key at your own risk')
    exit(1)


history_path = os.path.join(home, ".cache/youtty/data/history")

directory = os.path.dirname(history_path)
if not os.path.exists(directory):
    os.makedirs(directory)

history = open(history_path, "w")


kitten = open(home + "/.cache/youtty/data/kitten","r")
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
    user_input = input('Does this look right?(Y/n)').lower()
    if not user_input:
        user_input = 'y'
    if( user_input == 'y'):
        history.write(data["items"][i]['id']['videoId'] + "\n")
        history.close()
        break

print('Err: Please try to specify one of the 3 videos from above (1,2,3) \n or type q to quit and cancel')
try:
    tmp=int(input())
    if(tmp in range(1,4)):
     history.write(data["items"][tmp-1]['id']['videoId'] + "\n")
     history.close
    else:
     exit()
except ValueError:
    exit()

if(kitten_bool):
    kitten = open(home + "/.cache/youtty/data/kitten","w")
    kitten.write("0")
    kitten.close()