# Commands #

# make:      Builds the program for the OS
# clean:     Clean all the .o and executable files from the OS folders

################################################################################
#---------------------------------# VARIABLES #--------------------------------#
################################################################################

# Compiler #
CXX      = g++
LFLAGS   = `pkg-config --libs --static $(ALLEGRO_LIBS)`
CXXFLAGS = -Wall -std=c++11

# Allegro libs #
ALLEGRO_LIBS = \
	allegro-static-5 \
	allegro_ttf-static-5 \
	allegro_font-static-5 \
	allegro_primitives-static-5

# Directories #
SRCDIR   = src
INCDIR   = include
BUILDDIR = build
BINDIR   = bin

# Output #
NAME = castle_square.out

################################################################################
#--------------------------# OS DEPENDANT VARIABLES #--------------------------#
#--------------------------#         WINDOWS        #--------------------------#
################################################################################

ifeq ($(OS),Windows_NT)

	# Remove #
	RM    =  del /q /s /f
	RMDIR =  rmdir /q /s

	# Clean #
	CLEAN      = $(RM) $(BUILDDIR)\$(OS)\*.o $(BUILDDIR)\$(OS)\*.d $(BINDIR)\$(OS)\$(NAME)* >nul 2>nul || (exit 0)
	# El (exit 0) evita que make se detenga en caso de que no encuentre los archivos #

	# Directories #
	MKDIR = mkdir $(subst /,\,$@) >nul 2>nul || (exit 0)
	# El (exit 0) evita que make se detenga en caso de que mkdri avise que la carpeta ya existe #

################################################################################
#--------------------------# OS DEPENDANT VARIABLES #--------------------------#
#--------------------------#          LINUX         #--------------------------#
################################################################################
else

	OS = $(shell uname -s)

	# Remove #
	RM  =  rm -rf

	# Clean #
	CLEAN      = $(RM) $(BUILDDIR)/$(OS)/*.o $(RM) $(BUILDDIR)/$(OS)/*.d $(BINDIR)/$(OS)/$(NAME)* $(CLEAN_DEPS)

	# Directories #
	MKDIR = mkdir -p -- $@

endif

################################################################################
#-----------------------------#  OTHER VARIABLES #-----------------------------#
################################################################################

SRCS   = $(wildcard $(SRCDIR)/*.cpp)
OBJS   = $(subst $(SRCDIR)/, $(BUILDDIR)/$(OS)/, $(SRCS:.cpp=.o))
DEPS   = $(subst $(SRCDIR)/, $(BUILDDIR)/$(OS)/, $(SRCS:.cpp=.d))
TARGET = $(BINDIR)/$(OS)/$(NAME)

################################################################################
#-------------------------------#  DEPENDENCES #-------------------------------#
################################################################################

# FILES #

$(TARGET): directories $(OBJS)
	$(CXX) $(OBJS) -o $@ $(CXXFLAGS) $(LFLAGS)

$(BUILDDIR)/$(OS)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(LFLAGS) -c $< -o $@

# DIRECTORIES #
directories: $(BUILDDIR)/$(OS) $(BINDIR)/$(OS)

$(BUILDDIR)/$(OS):
	$(MKDIR)
$(BINDIR)/$(OS):
	$(MKDIR)

# CLEAN #
clean:
	$(CLEAN)

-include $(DEPS)
