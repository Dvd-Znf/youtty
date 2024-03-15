DESTDIR ?= /usr/bin

youtty: src/main.c
	gcc src/main.c -o youtty


install: youtty
	install youtty $(DESTDIR)/youtty

uninstall: youtty
	rm -v youtty $(DESTDIR)/youtty

clean: 
	rm youtty