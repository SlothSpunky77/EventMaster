CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS = -lmysqlclient -lpthread

INCLUDES = -I/usr/local/include
LIBS = -L/usr/local/lib

SRCS = main.cpp model.cpp view.cpp controller.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = eventmaster

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

# Copy HTML file to build directory
install: $(TARGET)
	@if [ ! -f index.html ]; then \
		echo "Copying index.html to build directory"; \
		cp index.html ./; \
	fi

.PHONY: all clean install