DEBUG		=  1
DNLANG 	=  Dnlang
DNLANGIR=  $(DNLANG)/IR
DNLANGRT=  $(DNLANG)/runtime
OBJS		=		Main.o Dnscript.o Title.o Select.o Game.o \
						Event.o Keyboard.o Api.o Frame.o Object.o\
						Game/Load.o Game/Clear.o Game/Play.o Game/Menu.o Game/Player.o\
						Game/Bullet.o Game/Enemy.o\
						test/player_test.o test/enemy_test.o\

DN_OBJS =	  $(DNLANG)/Lexer.o $(DNLANG)/DnLexer.o $(DNLANG)/Token.o $(DNLANG)/Parser.o \
						$(DNLANG)/DnParser.o $(DNLANG)/Scope.o $(DNLANG)/Symbol.o $(DNLANG)/Symbols.o \
						$(DNLANGIR)/AST.o $(DNLANGIR)/ASTVisitor.o \

IN_OBJS	=		$(DNLANGRT)/DnInLexer.o $(DNLANGRT)/DnInParser.o $(DNLANGRT)/Interprter.o \

CURPATH = 	$(shell pwd)
INCLUDE =		$(CURPATH)/include
DNSCRIPT=		$(CURPATH)/Dnscript
DNTEST	=		$(CURPATH)/Dntest

CXX 		= 	g++ -fstack-protector-all -D_FORTIFY_SOURCE=2
LIBSDL_CXXFLAGS = $(shell sdl2-config --cflags)
LIBSDL_LDFLAGS  = $(shell sdl2-config --libs)

ifdef DEBUG
	CXXFLAG =		-Wall -I$(INCLUDE) -std=c++11 $(LIBSDL_CXXFLAGS) -fexceptions -g -o
else
	CXXFLAG =		-Wall -I$(INCLUDE) -std=c++11 $(LIBSDL_CXXFLAGS) -fexceptions -o
endif

LDFLAG	=		-Wl,-z,relro,-z,now -lSDL2_image $(LIBSDL_LDFLAGS) -lSDL2_gfx

CHKSEC	=		$(shell which checksec.sh)

all:
	$(MAKE) $(DNSCRIPT)

test:
	$(MAKE) $(DNTEST)

$(DNSCRIPT) : $(OBJS) $(DN_OBJS) $(IN_OBJS)
	$(CXX) $(CXXFLAG) $@ $^ $(LDFLAG)

$(DNTEST) : test/dnlang_test01.o $(DN_OBJS)
	$(CXX) $(CXXFLAG) $@ $^ $(LDFLAG)

security:
ifneq ("$(CHKSEC)","")
	$(CHKSEC) --file $(DNSCRIPT)
else
	echo '[**ERROR**] checksec.sh not found'
endif

clean :
	rm -rf $(DNSCRIPT) $(DNTEST)
	find . -regex ".*\.o" -exec rm -rf {} \;

%.o : %.cpp
	$(CXX) $(CXXFLAG) $*.o -c $*.cpp
