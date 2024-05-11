DESTDIR ?= /usr/bin

youtty: src/main.c
	gcc src/main.c -o youtty


install: youtty
	mkdir -p ~/.cache/youtty
	mkdir ~/.cache/youtty/data
	touch ~/.cache/youtty/data/kitten
	echo "0" > ~/.cache/youtty/data/kitten
	mkdir -p ~/.local/share/youtty
	cp ./src/api-caller.py ~/.local/share/youtty
	cp -n ./src/key_name.py ~/.local/share/youtty
	echo "Don't forget to add your API key to ~/.local/share/youtty/key_name.py"
	install youtty $(DESTDIR)/youtty

uninstall: youtty
	rm -v youtty $(DESTDIR)/youtty

clean: 
	rm youtty
