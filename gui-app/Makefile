CFLAGS=-g -Wall -Wextra -pedantic -std=c11 `pkg-config --cflags --libs gtk+-2.0`
build:
	$(CC) do_nothing_gui.c -o do_nothing_gui $(CFLAGS)

po:
	sh ./gen_locale_files.sh

locales:
	sh ./gen_mo_files.sh
