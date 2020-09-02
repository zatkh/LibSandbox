CC = gcc
CFLAGS = -g -Wall 
SBOX_DIR = $(PWD)/../intra_proc_sbox/
LIBS = -L$(SBOX_DIR)/out -lsbox -lpthread
CFLAGS += -I$(SBOX_DIR)
OBJ_FILES = privilage_test shm_test

all: $(OBJ_FILES) hello.so

privilage_test:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

shm_test:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

hello.so:
	$(CC) -shared -fPIC -lpthread -o hello.so loader_test.c


clean:
	rm *.o $(OBJ_FILES) hello.so
