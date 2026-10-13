#include <stdio.h>
#include <stdlib.h>
#include "doctor_registry.h"

void doctorRegistryInit(DoctorRegistry *registry)
{
    registry->front = NULL;
    registry->back = NULL;
    registry->size = 0;
}

void doctorRegistryFree(DoctorRegistry *registry)
{
    DoctorNode *p = registry->front;
    while (p != NULL) {
        DoctorNode *next = p->next;
        free(p);
        p = next;
    }
    registry->front = NULL;
    registry->back = NULL;
    registry->size = 0;
}

Doctor *findDoctor(DoctorRegistry *registry, int id)
{
    DoctorNode *p = registry->front;
    while (p != NULL) {
        if (p->data.id == id)
            return &p->data;
        p = p->next;
    }
    return NULL;
}

int registerDoctor(DoctorRegistry *registry, Doctor d)
{
    DoctorNode *n;

    if (findDoctor(registry, d.id) != NULL)
        return 0;

    n = (DoctorNode *)malloc(sizeof(DoctorNode));
    if (n == NULL)
        return 0;

    n->data = d;
    n->next = NULL;

    if (registry->back == NULL) {
        registry->front = n;
    } else {
        registry->back->next = n;
    }
    registry->back = n;

    registry->size++;
    return 1;
}

void showDoctors(const DoctorRegistry *registry)
{
    const DoctorNode *p = registry->front;

    if (p == NULL) {
        printf("No doctors registered.\n");
        return;
    }

    printf("\n%-6s %-22s %-20s %-10s\n",
           "ID", "Name", "Specialty", "Available");
    printf("------------------------------------------------------------\n");

    while (p != NULL) {
        printf("%-6d %-22s %-20s %-10s\n",
               p->data.id,
               p->data.name,
               p->data.specialty,
               p->data.available ? "YES" : "NO");
        p = p->next;
    }
}

void changeDoctorAvailability(DoctorRegistry *registry, int id, int available)
{
    Doctor *d = findDoctor(registry, id);
    if (d != NULL)
        d->available = available ? 1 : 0;
}
