hook_x64.so : hook.c test
	gcc -shared -fPIC hook.c -o hook_x64.so -ldl

hook_x86.so : hook.c test
	gcc -shared -fPIC hook.c -o hook_x86.so -ldl -m32

test_x64 : test.c
	gcc -o test_x64 test.c

test_x86 : test.c
	gcc -o test_x86 test.c -m32

clean :
	rm *.so *.log *.txt test
