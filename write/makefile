
ifeq ($(VENDOR),cray)
        CC=cc -dynamic
else
        CC=mpic++
endif

CCFLAGS=
LDFLAGS=-lcasa_tables -lcasa_casa
TARGET= ConcatWrite

all: $(TARGET) cl

$(TARGET): $(TARGET:=.cc)
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) 

cl: 
	rm -rf *.casa *.eps *.e* *.o* *.log *.ER *.OU

clean:cl 
	rm -rf $(TARGET) *.dSYM *.so log

re: clean all

