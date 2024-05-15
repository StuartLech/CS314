#include "lab2-api.h"

//----------------------------------
//
//  if you run userprog4.dlx.obj 2, it should output
//
//	A0
//	B0
//	A1
//	A2
//	A3
//	A4
//	A5
//	A6
//	B1
//	A7
//	A8
//	A9
//	B2
//	A10
//	B3
//	A11
//	B4
//	A12
//	B5
//	A13
//	B6
//	A14
//	B7
//	A15
//	B8
//	A16
//	B9
//	A17
//	B10
//	A18
//	B11
//	A19
//	B12
//	A20
//	B13
//	A21
//	B14
//	A22
//	B15
//	A23
//	B16
//	A24
//	B17
//	A25
//	B18
//	A26
//	B19
//	A27
//	B20
//	A28
//	B21
//	A29
//	B22
//	A0
//	B23
//	A1
//	B24
//	A2
//	B25
//	A3
//	B26
//	A4
//	B27
//	A5
//	B28
//	A6
//	B29
//	A7
//	B0
//	A8
//	B1
//	A9
//	B2
//	A10
//	B3
//	A11
//	B4
//	A12
//	B5
//	A13
//	B6
//	A14
//	B7
//	A15
//	B8
//	A16
//	B9
//	A17
//	B10
//	A18
//	B11
//	A19
//	B12
//	A20
//	B13
//	A21
//	B14
//	A22
//	B15
//	A23
//	B16
//	A24
//	B17
//	A25
//	B18
//	A26
//	B19
//	A27
//	B20
//	A28
//	B21
//	A29
//	B22
//	B23
//	B24
//	B25
//	B26
//	B27
//	B28
//	B29
// 
//
//   You are free to modify this file (and other userprogs) to test your solution
//   Get to know the scheduling algorithm before you hack or you'll get nowhere. 
//   I'd suggest setting up the scenario asked for in the "pencil and paper" 
//   algorithm walkthrough to check for correct behavior. 
//
//   Start early. 
//----------------------------------------------------------------------------
main (int argc, char *argv[])
{
  int number, i,j,offset;
  uint32 handle;
  sem_t semaphore;
  char num_str[10], semaphore_str[10];

  switch(argc)
  {
    case 2:
      number = dstrtol(argv[1], NULL, 10);
      //Printf("Setting number = %d\n", number);
      semaphore = sem_create(1);
      ditoa(semaphore, semaphore_str);	//Convert the semaphore to a string

      for(i=0; i<number; i++)
      {
        ditoa(i, num_str);
        process_create(i,0,"userprog4.dlx.obj", num_str,semaphore_str,NULL);
      }
      break;
    case 3:
      offset = dstrtol(argv[1], NULL, 10);       //Get semaphore
      semaphore = dstrtol(argv[2], NULL, 10);       //Get semaphore
     // Printf("Offset is %d and semaphore is %d\n",offset,semaphore);
     // Printf("Pid is %d and process is %c\n",getpid(),'A'+offset);
      for(i=0;i<30;i++)
      {
        for(j=0;j<50000;j++);
        Printf("%c%d no sempaphore\n",'A'+offset,i);
      }

      for(i=0;i<30;i++)
      {
	//Printf("Waiting...%c\n",'A'+offset);
        sem_wait(semaphore);
        for(j=0;j<50000;j++);
        Printf("%c%d with semaphore\n",'A'+offset,i);
	//Printf("Signalling...%c\n",'A'+offset);
        sem_signal(semaphore);
      }
       Printf("Process %c processing time: .%ds\n",'A' + offset, TimerGet()/100);

      break;
    default:
      Printf("Usage: ");
      Printf(argv[0]);
      Printf(" number\n");
      Printf("argc = %d\n", argc);
      exit();
  }



}
