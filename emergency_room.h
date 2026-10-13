#ifndef EMERGENCY_ROOM_H
#define EMERGENCY_ROOM_H

#include "patient_record.h"

#define EMERGENCY_CAPACITY 50

typedef struct {
    Patient items[EMERGENCY_CAPACITY];
    int count;
} EmergencyRoom;

void emergencyRoomInit(EmergencyRoom *room);
void emergencyRoomFree(EmergencyRoom *room);
int sendToEmergency(EmergencyRoom *room, Patient p);
int takeEmergencyPatient(EmergencyRoom *room, Patient *out);
void showEmergencyRoom(const EmergencyRoom *room);

#endif
