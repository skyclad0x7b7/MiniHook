hook.so : hook.c test
	gcc -shared -fPIC hook.c -o hook.so -ldl -m32

test : test.c
	gcc -o test test.c -m32

clean :
	rm *.so test
