##
## Makefile for Makefile in /home/marwane/Projects/C++/sockets
## 
## Made by marwane
## Login   <marwane.khsime@epitech.eu>
## 
## Started on  Wed May  3 00:22:29 2017 marwane
## Last update Wed May  3 00:24:51 2017 marwane
##

#
##
##	-[UTILS]-
##
#

# Shorcut Rules
RM 	= 		rm -rf
# Run this project with debug flags ? (yes / no)
DEBUG 		=	no
# If display_opt is set to "percentage", shows the progress of the compilation in percentage, else use the index.
DISPLAY_OPT	= percentage
# Utils for the compilation's progress
COUNT 			= 1
NBSOURCES 		= $(shell find src/*.cpp | wc -l)
PERCENT			= 0
DISPLAY_ONE     = "[\033[95m$(PERCENT)%\033[0m][\033[92m$<\033[0m]"
DISPLAY_TWO     = "[\033[95m$(COUNT)\033[0m/\033[93m$(NBSOURCES)\033[0m][\033[92m$<\033[0m]"
COMPILATION_MSG = $(DISPLAY_TWO)

#
##
##	-[CONFIGURATION]
##
#

# Name of the projet
NAME		=	project
# Compiler
CXX			=	g++
# Compiler flags
CXXFLAGS	=	-std=c++14
CXXFLAGS	+=	-pedantic -O2
CXXFLAGS	+=	-W -Wall -Wextra -Weffc++ -Wshadow -Wnon-virtual-dtor -Wunreachable-code -Wundef
# Include folders
INCDIRS		:=	$(addprefix -I,$(shell find includes/ -type d -print))
CXXFLAGS	+=	$(INCDIRS)
# Libraries
LDFLAGS		=	-lpthread

# if debug is set to yes, add -g3 flag
ifeq ($(DEBUG),yes)
	CXXFLAGS += -g3
endif

# Set the compilation message
ifeq ($(DISPLAY_OPT), percentage)
        COMPILATION_MSG=$(DISPLAY_ONE)
endif

# Resource folder (root), object folder, and directory where the binary will be created.
SRCDIR   = src
OBJDIR   = obj
BINDIR   = .

# SOURCES
SOURCES	:= 	$(wildcard $(SRCDIR)/*.cpp)
# OBJECTS
OBJECTS	:= 	$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

#
##
### -[RULES]-
##
#

.PHONY: 	clean fclean re

$(BINDIR)/$(NAME):	$(OBJECTS)
			@$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)
			@echo "Project $(NAME) build successfully!"

$(OBJECTS):	$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
			@mkdir -p $(dir $@)
			@$(CXX) $(CXXFLAGS) -c $< -o $@
			@$(eval PERCENT=$(shell echo $$((($(COUNT)*100/$(NBSOURCES))))))
			@echo $(COMPILATION_MSG)
			@$(eval COUNT=$(shell echo $$((($(COUNT)+1)))))


clean:
			@$(RM) $(OBJDIR)
			@echo "Cleanup complete!"

fclean: 	clean
			@$(RM) $(BINDIR)/$(NAME)
			@echo "Executable removed!"

re:			fclean $(BINDIR)/$(NAME)
