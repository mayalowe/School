prereqs.out : catalog.o course.o main.o quarter.o schedule.o  
	g++ -ansi -Wall -g -o prereqs.out ListNode.o catalog.o course.o list.o main.o quarter.o schedule.o 

catalog.o : catalog.cpp list.cpp list.h catalog.h  
	g++ -ansi -Wall -g -c catalog.cpp

course.o : course.cpp course.h  
	g++ -ansi -Wall -g -c course.cpp

main.o : main.cpp catalog.h schedule.h  
	g++ -ansi -Wall -g -c main.cpp

quarter.o : quarter.cpp list.cpp list.h quarter.h  
	g++ -ansi -Wall -g -c quarter.cpp

schedule.o : schedule.cpp quarter.h catalog.h list.cpp list.h schedule.h  
	g++ -ansi -Wall -g -c schedule.cpp

clean :
	rm -f prereqs.out catalog.o course.o main.o quarter.o schedule.o 

