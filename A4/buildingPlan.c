#include <stdio.h>
#include <stdlib.h>

#include "building.h"
void findDoors(FloorPlan *fl)
{
   for (int i=0; i<=HEIGHT; i++)
   {
       //printf("%d\n", i);
       //printf("%d\n", fl->numDoors);
       for (int j=0; j<=WIDTH; j++)
       {
      //   printf("%d\n", j);
         if (fl->grid[i][j]=='2'){
          // printf("%c", fl->grid[i][j] );
           fl->numDoors++;
           //printf("%d\n", fl->numDoors);
          // printf ("%d & %d\n", i,j);
         }
       }

   }
   Door dors[fl->numDoors];
   //printf("%d", doors[0].row);
   int placement=0;
   for (int i=0; i<=HEIGHT; i++)
   {
       //printf("%d\n", i);
       //printf("%d\n", fl->numDoors);
       for (int j=0; j<=WIDTH; j++)
       {
      //   printf("%d\n", j);
         if (fl->grid[i][j]=='2'){
          // printf("%c", fl->grid[i][j] );
            dors[placement].row=i;
            dors[placement].col=j;
            placement++;
          //  printf("%d\n", placement);
          // printf ("%d & %d\n", i,j);
         }
       }

   }
   fl->doors= dors;
//   printf("%d\n", fl->doors[0].row);
//   printf("%d\n", fl->doors[0].col);

}
void findRooms(Building *build, int floornum)
{
//  printf("1");
  Room *newR;
  newR= malloc(sizeof(unsigned char) * 3 + sizeof(struct RoomType *));
  newR->size=0;
  newR->numDoors=0;

//  printf("2");
  for (int i=0; i<=HEIGHT; i++)
  {
//    printf("%d", floornum);

      for (int j=0; j<=WIDTH; j++)
      {
        if (build->floors[floornum].grid[i][j]=='0')
        {
           //printf("made it in");
            shaperoom( newR, build, floornum, i, j ,1);
           //printf("donzo");
        }
      }
  }
  //build->floors[floornum].roomList->nextRoom=newR;
//  printf("ASD");
  build->floors[floornum].roomList= newR;
  printf("Done\n");
}
void shaperoom ( Room *newR, Building *build,int floornum,int i, int j, int cour ){
  //printf("RELLA RELLA PIZZA\n");
  if (cour==1)
  {
  //  printf("Hell");
    if ( build->floors[floornum].grid[i][j] !='0')
    {
      shaperoom ( newR,build,floornum, i, j, 2 );
    }
    else if ( build->floors[floornum].grid[i][j]=='u')
    {
      shaperoom ( newR, build, floornum, i+1,  j, 1 );
    }
    else if (build->floors[floornum].grid[i][j]=='2')
    {
      newR->numDoors++;
      build->floors[floornum].grid[i][j]='u';
      shaperoom ( newR, build, floornum, i+1,  j, 1 );
    }
    else
    {
      newR->size++;
      build->floors[floornum].grid[i][j]='u';
      shaperoom ( newR, build, floornum, i+1,  j, 1 );
    }
  }
  else if (cour==2)
  {
    if ( build->floors[floornum].grid[i][j] !='0')
    {
      shaperoom ( newR, build, floornum, i-1, j-1, 3 );
    }
    else if ( build->floors[floornum].grid[i][j]=='u')
    {
      shaperoom ( newR, build, floornum, i+1,  j, 1 );
    }
    else if (build->floors[floornum].grid[i][j]=='2')
    {
      newR->numDoors++;
      build->floors[floornum].grid[i][j]='u';
      shaperoom ( newR, build, floornum, i+1,  j, 1 );
    }
    else
    {
      newR->size++;
      build->floors[floornum].grid[i][j]='u';
      shaperoom ( newR, build, floornum, i+1,  j, 1 );
    }


  }
  else if (cour==3)
  {
    // printf("PIZZA MOZZEREALLA\n");

   }


}
void sortRooms(Building *build)
{
  printf("in here");
  Room  *office;             // Linked-List of all offices in the building (includes all floors)
  Room  *meetingRoom;        // Linked-List of all meeting rooms in the building (includes all floors)
  Room  *lab;                // Linked-List of all labs in the building (includes all floors)
  Room  *hallway;            // Linked-List of all hallways in the building (includes all floors)
  Room   *storageRoo;
  office= malloc(sizeof(unsigned char) * 3 + sizeof(struct RoomType *));
  office->nextRoom=NULL;
  meetingRoom=  malloc(sizeof(unsigned char) * 3 + sizeof(struct RoomType *));
  meetingRoom->nextRoom;
  lab= malloc(sizeof(unsigned char) * 3 + sizeof(struct RoomType *));
  lab->nextRoom=NULL;
  hallway=  malloc(sizeof(unsigned char) * 3 + sizeof(struct RoomType *));
  hallway->nextRoom=NULL;
  storageRoo= malloc(sizeof(unsigned char) * 3 + sizeof(struct RoomType *));
  storageRoo->nextRoom=NULL;
  for (int floor=0; floor<= NUM_FLOORS; floor++)
  {
    printf("%d\n", (sizeof(build->floors[floor].roomList)));
    for (int loc=0; loc<=(sizeof(build->floors[floor].roomList)); loc++)
    {
      if (build->floors[floor].roomList[loc].size>=30)
      {
        *lab= build->floors[floor].roomList[loc];

      }
      else if (build->floors[floor].roomList[loc].numDoors==1)
      {
        *office= build->floors[floor].roomList[loc];

      }
      else if (build->floors[floor].roomList[loc].numDoors>=4)
      {
        *hallway= build->floors[floor].roomList[loc];

      }
      else if (build->floors[floor].roomList[loc].size<=6)
      {
        *storageRoo= build->floors[floor].roomList[loc];

      }
      else
      {
        *meetingRoom=build->floors[floor].roomList[loc];
      }
    }


      build->storageRooms=storageRoo;
      build->offices=office;
      build->labs=lab;
      build->meetingRooms=meetingRoom;
      build->hallways=hallway;
      build->floors[floor].roomList=NULL;
  }
  printf("FINISH\n");
}
void printRoomList(Room*roomList, char*roomType)
{
 for (int print=0; print<(sizeof(roomList)); print++)
  {
    printf("%s (on floor %d ) with %d square feet and %d doors\n", roomType, roomList[print].floor, (roomList[print].size *4), roomList[print].numDoors );
  }
}
void freeEverything(Building *build)
{
    free(build->offices);
    free(build->meetingRooms);
    free(build->labs);
    free(build->hallways);
    free(build->storageRooms);
}
