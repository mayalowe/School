prereqs.out : catalog.o course.o flexprereq.o main.o major.o prereq.o prereqptr.o quarter.o schedule.o  
	g++ -ansi -Wall -g -o prereqs.out catalog.o course.o flexprereq.o main.o major.o prereq.o prereqptr.o quarter.o schedule.o 

catalog.o : catalog.cpp list.cpp list.h catalog.h  
	g++ -ansi -Wall -g -c catalog.cpp

course.o : course.cpp course.h prereq.h flexprereq.h  
	g++ -ansi -Wall -g -c course.cpp

flexprereq.o : flexprereq.cpp flexprereq.h  
	g++ -ansi -Wall -g -c flexprereq.cpp

main.o : main.cpp catalog.h schedule.h  
	g++ -ansi -Wall -g -c main.cpp

major.o : major.cpp major.h schedule.h quarter.h list.cpp list.h  
	g++ -ansi -Wall -g -c major.cpp

prereq.o : prereq.cpp prereq.h  
	g++ -ansi -Wall -g -c prereq.cpp

prereqptr.o : prereqptr.cpp prereq.h prereqptr.h  
	g++ -ansi -Wall -g -c prereqptr.cpp

quarter.o : quarter.cpp list.cpp list.h quarter.h  
	g++ -ansi -Wall -g -c quarter.cpp

schedule.o : schedule.cpp quarter.h catalog.h list.cpp list.h schedule.h  
	g++ -ansi -Wall -g -c schedule.cpp

clean :
	rm -f prereqs.out catalog.o course.o flexprereq.o main.o major.o prereq.o prereqptr.o quarter.o schedule.o 

