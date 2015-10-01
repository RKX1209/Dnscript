OBJS		=		Main.o Dnscript.o Title.o Select.o Game.o \
						Image.o Keyboard.o Api.o Object.o

CURPATH = 	$(shell pwd)
INCLUDE =		$(CURPATH)/include
DNSCRIPT=		$(CURPATH)/Dnscript

CXX 		= 	g++ -fstack-protector-all -D_FORTIFY_SOURCE=2
LIBPNG_CXXFLAGS = $(shell libpng-config --cppflags)
LIBPNG_LDFLAGS  = $(shell libpng-config --ldflags)
LIBSDL_CXXFLAGS = $(shell sdl-config --cflags)
LIBSDL_LDFLAGS  = $(shell sdl-config --libs)

CXXFLAG =		-Wall -I$(INCLUDE) -std=c++11 $(LIBPNG_CXXFLAGS) $(LIBSDL_CXXFLAGS) -Wdelete-incomplete -o
LDFLAG	=		-Wl,-z,relro,-z,now -lglut -lGLU -lGL $(LIBPNG_LDFLAGS) $(LIBSDL_LDFLAGS)

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
	rm -rf $(DNSCRIPT) *.o

%.o : %.cpp
	$(CXX) $(CXXFLAG) $*.o -c $*.cpp
