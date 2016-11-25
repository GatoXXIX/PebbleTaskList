#ifndef TL_DATA_H
#define TL_DATA_H

typedef struct Data {
    struct Tasklist *firstTasklist;
    int n; /* Amount of tasklists */
} Data;

typedef struct Tasklist {  
    int id;
    struct Tasklist *nextTasklist;
    struct Task *firstTask;
} Tasklist;

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

Data* createData();
void freeData(Data *d);

void insertTask(Data *d, int source, int target, double weight);
void removeTask(Data *d, int source, int target);
void printData(Data *d);

double doesTaskExist(Data *d, int source, int target);
int getSizeOfData(Data *d);

#endif