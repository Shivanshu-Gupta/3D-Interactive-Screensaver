all:
	cd src; make
doc:
	cd doc; make
execute:
	./screensaver $(NUM_THREADS)
clean:
	cd src; make clean
