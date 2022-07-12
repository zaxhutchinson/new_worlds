################################################################################
### CUSTOMIZE BELOW HERE #######################################################

CC=g++ # define the compiler to use
TARGET=new_worlds # define the name of the executable

# RELEASE
# CFLAGS= -c -std=c++20 -Wall -O3
# DEBUG
CFLAGS= -c -std=c++20 -Wall -g3

LFLAGS= -Llib -lm #-lsfml-graphics -lsfml-window -lsfml-system -lfmt
SRCDIR = src
OBJDIR = obj
INCLUDE = -Iinc
SOURCES = $(foreach d,$(SRCDIR),$(wildcard $(d)/*.cpp))
OBJECTS = $(foreach d,$(SRCDIR),$(subst $(d),$(OBJDIR),$(wildcard $(d)/*.cpp)))

################################################################################
### DO NOT EDIT THE FOLLOWING LINES ############################################

# define list of objects
OBJS=$(subst .cpp,.o,$(OBJECTS))
# the target is obtained linking all .o files
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@

purge: clean
	rm -f $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

show:
	@echo 'SOURCES:   ' $(SOURCES)
	@echo 'OBJECTS:   ' $(OBJECTS)
	@echo 'OBJS:      ' $(OBJS)

################################################################################
################################################################################