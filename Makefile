DEBUG		=  1
OBJS		=		Main.o Dnscript.o Title.o Select.o Game.o \
						Event.o Keyboard.o Api.o Frame.o Object.o\
						Game/Load.o Game/Clear.o Game/Play.o Game/Menu.o Game/Player.o\
						Game/Bullet.o Game/Enemy.o\
						test/player_test.o test/enemy_test.o

CURPATH = 	$(shell pwd)
INCLUDE =		$(CURPATH)/include
DNSCRIPT=		$(CURPATH)/Dnscript

CXX 		= 	g++ -fstack-protector-all -D_FORTIFY_SOURCE=2
LIBSDL_CXXFLAGS = $(shell sdl2-config --cflags)
LIBSDL_LDFLAGS  = $(shell sdl2-config --libs)

ifdef DEBUG
	CXXFLAG =		-Wall -I$(INCLUDE) -std=c++11 $(LIBSDL_CXXFLAGS) -Wdelete-incomplete -g -o
else
	CXXFLAG =		-Wall -I$(INCLUDE) -std=c++11 $(LIBSDL_CXXFLAGS) -Wdelete-incomplete -o
endif

LDFLAG	=		-Wl,-z,relro,-z,now -lSDL2_image $(LIBSDL_LDFLAGS) -lSDL2_gfx

CHKSEC	=		$(shell which checksec.sh)

$(DNSCRIPT) : $(OBJS)
	$(CXX) $(CXXFLAG) $@ $^ $(LDFLAG)

security:
ifneq ("$(CHKSEC)","")
	$(CHKSEC) --file $(DNSCRIPT)
else
	echo '[**ERROR**] checksec.sh not found'
endif

clean :
	rm -rf $(DNSCRIPT)
	find . -regex ".*\.o" -exec rm -rf {} \;

%.o : %.cpp
	$(CXX) $(CXXFLAG) $*.o -c $*.cpp
