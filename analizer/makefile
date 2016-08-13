TARGET = vWFnew

CC = g++
CXXFLAGS = -std=c++11 -O2
#OPTS = -I /home/kmm/local/include
#BOOST_LIBS = -lboost_mpi -lboost_serialization

RM = rm -rf 

DEPS = statistics.h chain.h ../new_code/vect.h 
SRC = timeAnalizer.cpp statistics.cpp chain.cpp ../new_code/vect.cpp  

OBJS = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.cpp  $(DEPS)
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(TARGET) $(OBJS)
