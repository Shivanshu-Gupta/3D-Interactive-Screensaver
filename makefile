all:
	cd src_barrier; make
doc:
	cd doc; make
oneone:
	cd src_oneone; make
execute:
	cd src_barrier; make screen
execute_oneone:
	cd src_oneone; make screen
clean:
	cd src_barrier; make clean
clean_oneone:
	cd src_oneone; make clean
