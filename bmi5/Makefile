OBJS = main.o TDT_UDP.o
CFLAGS = -g 
LDFLAGS = -lrt

%.o : %.cpp 
	g++ -c -o $@ $(CFLAGS) $<

tdt_udp: $(OBJS)
	g++ -o $@ $(LDFLAGS) $(OBJS)
	
clean:
	rm -rf *.o tdt_udp