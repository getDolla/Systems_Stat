compile:
	gcc stat.c -o stat
run: stat
	./stat
clean:
	rm stat
	rm *~