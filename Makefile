CPP = g++
CPPFLAGS = -W -Wall

PATH_INCLUDES = Includes
PATH_SOURCES = Sources

BINARY = Strage
LIBRARIES = -lSDL2
SOURCES = $(shell find $(PATH_SOURCES) -name "*.cpp")

# Program configuration
CPPFLAGS += -DCONFIGURATION_DISPLAY_WIDTH=800
CPPFLAGS += -DCONFIGURATION_DISPLAY_HEIGHT=600
CPPFLAGS += -DCONFIGURATION_ENABLE_LOGGING=1

all:
	$(CPP) $(CPPFLAGS) -I$(PATH_INCLUDES) $(SOURCES) $(LIBRARIES) -o $(BINARY)

clean:
	rm -f $(BINARY)
