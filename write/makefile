
ifeq ($(VENDOR),cray)
        CC=cc -dynamic
else
        CC=mpic++
endif

CCFLAGS=-g
LDFLAGS=-lcasa_tables -lcasa_casa
TARGET= write_benchmark

all: $(TARGET) cl

$(TARGET): $(TARGET:=.cc)
#	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) 
	$(CC) *.cc -o $@ $(CCFLAGS) $(LDFLAGS) 

cl: 
	rm -rf *.casa *.eps *.e* *.o* *.log *.ER *.OU

clean:cl 
	rm -rf $(TARGET) *.dSYM *.so log

re: clean all

