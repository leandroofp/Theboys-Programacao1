# makefile The Boys
# Carlos Maziero - DINF/UFPR, 2024/2
 
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -std=c99
LDLIBS  = -lm
MAIN    = theboys
ENTREGA = $(MAIN)
 
# lista de arquivos de cabeçalho
HDR = fila.h fprio.h conjunto.h entidades.h eventos.h destruicoes.h \
      funcoesauxiliares.h simulador.h
 
# lista de arquivos-objeto
# não inclua conjunto.o, senão ele será removido com "make clean"
OBJ = fila.o fprio.o entidades.o eventos.o destruicoes.o \
      funcoesauxiliares.o simulador.o theboys.o
 
# construir o executável
$(MAIN): $(OBJ) conjunto.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
 
# construir os arquivos-objeto (qualquer mudança em um .h recompila tudo)
%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@
 
# executar
run: $(MAIN)
	./$(MAIN)
 
# testar no Valgrind
valgrind: $(MAIN)
	valgrind --leak-check=full --track-origins=yes ./$(MAIN)
 
# gerar arquivo TGZ para entregar
tgz: clean
	-mkdir -p /tmp/$(USER)/$(ENTREGA)
	chmod 0700 /tmp/$(USER)/$(ENTREGA)
	cp *.c *.h conjunto.o makefile /tmp/$(USER)/$(ENTREGA)
	tar czvf $(ENTREGA).tgz -C /tmp/$(USER) $(ENTREGA)
	rm -rf /tmp/$(USER)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"
 
# limpar arquivos temporários
clean:
	rm -f *~ $(OBJ) $(MAIN) /tmp/$(USER)/$(ENTREGA) $(ENTREGA).tgz
 