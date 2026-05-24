#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Report {
    int id;
    char inspector[32];
    float latitude;
    float longitude;
    char category[32];
    int severity;
    long timestamp;
    char description[128];
} Report;

typedef struct InspectorScore {
    char inspector[32];
    int score;
} InspectorScore;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./scorer <district>\n");
        return 1;
    }

    char path[256];
    snprintf(path, sizeof(path), "districts/%s/reports.dat", argv[1]);

    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Could not open reports.dat");
        return 1;
    }

    InspectorScore scores[100];
    int count = 0;

    Report r;

    while (fread(&r, sizeof(Report), 1, file) == 1) {
        int found = 0;

        for (int i = 0; i < count; i++) {
            if (strcmp(scores[i].inspector, r.inspector) == 0) {
                scores[i].score += r.severity;
                found = 1;
                break;
            }
        }

        if (!found && count < 100) {
            strcpy(scores[count].inspector, r.inspector);
            scores[count].score = r.severity;
            count++;
        }
    }

    fclose(file);

    printf("District: %s\n", argv[1]);

    for (int i = 0; i < count; i++) {
        printf("Inspector: %s | Score: %d\n",
               scores[i].inspector,
               scores[i].score);
    }

    return 0;
}
