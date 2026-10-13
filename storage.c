#include <stdio.h>
#include "storage.h"

int savePatients(const PatientBook *book, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    const PatientNode *p;

    if (fp == NULL)
        return 0;

    p = book->first;
    while (p != NULL) {
        fprintf(fp, "%d|%s|%d|%s|%d\n",
                p->value.id, p->value.name, p->value.age,
                p->value.condition, p->value.emergency);
        p = p->next;
    }

    fclose(fp);
    return 1;
}

int loadPatients(PatientBook *book, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    Patient p;

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%d|%59[^|]|%d|%79[^|]|%d\n",
                  &p.id, p.name, &p.age, p.condition, &p.emergency) == 5)
        addPatient(book, p);

    fclose(fp);
    return 1;
}

int saveDoctors(const DoctorRegistry *registry, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    const DoctorNode *p;

    if (fp == NULL)
        return 0;

    p = registry->front;
    while (p != NULL) {
        fprintf(fp, "%d|%s|%s|%d\n",
                p->data.id, p->data.name,
                p->data.specialty, p->data.available);
        p = p->next;
    }

    fclose(fp);
    return 1;
}

int loadDoctors(DoctorRegistry *registry, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    Doctor d;

    if (fp == NULL)
        return 0;

    while (fscanf(fp, "%d|%59[^|]|%59[^|]|%d\n",
                  &d.id, d.name, d.specialty, &d.available) == 4)
        registerDoctor(registry, d);

    fclose(fp);
    return 1;
}
