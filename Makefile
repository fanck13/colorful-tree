all:
	make -C src
	make -C test

.PHONY:
clean:
	- rm -rf ./out/*