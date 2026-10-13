# Smart Hospital Patient Queue Management System

## Overview
This C console project manages patient records, doctor records, a normal waiting room, an emergency queue, and text-file storage. The AI classification option is an educational demonstration added as a separate module.

## Modules
- `app.c` — console menus and user interaction.
- `patient_record.c/.h` — patient linked-list records, lookup, listing, and merge sort by ID.
- `doctor_registry.c/.h` — doctor registry using a linked list.
- `waiting_room.c/.h` — circular-array FIFO waiting room.
- `emergency_room.c/.h` — array-based priority queue for emergency entries.
- `storage.c/.h` — saves and loads patient and doctor records.
- `hospital.c/.h` — initializes and releases the project modules.
- `ai_triage.c/.h` — Naive Bayes classroom demonstration using fabricated training examples.

## AI demo integration
Select **6. AI classification demonstration** from the main menu. Enter `0` for No or `1` for Yes for each of the five demonstration inputs. The module validates the feature values and prints one of its demonstration categories.

The AI output is **not clinically validated**. The training rows are synthetic and must not be treated as medical evidence. The AI option does not alter the emergency queue or replace the judgement of qualified healthcare staff.

## Build with GCC
From this folder, run:

```sh
gcc -std=c99 -Wall -Wextra -pedantic app.c hospital.c patient_record.c doctor_registry.c waiting_room.c emergency_room.c storage.c ai_triage.c -lm -o smart_hospital
```

On Windows with MinGW GCC, the same command can be used in the project directory. If using Dev-C++, add `ai_triage.c` to the existing project along with the other `.c` files. Do not enable `AI_TRIAGE_STANDALONE` for the integrated project, because `app.c` already contains `main()`.

## Test notes
The integrated sources compiled with GCC using C99, `-Wall -Wextra -pedantic`, and `-lm` without compiler warnings in this environment. A scripted run verified that menu option 6 opens the demo, valid binary inputs produce a result, and an input outside 0/1 is rejected. This is a basic integration check, not full clinical validation or exhaustive testing.

## Recent data-structure improvement
The patient book and doctor registry now cache both the first and last linked-list nodes. Appending a new patient or doctor therefore does not scan the whole list to find its end: insertion is O(1) after the duplicate-ID lookup. Patient sorting rearranges the linked nodes, so it refreshes the cached tail afterward. This is a real implementation change; it is not a promise about any similarity-checker score.

## Suggested regression checks
1. Register two doctors and verify both appear in registration order.
2. Register two patients with distinct IDs and confirm a repeated ID is rejected.
3. Sort patients by ID, then add another patient and list the records; this checks that the cached tail remains correct after sorting.
4. Fill and drain the waiting room, checking that FIFO order is preserved.
5. Add emergency patients with different priorities and confirm the higher priority is removed first.
6. Try invalid AI feature values and confirm the demo rejects them.
