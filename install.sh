#!/bin/bash
mkdir ~/.cache/youtty
mkdir ~/.cache/youtty/data
#touch ~/.youtty/data/history Now using cache dir ~/.cache/youtty
touch ~/.cache/youtty/data/kitten
echo "0" > ~/.cache/youtty/data/kitten
mkdir ~/.youtty
cp ./api-caller.py ~/.youtty/
cp ./key_name.py ~/.youtty/
sudo make install

echo "Don't forget to add your API key to ~/.youtty/key_name.py"