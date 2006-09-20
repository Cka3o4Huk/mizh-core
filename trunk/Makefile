W_ASM = nasmw
UNIX_ASM = nasm
ASM = UNIX_ASM

all: boot.asm load2
	$(ASM) -fbin -o loader boot.asm
	make clean_obj

load2: core
	$(ASM) -fbin -o load2 bootload.asm

core: 
	make -C ./src -f ./Makefile all

clean_obj: 
	make -C ./src -f ./Makefile clean_obj
	del load2
	del core
clean:  clean_obj
	del loader
