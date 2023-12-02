FLEX_SOURCE = CodeL.l
BISON_SOURCE = parser.y
FLEX_OUTPUT = lex.yy.c
BISON_OUTPUT = parser.tab.c
OUTPUT_BINARY = projet

# Options pour GCC
CFLAGS = -g -w

# Cibles par défaut
all: $(OUTPUT_BINARY)

# Règle pour générer le fichier C à partir du fichier Flex
$(FLEX_OUTPUT): $(FLEX_SOURCE)
	flex $(FLEX_SOURCE)

# Règle pour générer le fichier C à partir du fichier Bison
$(BISON_OUTPUT): $(BISON_SOURCE)
	bison -d $(BISON_SOURCE)

# Règle pour la compilation avec GCC
$(OUTPUT_BINARY): $(FLEX_OUTPUT) $(BISON_OUTPUT)
	gcc $(CFLAGS) -o $(OUTPUT_BINARY) $(FLEX_OUTPUT) $(BISON_OUTPUT)

# Cible pour exécuter le programme
run: $(OUTPUT_BINARY)
	./$(OUTPUT_BINARY)

# Cible pour nettoyer les fichiers générés
clean:
	rm -f $(FLEX_OUTPUT) $(BISON_OUTPUT) $(OUTPUT_BINARY) y.tab.h
