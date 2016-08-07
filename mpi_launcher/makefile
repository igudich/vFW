CXXFLAGS += -std=c++11 -Wall -O3
TARGET1  = mpi_launcher
TARGET2 = vWF

CC = mpic++
RM = rm -rf 

SRC1 = mpi_launcher.cpp
SRC2 = main.cpp 

OBJS1 = $(SRC1:.cpp=.o)
OBJS2 = $(SRC2:.cpp=.o)

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1)
	$(CC) -o $(TARGET1) $(OBJS1) -lm

$(TARGET2): $(OBJS2)
	$(CC) -o $(TARGET2) $(OBJS2) -lm

%.o: %.cpp 
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(TARGET1) $(OBJS1) $(TARGET2) $(OBJS2)
