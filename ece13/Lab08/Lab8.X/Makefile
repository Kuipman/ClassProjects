RPG: Lab08_main.o Game.o Player.o
	gcc -o RPG Lab08_main.o Game.o Player.o

Lab08_main.o: Lab08_main.c UNIXBOARD.h Game.h Player.h
	gcc -c Lab08_main.c

Game.o: Game.c Game.h Player.h
	gcc -c Game.c

Player.o: Player.c Player.h Game.h
	gcc -c Player.c

clean:
	rm *.o
