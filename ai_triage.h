#ifndef AI_TRIAGE_H
#define AI_TRIAGE_H

/*
 * Educational AI demonstration for the Smart Hospital project.
 *
 * IMPORTANT:
 * This toy Naive Bayes model uses synthetic examples and is NOT clinically
 * validated. Do not use its output for real patient triage, diagnosis, or
 * treatment. Real symptoms must be assessed by qualified healthcare staff.
 */

typedef struct {
    int fever;                 /* 0 = no, 1 = yes */
    int cough;                 /* 0 = no, 1 = yes */
    int breathing_difficulty;  /* 0 = no, 1 = yes */
    int severe_pain;            /* 0 = no, 1 = yes */
    int confusion;              /* 0 = no, 1 = yes */
} AIFeatures;

typedef enum {
    AI_DEMO_ROUTINE = 0,
    AI_DEMO_REVIEW_SOON = 1,
    AI_DEMO_URGENT_REVIEW = 2
} AIDemoClass;

/* Returns 1 when features are valid; otherwise returns 0. */
int ai_features_valid(const AIFeatures *features);

/*
 * Classifies the input using a tiny synthetic training set.
 * This is only a classroom demonstration, not a medical decision.
 */
AIDemoClass ai_demo_classify(const AIFeatures *features);

/* Human-readable label for the demonstration output. */
const char *ai_demo_class_name(AIDemoClass result);

/* Prints a disclaimer and explains the result is not medical advice. */
void ai_demo_print_result(const AIFeatures *features);

#endif
