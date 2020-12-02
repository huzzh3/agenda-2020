Objects = main.o AgendaService.o AgendaUI.o Date.o Meeting.o Storage.o User.o

AgendaM : $(Objects) 
	g++ -o AgendaM $(Objects)
main.o : main.cpp
	g++ -c main.cpp
AgendaService.o : AgendaService.cpp
	g++ -c AgendaService.cpp
AgendaUI.o : AgendaUI.cpp
	g++ -c AgendaUI.cpp
Date.o : Date.cpp
	g++ -c Date.cpp
Meeting.o : Meeting.cpp
	g++ -c Meeting.cpp
Storage.o : Storage.cpp
	g++ -c Storage.cpp
User.o : User.cpp
	g++ -c User.cpp
clean :
	rm $(Objects)