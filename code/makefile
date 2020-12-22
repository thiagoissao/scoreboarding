# Makefile

all: gcc

COMP  := gcc
EXEC  := main
EARG1 := D_REENTRANT
EARG2 := lpthread
EXEC1 := ./a
ARG1  := ./examples/config
ARG2  := 7
ARG3  := ./examples/mnemoniosRAR
ARG4  := resul_thread1
ARG5  := 5
ARG6  := ./examples/mnemoniosRAW
ARG7  := resul_thread2

gcc:
	@$(COMP) $(EXEC).c -$(EARG1) -$(EARG2)
	@echo -e '\nCompilado! "a.out" criado!\n'
	@echo -e '\nExecutando..'
	@$(EXEC1).out -c $(ARG1).txt -n $(ARG2).txt -p $(ARG3).txt -o $(ARG4).txt -m $(ARG5) -r $(ARG6).txt -q $(ARG7).txt 


 
