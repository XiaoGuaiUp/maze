mazeway:mazeway.c seqstack.c
	gcc -g -o $@ $^

.PHONY:clean
	clean:
		rm -f mazeway
