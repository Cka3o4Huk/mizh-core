W_ASM = nasmw
UNIX_ASM = nasm
ASM = UNIX_ASM
MAKER = gmake

all: boot.asm load2
	$(ASM) -fbin -o loader boot.asm
	$(MAKER) clean_obj

load2: core
	$(ASM) -fbin -o load2 bootload.asm

core:
	@echo "###### Compiling core files"
	$(MAKER) -C ./src -f ./Makefile all

clean_obj:
	@echo "###### Clean all" 
	rm -rf ${.CURDIR}/obj
	rm -f load2
	rm -f core
clean:  clean_obj
	rm -f loader
