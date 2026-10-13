#include <stdlib.h>
#include "hospital.h"

void hospitalInit(HospitalState *h)
{
    patientBookInit(&h->patients);
    doctorRegistryInit(&h->doctors);
    waitingRoomInit(&h->waiting);
    emergencyRoomInit(&h->emergency);
}

void hospitalFree(HospitalState *h)
{
    patientBookFree(&h->patients);
    doctorRegistryFree(&h->doctors);
    waitingRoomFree(&h->waiting);
    emergencyRoomFree(&h->emergency);
}
