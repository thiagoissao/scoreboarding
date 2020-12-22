# Makefile

all: pdflatex

TEX	:=	pdflatex
DOC	:=	projeto3

# Compliação do arquivo 
pdflatex:
	@$(TEX) $(DOC).tex
	@echo -e '\nPDF => "projeto3" Criado\n'


# Para limpar todos gerados
clean:
	@rm -rf $(DOC).log $(DOC).pdf $(DOC).aux
	@echo -e 'Clean executado!\n'
