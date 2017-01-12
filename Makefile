CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = CC3K
OBJECTS = main.o game.o map.o textdisplay.o cell.o subject.o character.o enemy.o human.o dwarf.o elf.o halfling.o orcs.o merchant.o player.o admin.o shade.o vampire.o goblin.o troll.o drow.o gold.o potion.o itemfactory.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
