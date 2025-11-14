var := $(patsubst %.c, %.o,$(wildcard *.c))
calc.exe : $(var)
	gcc -o invert $(var)
clean :
	rm *.o *.exe