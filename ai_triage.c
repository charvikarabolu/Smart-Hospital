#include <stdio.h>
#include <math.h>
#include "ai_triage.h"

/*
 * Tiny, synthetic dataset for demonstrating Naive Bayes.
 * Labels are arbitrary demonstration classes, not medical labels.
 * These records are fabricated for programming practice and must never be
 * interpreted as clinical evidence.
 *
 * Feature order:
 * fever, cough, breathing difficulty, severe pain, confusion
 * Class:
 * 0 = routine demo
 * 1 = review soon demo
 * 2 = urgent review demo
 */
typedef struct {
    int x[5];
    int class_id;
} TrainingRow;

static const TrainingRow training_data[] = {
    {{0, 0, 0, 0, 0}, 0},
    {{1, 0, 0, 0, 0}, 0},
    {{0, 1, 0, 0, 0}, 0},
    {{1, 1, 0, 0, 0}, 1},
    {{1, 0, 0, 1, 0}, 1},
    {{0, 1, 0, 1, 0}, 1},
    {{1, 1, 0, 1, 0}, 1},
    {{0, 0, 1, 0, 0}, 2},
    {{1, 0, 1, 0, 0}, 2},
    {{0, 1, 1, 0, 0}, 2},
    {{0, 0, 0, 1, 1}, 2},
    {{1, 1, 1, 1, 1}, 2}
};

#define FEATURE_COUNT 5
#define CLASS_COUNT 3
#define ROW_COUNT (sizeof(training_data) / sizeof(training_data[0]))

static int get_feature(const AIFeatures *f, int index)
{
    switch (index) {
        case 0: return f->fever;
        case 1: return f->cough;
        case 2: return f->breathing_difficulty;
        case 3: return f->severe_pain;
        case 4: return f->confusion;
        default: return 0;
    }
}

int ai_features_valid(const AIFeatures *features)
{
    if (features == NULL) {
        return 0;
    }

    if ((features->fever != 0 && features->fever != 1) ||
        (features->cough != 0 && features->cough != 1) ||
        (features->breathing_difficulty != 0 &&
         features->breathing_difficulty != 1) ||
        (features->severe_pain != 0 && features->severe_pain != 1) ||
        (features->confusion != 0 && features->confusion != 1)) {
        return 0;
    }

    return 1;
}

AIDemoClass ai_demo_classify(const AIFeatures *features)
{
    int class_count[CLASS_COUNT] = {0, 0, 0};
    int feature_ones[CLASS_COUNT][FEATURE_COUNT] = {{0}};
    double log_score[CLASS_COUNT];
    int i, j, c, best_class = 0;

    if (!ai_features_valid(features)) {
        return AI_DEMO_REVIEW_SOON;
    }

    for (i = 0; i < (int)ROW_COUNT; ++i) {
        c = training_data[i].class_id;
        class_count[c]++;

        for (j = 0; j < FEATURE_COUNT; ++j) {
            if (training_data[i].x[j] == 1) {
                feature_ones[c][j]++;
            }
        }
    }

    for (c = 0; c < CLASS_COUNT; ++c) {
        /* Laplace smoothing avoids taking log(0). */
        log_score[c] = log((double)(class_count[c] + 1) /
                           (double)(ROW_COUNT + CLASS_COUNT));

        for (j = 0; j < FEATURE_COUNT; ++j) {
            double probability_one =
                (double)(feature_ones[c][j] + 1) /
                (double)(class_count[c] + 2);
            int value = get_feature(features, j);

            if (value == 1) {
                log_score[c] += log(probability_one);
            } else {
                log_score[c] += log(1.0 - probability_one);
            }
        }
    }

    for (c = 1; c < CLASS_COUNT; ++c) {
        if (log_score[c] > log_score[best_class]) {
            best_class = c;
        }
    }

    return (AIDemoClass)best_class;
}

const char *ai_demo_class_name(AIDemoClass result)
{
    switch (result) {
        case AI_DEMO_ROUTINE:
            return "Routine demo category";
        case AI_DEMO_REVIEW_SOON:
            return "Review-soon demo category";
        case AI_DEMO_URGENT_REVIEW:
            return "Urgent-review demo category";
        default:
            return "Unknown demo category";
    }
}

void ai_demo_print_result(const AIFeatures *features)
{
    AIDemoClass result;

    if (!ai_features_valid(features)) {
        printf("\nInvalid input. Enter 0 for No or 1 for Yes.\n");
        return;
    }

    result = ai_demo_classify(features);

    printf("\n--- AI CLASSIFICATION DEMO ---\n");
    printf("Model: Naive Bayes with synthetic training examples\n");
    printf("Demo output: %s\n", ai_demo_class_name(result));
    printf("This is not a medical assessment or treatment recommendation.\n");
    printf("A qualified healthcare professional must assess real symptoms.\n");
    printf("------------------------------\n");
}

#ifdef AI_TRIAGE_STANDALONE
int main(void)
{
    AIFeatures features;

    printf("SMART HOSPITAL - AI CLASSIFICATION DEMO\n");
    printf("Enter 0 for No and 1 for Yes. Synthetic educational model only.\n");
    printf("This program must not be used for real medical triage.\n\n");

    printf("Fever? ");
    if (scanf("%d", &features.fever) != 1) return 1;

    printf("Cough? ");
    if (scanf("%d", &features.cough) != 1) return 1;

    printf("Breathing difficulty? ");
    if (scanf("%d", &features.breathing_difficulty) != 1) return 1;

    printf("Severe pain? ");
    if (scanf("%d", &features.severe_pain) != 1) return 1;

    printf("Confusion? ");
    if (scanf("%d", &features.confusion) != 1) return 1;

    if (!ai_features_valid(&features)) {
        printf("Invalid input. Please enter only 0 or 1.\n");
        return 1;
    }

    ai_demo_print_result(&features);
    printf("For this project, queue decisions must be made by staff, not this model.\n");
    return 0;
}
#endif
