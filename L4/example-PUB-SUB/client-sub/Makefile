all: client-sub client-sub-even

client-sub : client-sub-odd.c
	gcc client-sub-odd.c -o client-sub-odd -lzmq

client-sub-even: client-sub-even.c
	gcc client-sub-even.c -o client-sub-even -lzmq

