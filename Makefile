CXX = g++

BUILD_NAME	= poemReader

DIR_SRC = src

DIR_MANAGERS	= $(DIR_SRC)/managers
DIR_MENUS			= $(DIR_SRC)/menus
DIR_WRAPPERS	= $(DIR_SRC)/wrappers

CXXFLAGS := -Wall $(shell perl -MExtUtils::Embed -e ccopts -e ldopts)

CPP_FILES =\
	$(DIR_SRC)/main.cpp\
	$(DIR_MANAGERS)/DirectoryManager.cpp\
	$(DIR_MANAGERS)/FileManager.cpp\
	$(DIR_MANAGERS)/Manager.cpp\
	$(DIR_MENUS)/MainMenu.cpp\
	$(DIR_MENUS)/Menu.cpp\
	$(DIR_MENUS)/PoemMenu.cpp\
	$(DIR_MENUS)/VerseMenu.cpp\
	$(DIR_WRAPPERS)/PerlWrapper.cpp

OBJ_FILES = $(CPP_FILES:.cpp=.o)

$(BUILD_NAME): $(OBJ_FILES)
	$(CXX) -o $@ $(OBJ_FILES) $(CXXFLAGS)

.PHONY: clean

clean:
	rm $(OBJ_FILES) $(BUILD_NAME)
