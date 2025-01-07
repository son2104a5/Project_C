#define MAX_SIZE_QUEUE 100

typedef struct{
	char requestID[10];
	char customerName[50];
	char pickupPoint[50];
	char destination[50];
	float distance;
}TaxiRequest;

typedef struct {
	TaxiRequest queue[MAX_SIZE_QUEUE];
	int front;
	int rear;
}Queue;
