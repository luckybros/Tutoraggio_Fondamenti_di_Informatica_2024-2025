#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10
#define NAME_LENGTH 50

typedef struct {
    char name[NAME_LENGTH];
    char subject[NAME_LENGTH];
    int grade;
} Record;

Record matrix[MAX_STUDENTS][MAX_SUBJECTS];
int studentCount = 0;
int subjectCount = 0;

void addStudent(const char* name) {
    if (studentCount >= MAX_STUDENTS) {
        printf("Numero massimo di studenti raggiunto.\n");
        return;
    }

    for (int j = 0; j < subjectCount; j++) {
        strcpy(matrix[studentCount][j].name, name);
        strcpy(matrix[studentCount][j].subject, matrix[0][j].subject); // Copia la materia esistente
        matrix[studentCount][j].grade = -1; // Nessun voto assegnato
    }

    studentCount++;
    printf("Studente '%s' aggiunto con successo.\n", name);
}

void addSubject(const char* subject) {
    if (subjectCount >= MAX_SUBJECTS) {
        printf("Numero massimo di materie raggiunto.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        strcpy(matrix[i][subjectCount].name, matrix[i][0].name); // Copia il nome dello studente esistente
        strcpy(matrix[i][subjectCount].subject, subject);
        matrix[i][subjectCount].grade = -1; // Nessun voto assegnato
    }

    subjectCount++;
    printf("Materia '%s' aggiunta con successo.\n", subject);
}

void updateGrade(const char* studentName, const char* subject, int grade) {
    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < subjectCount; j++) {
            if (strcmp(matrix[i][j].name, studentName) == 0 && strcmp(matrix[i][j].subject, subject) == 0) {
                matrix[i][j].grade = grade;
                printf("Voto aggiornato: %s - %s = %d\n", studentName, subject, grade);
                return;
            }
        }
    }
    printf("Studente o materia non trovati.\n");
}

void findBestStudentPerSubject() {
    for (int j = 0; j < subjectCount; j++) {
        int maxGrade = -1;
        char bestStudent[NAME_LENGTH] = "";

        for (int i = 0; i < studentCount; i++) {
            if (matrix[i][j].grade > maxGrade) {
                maxGrade = matrix[i][j].grade;
                strcpy(bestStudent, matrix[i][j].name);
            }
        }

        if (maxGrade != -1) {
            printf("Miglior studente in '%s': %s con voto %d\n", matrix[0][j].subject, bestStudent, maxGrade);
        } else {
            printf("Nessun voto disponibile per la materia '%s'.\n", matrix[0][j].subject);
        }
    }
}

int main() {
    addSubject("Matematica");
    addSubject("Fisica");

    addStudent("Luca");
    addStudent("Maria");

    updateGrade("Luca", "Matematica", 28);
    updateGrade("Maria", "Fisica", 30);

    findBestStudentPerSubject();

    return 0;
}
