ifeq ($(VENDOR),cray)
        CC=cc -dynamic
else
        CC=mpic++
endif

CCFLAGS=
LDFLAGS=-lcasa_tables -lcasa_casa -ladiosstman
TARGET=read_benchmark

all: $(TARGET) cl

$(TARGET): *.cc
	$(CC) *.cc -o $(TARGET) $(CCFLAGS) $(LDFLAGS) -fPIC --shared

cl:
	rm -rf *.casa *.eps *.e* *.o* *.log *.ER *.OU

clean:cl
	rm -rf $(TARGET) *.dSYM *.so log

re: clean all




