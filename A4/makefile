
buildingTest: buildingTest.o buildingPlan.o
		gcc -o buildingTest buildingTest.o buildingPlan.o
buildingTest.o:	buildingTest.c	 building.h
		gcc -c buildingTest.c
buildingPlan.o: buildingPlan.c building.h
		gcc -c buildingPlan.c
clean:
		rm -f *.o
