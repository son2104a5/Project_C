#include "datatype.h"

void menu();
void initializeQueue(Queue *q);
int isQueueEmpty(Queue *q);
int isQueueFull(Queue *q);
void enqueue(Queue *q, TaxiRequest request);
TaxiRequest dequeue(Queue *q);
void displayQueue(Queue *q);
void deleteRequestByID(Queue *q, const char *requestID);
void saveQueueToFile(Queue *q, const char *filename);
void loadQueueFromFile(Queue *q, const char *filename);
