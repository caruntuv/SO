#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include <time.h>

#define NAME_LEN 32
#define CATEGORY_LEN 32
#define DESC_LEN 128

typedef struct {
    int id;
    char inspector[NAME_LEN];
    float latitude;
    float longitude;
    char category[CATEGORY_LEN];
    int severity;
    time_t timestamp;
    char description[DESC_LEN];
} Report;

void create_district(const char *name) {
    char base_path[100] = "districts/";
    char full_path[100];

    strcpy(full_path, base_path);
    strcat(full_path, name);

    if (mkdir(full_path, 0750) == -1) {
        perror("Error creating directory");
        return;
    }

    chmod(full_path, 0750);

    char reports_path[150];
    strcpy(reports_path, full_path);
    strcat(reports_path, "/reports.dat");

    int fd1 = open(reports_path, O_CREAT | O_RDWR, 0664);
    if (fd1 == -1) {
        perror("Error creating reports.dat");
        return;
    }
    close(fd1);
    chmod(reports_path, 0664);

    char cfg_path[150];
    strcpy(cfg_path, full_path);
    strcat(cfg_path, "/district.cfg");

    int fd2 = open(cfg_path, O_CREAT | O_RDWR, 0640);
    if (fd2 == -1) {
        perror("Error creating district.cfg");
        return;
    }
    close(fd2);
    chmod(cfg_path, 0640);

    char log_path[150];
    strcpy(log_path, full_path);
    strcat(log_path, "/logged_district");

    int fd3 = open(log_path, O_CREAT | O_RDWR, 0644);
    if (fd3 == -1) {
        perror("Error creating logged_district");
        return;
    }
    close(fd3);
    chmod(log_path, 0644);

    printf("District '%s' created successfully!\n", name);
}

void log_action(const char *district, const char *role, const char *user, const char *action) {
    char path[150];

    // build: districts/downtown/logged_district
    strcpy(path, "districts/");
    strcat(path, district);
    strcat(path, "/logged_district");

    // open file in append mode
    int fd = open(path, O_WRONLY | O_APPEND);

    if (fd == -1) {
        perror("Error opening log file");
        return;
    }

    // get current time
    time_t now = time(NULL);

    // write log line
    dprintf(fd, "[%ld] %s %s %s\n", now, role, user, action);

    close(fd);
}

void add_report(const char *district, const char *user) {
    char path[150];

    // build path to reports.dat
    strcpy(path, "districts/");
    strcat(path, district);
    strcat(path, "/reports.dat");

    int fd = open(path, O_WRONLY | O_APPEND);

    if (fd == -1) {
        perror("Error opening reports file");
        return;
    }

    Report r;

    // TEMP values (we'll improve later)
    r.id = 1;  // later we auto-increment
    strcpy(r.inspector, user);
    r.latitude = 45.75;
    r.longitude = 21.23;
    strcpy(r.category, "road");
    r.severity = 2;
    r.timestamp = time(NULL);
    strcpy(r.description, "Test issue");

    write(fd, &r, sizeof(Report));

    close(fd);

    printf("Report added!\n");
}

int main(int argc, char *argv[])
{
    if (argc < 5) {
        printf("Usage: ./city_manager --role <role> --user <name> <command>\n");
        return 1;
    }

    char role[20] = "";
    char user[50] = "";
    char district[50] = "";
    int add_flag = 0;
    int report_flag = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--role") == 0 && i + 1 < argc) {
            strcpy(role, argv[i + 1]);
        }

        if (strcmp(argv[i], "--user") == 0 && i + 1 < argc) {
            strcpy(user, argv[i + 1]);
        }

        if (strcmp(argv[i], "--add") == 0 && i + 1 < argc) {
            strcpy(district, argv[i + 1]);
            add_flag = 1;
        }
	if (strcmp(argv[i], "--report") == 0 && i + 1 < argc) {
	  strcpy(district, argv[i + 1]);
	  report_flag = 1;
	}
    }

    if (add_flag && strcmp(role, "manager") != 0) {
        printf("Only manager can add districts!\n");
        return 1;
    }

    if (add_flag) {
        create_district(district);
	char action[100] = "created district ";
	strcat(action, district);
	log_action(district, role, user, action);
    } else {
        printf("No valid command provided.\n");
    }

    if (report_flag && strcmp(role, "inspector") != 0) {
    printf("Only inspector can add reports!\n");
    return 1;
    }
    if (report_flag) {
    add_report(district, user);

    char action[100] = "added report in ";
    strcat(action, district);

    log_action(district, role, user, action);}

    return 0;
}
