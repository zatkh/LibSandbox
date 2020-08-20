CC = gcc
CFLAGS = -g -Wall 
SBOX_DIR = $(PWD)/../intra_proc_sbox/
LIBS = -L$(SBOX_DIR)/out -lsbox -lpthread
CFLAGS += -I$(SBOX_DIR)
OBJ_FILES = privilage_test shm_test

all: $(OBJ_FILES)

privilage_test:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)

shm_test:
	$(CC) $(CFLAGS) $@.c -o $@ $(LIBS)


clean:
	rm *.o $(OBJ_FILES)
