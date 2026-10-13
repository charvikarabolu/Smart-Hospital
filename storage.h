#ifndef STORAGE_H
#define STORAGE_H

#include "hospital.h"

int savePatients(const PatientBook *book, const char *filename);
int loadPatients(PatientBook *book, const char *filename);
int saveDoctors(const DoctorRegistry *registry, const char *filename);
int loadDoctors(DoctorRegistry *registry, const char *filename);

#endif
