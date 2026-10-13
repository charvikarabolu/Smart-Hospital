#ifndef PATIENT_RECORD_H
#define PATIENT_RECORD_H

#define NAME_SIZE 60
#define DISEASE_SIZE 80

typedef struct {
    int id;
    char name[NAME_SIZE];
    int age;
    char condition[DISEASE_SIZE];
    int emergency;
} Patient;

typedef struct PatientNode {
    Patient value;
    struct PatientNode *next;
} PatientNode;

typedef struct {
    PatientNode *first;
    PatientNode *last; /* cached end node avoids rescanning on every insert */
    int count;
} PatientBook;

void patientBookInit(PatientBook *book);
void patientBookFree(PatientBook *book);
int addPatient(PatientBook *book, Patient p);
Patient *lookupRecord(PatientBook *book, int patientId);
void listPatients(const PatientBook *book);
void sortPatientsById(PatientBook *book);

#endif
