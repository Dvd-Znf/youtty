#!/bin/bash
mkdir ~/.cache/youtty
mkdir ~/.cache/youtty/data
#touch ~/.youtty/data/history Now using cache dir ~/.cache/youtty
touch ~/.cache/youtty/data/kitten
echo "0" > ~/.cache/youtty/data/kitten
#mkdir ~/.youtty
mkdir ~/.local/share/youtty
cp ./api-caller.py ~/.local/share/youtty
cp ./key_name.py ~/.local/share/youtty
sudo make install

echo "Don't forget to add your API key to ~/.local/share/youtty/key_name.py"
#echo "You can also change the api key using: youtty -<feature to be added>"