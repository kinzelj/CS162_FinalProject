# ***************************************************************
# Variables
# ***************************************************************
PROJ = FinalProject 
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -pedantic
EXE = $(PROJ)
ZIP =_Kinzel_Josh.zip
.PHONY : clean debug zip

# ***************************************************************
# Source Files 
# ***************************************************************
SRC  = main.cpp
SRC += intValidation.cpp 
SRC += menu.cpp
SRC += WIN_32_ClearScreen.cpp 
SRC += EmptyUnit.cpp 
SRC += Game.cpp 
SRC += HorizUnit.cpp 
SRC += Item.cpp 
SRC += ItemUnit.cpp 
SRC += MainSpace.cpp 
SRC += Person.cpp 
SRC += Space.cpp
SRC += SpaceUnit.cpp 
SRC += TunnelSpace.cpp 
SRC += VentSpace.cpp 
SRC += HallwaySpace.cpp 
SRC += ShopSpace.cpp 
SRC += ClosetSpace.cpp 
SRC += VertUnit.cpp 

# ***************************************************************
# Create object files 
# ***************************************************************
OBJS = $(SRC:.cpp=.o)

# ***************************************************************
# Compile binary
# ***************************************************************
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^

# ***************************************************************
# Debug, create .zip, clean object/exe files
# ***************************************************************
debug: $(EXE)
	@valgrind --leak-check=full ./$(EXE)

zip:
	zip -D $(EXE)$(ZIP) *.cpp *.h makefile

clean:
	rm -f *.zip *.o $(EXE) 
