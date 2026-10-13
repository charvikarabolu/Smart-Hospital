#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient_record.h"

static PatientNode *makeNode(Patient p)
{
    PatientNode *n = (PatientNode *)malloc(sizeof(PatientNode));
    if (n != NULL) {
        n->value = p;
        n->next = NULL;
    }
    return n;
}

void patientBookInit(PatientBook *book)
{
    book->first = NULL;
    book->count = 0;
}

void patientBookFree(PatientBook *book)
{
    PatientNode *cur = book->first;
    while (cur != NULL) {
        PatientNode *next = cur->next;
        free(cur);
        cur = next;
    }
    book->first = NULL;
    book->count = 0;
}

Patient *lookupRecord(PatientBook *book, int patientId)
{
    PatientNode *cur = book->first;
    while (cur != NULL) {
        if (cur->value.id == patientId)
            return &cur->value;
        cur = cur->next;
    }
    return NULL;
}

int addPatient(PatientBook *book, Patient p)
{
    PatientNode *n;

    if (lookupRecord(book, p.id) != NULL)
        return 0;

    n = makeNode(p);
    if (n == NULL)
        return 0;

    if (book->first == NULL) {
        book->first = n;
    } else {
        PatientNode *cur = book->first;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = n;
    }

    book->count++;
    return 1;
}

void listPatients(const PatientBook *book)
{
    const PatientNode *cur = book->first;

    if (cur == NULL) {
        printf("No patient records available.\n");
        return;
    }

    printf("\n%-6s %-22s %-6s %-24s %-10s\n",
           "ID", "Name", "Age", "Condition", "Emergency");
    printf("---------------------------------------------------------------------\n");

    while (cur != NULL) {
        printf("%-6d %-22s %-6d %-24s %-10s\n",
               cur->value.id,
               cur->value.name,
               cur->value.age,
               cur->value.condition,
               cur->value.emergency ? "YES" : "NO");
        cur = cur->next;
    }
}

/* Bottom-up merge sort on the linked list. */
static PatientNode *mergeLists(PatientNode *a, PatientNode *b)
{
    PatientNode dummy;
    PatientNode *tail = &dummy;
    dummy.next = NULL;

    while (a != NULL && b != NULL) {
        if (a->value.id <= b->value.id) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    tail->next = (a != NULL) ? a : b;
    return dummy.next;
}

void sortPatientsById(PatientBook *book)
{
    int width;

    if (book->first == NULL || book->first->next == NULL)
        return;

    for (width = 1; width < book->count; width *= 2) {
        PatientNode *cur = book->first;
        PatientNode *newHead = NULL;
        PatientNode *newTail = NULL;

        while (cur != NULL) {
            PatientNode *left = cur;
            PatientNode *right;
            PatientNode *next;
            int i;

            for (i = 1; i < width && cur->next != NULL; ++i)
                cur = cur->next;

            right = cur->next;
            cur->next = NULL;

            cur = right;
            for (i = 1; i < width && cur != NULL && cur->next != NULL; ++i)
                cur = cur->next;

            if (cur != NULL) {
                next = cur->next;
                cur->next = NULL;
            } else {
                next = NULL;
            }

            {
                PatientNode *merged = mergeLists(left, right);
                if (newHead == NULL)
                    newHead = merged;
                else
                    newTail->next = merged;

                newTail = merged;
                while (newTail != NULL && newTail->next != NULL)
                    newTail = newTail->next;
            }

            cur = next;
        }

        book->first = newHead;
    }
} 
