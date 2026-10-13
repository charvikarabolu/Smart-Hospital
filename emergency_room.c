#include <stdio.h>
#include "emergency_room.h"

void emergencyRoomInit(EmergencyRoom *room)
{
    room->count = 0;
}

void emergencyRoomFree(EmergencyRoom *room)
{
    room->count = 0;
}

int sendToEmergency(EmergencyRoom *room, Patient p)
{
    int i;

    if (room->count == EMERGENCY_CAPACITY)
        return 0;

    i = room->count;
    while (i > 0 && room->items[i - 1].emergency < p.emergency) {
        room->items[i] = room->items[i - 1];
        --i;
    }

    room->items[i] = p;
    room->count++;
    return 1;
}

int takeEmergencyPatient(EmergencyRoom *room, Patient *out)
{
    int i;

    if (room->count == 0)
        return 0;

    *out = room->items[0];

    for (i = 1; i < room->count; ++i)
        room->items[i - 1] = room->items[i];

    room->count--;
    return 1;
}

void showEmergencyRoom(const EmergencyRoom *room)
{
    int i;

    if (room->count == 0) {
        printf("Emergency room queue is empty.\n");
        return;
    }

    printf("\nEmergency order:\n");
    for (i = 0; i < room->count; ++i)
        printf("%d. Patient %d (priority %d)\n",
               i + 1, room->items[i].id, room->items[i].emergency);
}
