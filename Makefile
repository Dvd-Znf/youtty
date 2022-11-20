DESTDIR ?= /usr/bin

youtty: main.c
	gcc main.c -o youtty


install: youtty
	install youtty $(DESTDIR)/youtty

uninstall: youtty
	rm -v youtty $(DESTDIR)/youtty

clean: 
	rm youtty