#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "patient_record.h"
#include "doctor_registry.h"
#include "waiting_room.h"
#include "emergency_room.h"

typedef struct {
    PatientBook patients;
    DoctorRegistry doctors;
    WaitingRoom waiting;
    EmergencyRoom emergency;
} HospitalState;

void hospitalInit(HospitalState *h);
void hospitalFree(HospitalState *h);

#endif
