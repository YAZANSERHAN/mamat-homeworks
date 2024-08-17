CXX=g++
CXXFLAGS = -g -Wall -std=c++11 -fpic
CXXLINK=$(CXX)
OBJS=string.o port.o ip.o string-array.o

# Target to build the firewall executable
firewall.exe: libfirewall.so main.o $(OBJS)
	$(CXXLINK) -g -Wall $(OBJS) main.o -o firewall.exe -L. -lfirewall -linput

# Target to build the main.o object file
main.o: main.cpp string.h generic-field.h ip.h port.h input.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp   

# Target to build the shared library libfirewall.so
libfirewall.so: $(OBJS)
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so
	
# Target to build individual object files
string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp
	
ip.o: ip.cpp string.h generic-field.h ip.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp
	
port.o: port.cpp string.h generic-field.h port.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

string-array.o: string-array.cpp string-array.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic string-array.cpp
		
clean:
	rm -f string.o port.o ip.o string-array.o main.o libfirewall.so firewall.exe
