#include <stdio.h>
#include "waiting_room.h"

void waitingRoomInit(WaitingRoom *room)
{
    room->head = 0;
    room->tail = 0;
    room->length = 0;
}

void waitingRoomFree(WaitingRoom *room)
{
    room->head = 0;
    room->tail = 0;
    room->length = 0;
}

int admitToWaitingRoom(WaitingRoom *room, const Patient *patient)
{
    if (room->length == WAITING_CAPACITY)
        return 0;

    room->items[room->tail] = *patient;
    room->tail = (room->tail + 1) % WAITING_CAPACITY;
    room->length++;
    return 1;
}

int releaseFromWaitingRoom(WaitingRoom *room, Patient *out)
{
    if (room->length == 0)
        return 0;

    *out = room->items[room->head];
    room->head = (room->head + 1) % WAITING_CAPACITY;
    room->length--;
    return 1;
}

void showWaitingRoom(const WaitingRoom *room)
{
    int i, pos;

    if (room->length == 0) {
        printf("Waiting room is empty.\n");
        return;
    }

    printf("Waiting patient IDs: ");
    pos = room->head;

    for (i = 0; i < room->length; ++i) {
        printf("%d", room->items[pos].id);
        if (i + 1 < room->length)
            printf(" -> ");
        pos = (pos + 1) % WAITING_CAPACITY;
    }
    printf("\n");
}
