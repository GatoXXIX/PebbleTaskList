/* Author:        Gartenlehner Daniel */
/* Enrolment nr.: S1510307010         */
/* Exercise:      SWO32A04BB          */
/*                Pebble Projekt      */
/* Created on:    24.11.2016          */ 
/* Semester:      WS 16/17            */
/* FileName:      tl_data.h           */

#ifndef TL_DATA_H
#define TL_DATA_H

typedef struct Task {
	int taskNr;
	int priorityCode;
	int year;
	int month;
	int day;
  struct Task *nextTask;
} Task;

typedef struct Tasklist {  
  int id;
  struct Tasklist *nextTasklist;
  struct Task *firstTask;
} Tasklist;

typedef struct Data {
  struct Tasklist *firstTasklist;
  int tl; /* Amount of tasklists */
} Data;

Data* createData();
void freeData(Data *d);

void insertTask(Data *d, int taskNr);
void removeTask(Data *d, int taskNr);
void printData(Data *d);
bool doesTaskExist(Data *d, int taskNr);

#endif