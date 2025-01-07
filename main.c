#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main() {
    Queue taxiQueue;
    initializeQueue(&taxiQueue);

    int choice;
    char filename[] = "data.bin";
    loadQueueFromFile(&taxiQueue, filename);

    do {
        menu();
        scanf("%d", &choice);
        getchar();
        system("cls");

        switch (choice) {
            case 1: {
                TaxiRequest newRequest;
                generateUniqueRequestID(&taxiQueue, newRequest.requestID);
                printf("ID yeu cau duoc tao: %s\n", newRequest.requestID);

                printf("Nhap ten khach hang: ");
                fgets(newRequest.customerName, sizeof(newRequest.customerName), stdin);
                newRequest.customerName[strcspn(newRequest.customerName, "\n")] = '\0';

                printf("Nhap diem don: ");
                fgets(newRequest.pickupPoint, sizeof(newRequest.pickupPoint), stdin);
                newRequest.pickupPoint[strcspn(newRequest.pickupPoint, "\n")] = '\0';

                printf("Nhap diem den: ");
                fgets(newRequest.destination, sizeof(newRequest.destination), stdin);
                newRequest.destination[strcspn(newRequest.destination, "\n")] = '\0';

                printf("Nhap khoang cach (km): ");
                scanf("%f", &newRequest.distance);

                enqueue(&taxiQueue, newRequest);
                system("cls");
                break;
            }
            case 2:
                displayQueue(&taxiQueue);
                break;

            case 3: {
                if (!isQueueEmpty(&taxiQueue)) {
                    TaxiRequest nextRequest = dequeue(&taxiQueue);
                    printf("\nDang xu ly yeu cau tiep theo:\n");
                    printf("ID yeu cau: %s\nKhach hang: %s\nDiem don: %s\nDiem den: %s\nKhoang cach: %.2f km\n",
                           nextRequest.requestID, nextRequest.customerName, nextRequest.pickupPoint, nextRequest.destination, nextRequest.distance);
                } else {
                    printf("Khong co yeu cau nao de xu ly.\n");
                }
                break;
            }

            case 4: {
            	displayQueue(&taxiQueue);
                char requestID[10];
                printf("Nhap ID yeu cau can xoa: ");
                fgets(requestID, sizeof(requestID), stdin);
                requestID[strcspn(requestID, "\n")] = '\0';
                deleteRequestByID(&taxiQueue, requestID);
                
                break;
            }

            case 0:
                saveQueueToFile(&taxiQueue, filename);
                printf("Dang thoat he thong.\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (1 == 1);

    return 0;
}
