# youtty
## Watch youtube from the tty
Youtty is a simple program that combines: Youtube Data API, youtube-dl and vlc to allow you to easily watch youtube videos from the tty  
![Screenshot](/Screenshot.png)  
## Dependencies:  
- python  
- youtube-dl  
- vlc  
- make and gcc (Build dependencies)  
## How to install (from source):
### Step 0:
Clone this repo :P  
### Step 1:
Run the install.sh script;  
The automated script will create necessary data directories  
But it will also compile the main.c file from source
```
$ ./install.sh  
```
(You might need to give execute permision to the install script)
```
$ chmod +x ./install.sh  
```
### Step 2:
Add your own youtube data api key to the ~/.youtty/key_name.py file  
Creating a youtube data key is 100% free and very simple (Google is your friend!!!)  
(In the future i might add my own key for the public)  
## How it works?
The main.c file is really just a glorified script  
It will call to the api-caller.py file located under ~/.youtty to then asks the youtube data api for a specific search result  
It will then trow that into a file  
After that youtube-dl downloads the video  
And vlc is used to play it  
## Why?
Graphics on a plain tty look awsome!!!!  
## Todo:
- [X] Add support for the kitty terminal to preview thumbnail
- [ ] Add somekind of "history" or "save video" mechanic
- [ ] Known bug: youtube-dl may not download a video sometimes
# Credit (for some AWSOME dependencies):
- youtube-dl (Its amazing)
- vlc (mindblowing)
  
Please open an issue in case you find one  
<3  