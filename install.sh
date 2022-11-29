#!/bin/bash
mkdir ~/.youtty
mkdir ~/.youtty/data
touch ~/.youtty/data/history
touch ~/.youtty/data/kitten
echo "0" > ~/.youtty/data/kitten
cp ./api-caller.py ~/.youtty/
cp ./key_name.py ~/.youtty/
sudo make install

echo "Don't forget to add your API key to ~/.youtty/key_name.py"