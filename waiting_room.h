#ifndef WAITING_ROOM_H
#define WAITING_ROOM_H

#include "patient_record.h"

#define WAITING_CAPACITY 50

typedef struct {
    Patient items[WAITING_CAPACITY];
    int head;
    int tail;
    int length;
} WaitingRoom;

void waitingRoomInit(WaitingRoom *room);
void waitingRoomFree(WaitingRoom *room);
int admitToWaitingRoom(WaitingRoom *room, const Patient *patient);
int releaseFromWaitingRoom(WaitingRoom *room, Patient *out);
void showWaitingRoom(const WaitingRoom *room);

#endif
