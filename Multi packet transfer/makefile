all: result

result: main.o bit.o precalc.o byte.o better.o
		gcc obj/main.o obj/bit.o obj/precalc.o obj/byte.o obj/better.o -o lib/result
		./lib/result

main.o: src/main.c
		gcc -c src/main.c -o obj/main.o

bit.o: src/bit.c
		gcc -c src/bit.c -o obj/bit.o

precalc.o: src/precalc.c
		gcc -c src/precalc.c -o obj/precalc.o

byte.o: src/byte.c
		gcc -c src/byte.c -o obj/byte.o

better.o: src/better.c
		gcc -c src/better.c -o obj/better.o

clean:
	rm -rf obj/*.o
	rm -f lib/result
