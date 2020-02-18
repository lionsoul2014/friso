PROJECT= friso

CC= gcc

lib: friso.cma friso.cmxa

stub.o: stub.c
	$(CC) -Wall -fPIC -I `ocamlc -where` -c -o $@ $<

friso.cma friso.cmxa: friso.ml stub.o
	ocamlfind ocamlmklib -lfriso -o friso -oc friso_stubs $^

friso.ml: friso.cmi


friso.cmi: friso.mli
	ocamlc $<

.PHONY: install clean

install: lib
	ocamlfind install $(PROJECT) META *.mli *.cmi *.cma *.cmxa *.so *.a

uninstall:
	ocamlfind remove $(PROJECT)

clean:
	rm -f *.o *.cm* *.a *.so

