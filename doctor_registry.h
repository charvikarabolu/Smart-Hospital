#ifndef DOCTOR_REGISTRY_H
#define DOCTOR_REGISTRY_H

#define DOCTOR_NAME_SIZE 60
#define SPECIALTY_SIZE 60

typedef struct {
    int id;
    char name[DOCTOR_NAME_SIZE];
    char specialty[SPECIALTY_SIZE];
    int available;
} Doctor;

typedef struct DoctorNode {
    Doctor data;
    struct DoctorNode *next;
} DoctorNode;

typedef struct {
    DoctorNode *front;
    int size;
} DoctorRegistry;

void doctorRegistryInit(DoctorRegistry *registry);
void doctorRegistryFree(DoctorRegistry *registry);
int registerDoctor(DoctorRegistry *registry, Doctor d);
Doctor *findDoctor(DoctorRegistry *registry, int id);
void showDoctors(const DoctorRegistry *registry);
void changeDoctorAvailability(DoctorRegistry *registry, int id, int available);

#endif
