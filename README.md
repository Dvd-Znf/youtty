# youtty
![GitHub Release](https://img.shields.io/github/v/release/Dvd-Znf/youtty?include_prereleases&logo=GitHub&label=Latest%20release%3A&color=lightgreen)
![AUR Version](https://img.shields.io/aur/version/youtty?logo=Arch%20Linux&label=Latest%20AUR%20version%3A)
## Watch youtube from the tty
Youtty is a simple program that combines: Youtube Data API, yt-dlp and vlc to allow you to easily watch youtube videos from the tty  
![Screenshot](/Screenshot.png)  
## Dependencies:  
- python      
- python-requests (module)       
- yt-dlp   
- vlc  
- make and gcc (Build dependencies)
## How to install (Arch Linux):
The youtty program is now available from the AUR!!!   
https://aur.archlinux.org/packages/youtty    
If you use an aur helper, then just do that.
Here are the steps for manual aur install:
### Step 1:
Clone the pkgbase
```
$ git clone https://aur.archlinux.org/youtty.git
```
### Step 2 (optional):
Verify the that the PKGBUILD is ok
```
$ cd youtty
$ cat PKGBUILD
```
### Step 3:
Build, install and get all dependencies
```
$ makepkg -sirc
```
### Step 4:
Check [Step 2](https://github.com/Dvd-Znf/youtty#step-2) from manual install
## How to manually install:
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
Creating a youtube data key is 100% free and very simple   
You may also use the `--no-key` flag instead, but this will limit some functionality(No video selection, No Thumbnail preview)     
Using `--no-key` may also lead to some other non desired behavior, please submit issue if you find and be ready to CTR+C.     
## How it works?
The main.c file is really just a glorified script  
It will call to the api-caller.py file located under ~/.youtty to then asks the youtube data api for a specific search result  
It will then throw that into a file  
After that yt-dlp downloads the video  
And vlc is used to play it  
## Why?
Graphics on a plain tty look awsome!!!!  
## Todo:   
- ~~Consider adopting [this](http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html) specification regarding the use of data dir (Use `~/.cache` instead of `~/.youtty/history` and `~/.youtty/content` idk)~~      
    - ~~There is still work here to be done with `kitty` and `content`!!~~
    - ~~Could also entirely replace `~/.youtty` (Change where to store the API key)~~
    - ~~Ability to change API key directly from the cli~~      
- Reorganize repo       
- Add some version.h idk     
- Add suport for mpv       
# Credit (for some AWSOME dependencies):
- youtube-dl && yt-dlp (Its amazing)
- vlc (mindblowing)
  
Please open an issue in case you find one  
<3  
