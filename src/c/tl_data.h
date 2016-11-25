#ifndef TL_DATA_H
#define TL_DATA_H

typedef struct Task {
    double weight;  /* Delete */    
    int destTasklistId; /* Delete */
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

void insertTask(Data *d, int source, int target, double weight);
void removeTask(Data *d, int source, int target);
void printData(Data *d);
double doesTaskExist(Data *d, int source, int target);

#endif