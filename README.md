# Smart Hospital Patient Queue Management System

## 1. Project Overview

The **Smart Hospital Patient Queue Management System** is a console-based application written in the C programming language. It is designed to organize basic hospital operations, including patient records, doctor records, normal waiting queues, emergency queues, patient sorting, and data storage.

The project demonstrates modular programming and the use of common data structures in a practical hospital-management scenario.

## 2. Objectives

- Maintain patient information in an organized way.
- Register and list doctors.
- Manage normal patients in first-in, first-out (FIFO) order.
- Give higher priority to patients with more urgent conditions.
- Search for patient records.
- Sort patient records by age.
- Store patient and doctor data in files so that information can be loaded again when the program starts.

## 3. Main Features

- Patient registration and record management.
- Doctor registration and listing.
- Normal waiting-room queue using a circular queue.
- Emergency waiting-room queue ordered by urgency.
- Patient search and age-based sorting.
- Basic file-based persistence for patient and doctor data.
- Menu-driven console interface.

> Note: The exact options available depend on the functions implemented in the source files included with your copy of the project.

## 4. Project File Structure

```text
Smart-Hospital/
├── app.c
├── hospital.c
├── hospital.h
├── patient_record.c
├── patient_record.h
├── doctor_registry.c
├── doctor_registry.h
├── waiting_room.c
├── waiting_room.h
├── emergency_room.c
├── emergency_room.h
├── sorting.c
├── sorting.h
├── storage.c
├── storage.h
├── ARCHITECTURE.txt
└── README.md
```

### File Responsibilities

| File | Purpose |
|---|---|
| `app.c` | Contains the program entry point and starts the application. |
| `hospital.c`, `hospital.h` | Coordinate the main hospital state and menu operations. |
| `patient_record.c`, `patient_record.h` | Define patient records and patient-list operations. |
| `doctor_registry.c`, `doctor_registry.h` | Maintain the doctor registry. |
| `waiting_room.c`, `waiting_room.h` | Manage the normal FIFO waiting queue. |
| `emergency_room.c`, `emergency_room.h` | Manage the emergency priority queue. |
| `sorting.c`, `sorting.h` | Provide patient sorting functionality. |
| `storage.c`, `storage.h` | Save and load supported records using files. |
| `ARCHITECTURE.txt` | Describes the system design and module relationships. |

## 5. Requirements

- A C compiler compatible with the C language features used in the source code.
- Dev-C++ or another C development environment.
- All project `.c` and `.h` files in the same project directory, unless the project is configured with different paths.

## 6. How to Open and Run in Dev-C++

1. Download or copy the complete project folder.
2. Extract the folder if it is compressed as a ZIP file.
3. Open Dev-C++.
4. Create a **Console Application** project and select **C** as the language, or open the supplied Dev-C++ project file if one is included.
5. Add every implementation file (`.c`) to the project. Keep the corresponding `.h` files in the project folder and include them from the source files.
6. Ensure that `app.c` is the file containing `main()` and that there is only one active `main()` function in the project.
7. Select **Execute → Compile & Run**.

### Important Compilation Notes

- Compile all required `.c` files together. Do not try to build each module as a separate program.
- Header files (`.h`) provide declarations; they are not compiled as separate programs.
- If the compiler reports an undefined reference or linker error, check that every required `.c` file is included in the project.
- If the compiler reports a missing header, confirm that the `.h` file is present and that the include path is correct.
- Different Dev-C++ versions may use different compiler settings. Use a C compiler configuration suitable for the source code.

## 7. Data Files

The storage module may create data files in the program's current working directory. Keep these files with the project data if you want to retain saved records between runs.

- Do not manually edit binary data files unless you know their format.
- Back up data files before deleting or replacing them.
- If the program is run from a different working directory, relative data-file paths may refer to a different location.

## 8. Data Structures and Algorithms

- **Singly linked list:** stores patient records and supports operations such as insertion, search, and deletion when implemented.
- **Circular queue:** manages normal waiting-room entries in FIFO order.
- **Priority queue:** places emergency cases according to the urgency value used by the program.
- **Merge sort:** supports sorting patient records by age.
- **File I/O:** supports saving and loading patient and doctor information.

## 9. Testing Checklist

Before sharing the project, test the following:

1. Compile the complete project with no errors.
2. Start the program and confirm that the menu appears.
3. Register a patient and verify that the record can be displayed or searched.
4. Register a doctor and verify that the doctor list is displayed.
5. Add normal patients and confirm FIFO queue behavior.
6. Add emergency cases with different urgency values and confirm the intended priority order.
7. Test sorting with multiple patient ages.
8. Close and restart the program to check whether saved data loads correctly.
9. Test invalid menu choices and empty/full queue conditions where applicable.

## 10. Limitations

This is an educational console project, not a production hospital information system. It does not replace professional medical triage, clinical decision-making, secure hospital databases, authentication, audit logging, or privacy controls. Emergency priority values are demonstration inputs and must not be treated as medical advice.

## 11. Future Enhancements

- Input validation and clearer error messages.
- A graphical user interface.
- Stronger data validation and safer, versioned storage formats.
- Login roles for receptionists, doctors, and administrators.
- Appointment scheduling and reporting.
- A clinically reviewed triage workflow, if the project is extended beyond a classroom demonstration.

## 12. Author / Team

Add your team members, class, department, institution, and project guide here before submission.
