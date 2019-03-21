x64 : hook.c test_x64
	gcc -shared -fPIC hook.c -o hook_x64.so -ldl -std=c99 -D _X64

x86 : hook.c test_x86
	gcc -shared -fPIC hook.c -o hook_x86.so -ldl -m32 -std=c99 -D _X86

test_x64 : test.c
	gcc -o test_x64 test.c

test_x86 : test.c
	gcc -o test_x86 test.c -m32

clean :
	rm *.so *.log *.txt test_x64 test_x86
