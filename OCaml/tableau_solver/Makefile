#
# Makefile
#

SRC= term.ml parser.mly lexer.mll test.ml
COMPONENT= term.ml parser.mli parser.ml lexer.ml test.ml
TARGET= test_parse

all:	$(TARGET)

$(TARGET): 	$(COMPONENT)
	ocamlmktop $(COMPONENT) -o $(TARGET)

parser.mli:	parser.mly
	ocamlyacc	parser.mly

parser.ml:	parser.mly
	ocamlyacc parser.mly

lexer.ml:	lexer.mll
	ocamllex lexer.mll

backup:
	cp -f Makefile $(SRC) back

clean:
	rm -f parser.ml parser.mli lexer.ml $(TARGET) *.cmi *.cmo *.mli
