
# RUN target (for typing "make")
RUN: project project_debug

# executable targets
project: llist.o user_interface.o
	g++ -o project llist.o user_interface.o

project_debug: remove_objects llist_debug.o user_interface_debug.o
	g++ -o project_debug llist.o user_interface.o
	
# object targets
llist.o: llist.cpp record.h
	g++ -ansi -pedantic-errors -Wall -c llist.cpp

user_interface.o: user_interface.cpp record.h
	g++ -ansi -pedantic-errors -Wall -c user_interface.cpp

llist_debug.o: llist.cpp record.h
	g++ -DDEBUGMODE -ansi -pedantic-errors -Wall -c llist.cpp

user_interface_debug.o: user_interface.cpp record.h
	g++ -DDEBUGMODE -ansi -pedantic-errors -Wall -c user_interface.cpp

# utility target
remove_objects:
	rm *.o

clean:
	rm *.o project project_debug

real_clean:
	rm *.o project project_debug database.txt
