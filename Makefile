CC := gcc -std=c++11
CFLAGS := -Wall -pedantic -Wextra #-g
INC := -lstdc++ -Iinclude/
#LIB :=

SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGETFILE := Run
TARGET := $(TARGETDIR)/$(TARGETFILE)

SRCEXT := cpp
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(SOURCES: .$(SRCEXT)=.o)

#$(TARGET): $(OBJECTS)
$(TARGETFILE): $(OBJECTS)
	mkdir -p $(TARGETDIR)
	$(CC) $^ -o $@ $(CFLAGS) $(INC)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)

.PHONY: clean
clean:
	rm -f -r $(BUILDDIR) $(TARGETDIR) $(TARGETFILE)
