#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void start_monitor()
{
    pid_t hub_mon = fork();

    if (hub_mon < 0)
    {
        perror("fork");
        return;
    }

    if (hub_mon > 0)
    {
        printf("hub_mon created PID=%d\n",
               hub_mon);

        return;
    }

    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid_t monitor_pid = fork();
    if (monitor_pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execl("./monitor_reports","monitor_reports",NULL);
        perror("execl");
        exit(1);
    }

    close(fd[1]);
    char buffer[256];
    int saw_exit = 0;

    while (1)
    {
        int n = read(fd[0], buffer,sizeof(buffer) - 1);
        if (n <= 0)
            break;
        buffer[n] = '\0';
        if (strstr(buffer, "EXIT|") != NULL || strstr(buffer, "ERROR|") != NULL) {
            saw_exit = 1;
        }
        printf("[MONITOR] %s", buffer);
        fflush(stdout);
    }

    close(fd[0]);
    waitpid(monitor_pid, NULL, 0);

    if (saw_exit) {
        printf("[MONITOR] Monitor process ended\n");
    } else {
        printf("[MONITOR] Monitor output pipe closed\n");
    }
    fflush(stdout);
    exit(0);
}

void calculate_scores(char *line)
{
    char *token = strtok(line, " ");
    pid_t children[100];
    int read_fds[100];
    int children_count = 0;

    while ((token = strtok(NULL, " ")) != NULL) {
        if (children_count >= 100) {
            fprintf(stderr, "Too many districts; maximum is 100\n");
            break;
        }

        int fd[2];

        if (pipe(fd) == -1) {
            perror("pipe");
            continue;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            close(fd[0]);
            close(fd[1]);
            continue;
        }

        if (pid == 0) {
            close(fd[0]);

            dup2(fd[1], STDOUT_FILENO);

            close(fd[1]);

            execl("./scorer", "scorer", token, NULL);

            perror("execl scorer");
            exit(1);
        }

        close(fd[1]);
        children[children_count] = pid;
        read_fds[children_count] = fd[0];
        children_count++;
    }

    char buffer[256];

    printf("Combined workload report\n");

    for (int i = 0; i < children_count; i++) {
        int n;

        while ((n = read(read_fds[i], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0';
            printf("%s", buffer);
        }

        close(read_fds[i]);
    }

    for (int i = 0; i < children_count; i++) {
        waitpid(children[i], NULL, 0);
    }
}

int main()
{
    char line[512];

    while (1)
    {
        printf("city_hub> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0)
            break;

        if (strcmp(line, "start-monitor") == 0 || strcmp(line, "start_monitor") == 0)
	  {
	    start_monitor();
	  }
	else if (strncmp(line, "calculate_scores", 16) == 0)
	  {
	    calculate_scores(line);
	  }
	else
	  {
	    printf("Unknown command\n");
	  }
    }

    return 0;
}
