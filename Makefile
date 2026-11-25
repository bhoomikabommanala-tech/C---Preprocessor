mypreprocessor: main.o macro_replace.o file_inclusion.o comment_removal.o
	gcc -o mypreprocessor main.o macro_replace.o file_inclusion.o comment_removal.o

main.o: main.c header.h
	gcc -c main.c

macro_replace.o: macro_replace.c header.h
	gcc -c macro_replace.c

file_inclusion.o: file_inclusion.c header.h
	gcc -c file_inclusion.c

comment_removal.o: comment_removal.c header.h
	gcc -c comment_removal.c

clean:
	@echo "cleaning up...."
	@rm -f *.o mypreprocessor
