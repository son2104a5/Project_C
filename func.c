#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueFull(Queue *q) {
    return (q->rear + 1) % MAX_SIZE_QUEUE == q->front;
}

int isDuplicateID(Queue *q, const char *id) {
    if (isQueueEmpty(q)) {
        return 0;
    }
    int i = q->front;
    while (1) {
        if (strcmp(q->queue[i].requestID, id) == 0) {
            return 1;
        }
        if (i == q->rear) {
            break;
        }
        i = (i + 1) % MAX_SIZE_QUEUE;
    }
    return 0;
}

void generateUniqueRequestID(Queue *q, char *id) {
	srand(time(NULL));
    do {
        snprintf(id, 10, "TX%d", rand() % 10000000);
    } while (isDuplicateID(q, id));
}

void enqueue(Queue *q, TaxiRequest request) {
    if (isQueueFull(q)) {
        printf("Loi: Hang doi day. Khong the them yeu cau moi.\n");
        return;
    }
    if (isQueueEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_SIZE_QUEUE;
    q->queue[q->rear] = request;
}

TaxiRequest dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Loi: Hang doi trong. Khong co yeu cau de xu ly.\n");
        exit(1);
    }
    TaxiRequest request = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE_QUEUE;
    }
    return request;
}

int isQueueEmpty(Queue *q) {
    return q->front == -1;
}

void displayQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Hang doi trong.\n");
        return;
    }
    printf("\nDanh sach cac yeu cau taxi hien tai:\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("| %-12s | %-18s | %-12s | %-12s | %-18s |\n", "ID yeu cau", "Khach hang", "Diem Don", "Diem Den", "Khoang cach (km)");
    printf("----------------------------------------------------------------------------------------\n");
    int i = q->front;
    while (1) {
        TaxiRequest request = q->queue[i];
        printf("| %-12s | %-18s | %-12s | %-12s | %-18.2f |\n",
               request.requestID, request.customerName, request.pickupPoint, request.destination, request.distance);
        printf("----------------------------------------------------------------------------------------\n");
        if (i == q->rear) {
            break;
        }
        i = (i + 1) % MAX_SIZE_QUEUE;
    }
}

void deleteRequestByID(Queue *q, const char *requestID) {
    if (isQueueEmpty(q)) {
        printf("Loi: Hang doi trong. Khong the xoa yeu cau.\n");
        return;
    }
    Queue tempQueue;
    initializeQueue(&tempQueue);
    int found = 0;

    while (!isQueueEmpty(q)) {
        TaxiRequest request = dequeue(q);
        if (strcmp(request.requestID, requestID) == 0) {
            found = 1;
            printf("Yeu cau voi ID %s da duoc xoa.\n", requestID);
        } else {
            enqueue(&tempQueue, request);
        }
    }

    *q = tempQueue;

    if (!found) {
        printf("Khong tim thay yeu cau voi ID %s trong hang doi.\n", requestID);
    }
}

void saveQueueToFile(Queue *q, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Loi: Khong the mo file de ghi.\n");
        return;
    }
    fwrite(q, sizeof(Queue), 1, file);
    fclose(file);
    printf("Du lieu hang doi da duoc luu vao file '%s'.\n", filename);
}

void loadQueueFromFile(Queue *q, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Loi: Khong the mo file de doc.\n");
        return;
    }
    fread(q, sizeof(Queue), 1, file);
    fclose(file);
    printf("Du lieu hang doi da duoc tai tu file '%s'.\n", filename);
}

