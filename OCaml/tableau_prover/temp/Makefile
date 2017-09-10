#
# Makefile
#

SRC= misc.ml term.ml parser.mly lexer.mll test_parse.ml
COMPONENT= misc.ml term.ml parser.mli parser.ml lexer.ml test_parse.ml lf_proof.ml nj_proof.ml solver.ml
TARGET= test_parse

all:	$(TARGET)

$(TARGET):	$(COMPONENT)
	ocamlmktop $(COMPONENT) -o $(TARGET)
	ocamlopt -annot -bin-annot $(COMPONENT) -o hoge
	mrm hoge

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
