ASM = nasmw

all: boot.asm load2
	$(ASM) -fbin -o loader boot.asm
	make clean_obj

load2: core
	$(ASM) -fbin -o load2 bootload.asm

core: 
	make -C src -f .\makefile all

clean_obj: 
	make -C src -f .\makefile clean_obj
	del load2
	del core
clean:  clean_obj
	del loader	
