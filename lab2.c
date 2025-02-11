#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_child_task(int child_num) {
    char *cmd;
    char *args[3];

    switch (child_num) {
        case 0:
            cmd = "echo"; args[0] = "echo"; args[1] = "Hello, User!"; args[2] = NULL; break;
        case 1:
            cmd = "ls"; args[0] = "ls"; args[1] = "-l"; args[2] = NULL; break;
        case 2:
            cmd = "date"; args[0] = "date"; args[1] = NULL; break;
        case 3:
            cmd = "pwd"; args[0] = "pwd"; args[1] = NULL; break;
        case 4:
            cmd = "whoami"; args[0] = "whoami"; args[1] = NULL; break;
        case 5:
            cmd = "hostname"; args[0] = "hostname"; args[1] = NULL; break;
        case 6:
            cmd = "uptime"; args[0] = "uptime"; args[1] = NULL; break;
        case 7:
            cmd = "df"; args[0] = "df"; args[1] = "-h"; args[2] = NULL; break;
        case 8:
            cmd = "free"; args[0] = "free"; args[1] = "-m"; args[2] = NULL; break;
        case 9:
            cmd = "ps"; args[0] = "ps"; args[1] = "-e"; args[2] = NULL; break;
        default:
            cmd = "echo"; args[0] = "echo"; args[1] = "Default case!"; args[2] = NULL; break;
    }

    execvp(cmd, args);
    perror("execvp failed");
    exit(EXIT_FAILURE);
}



int main() {
    const int num_children = 10;
    pid_t pids[num_children];

    for (int i = 0; i < num_children; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pids[i] == 0) {
            printf("Child %d (PID %d) executing...\n", i, getpid());
            execute_child_task(i % 3);
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < num_children; i++) {
    int status;
    pid_t pid = wait(&status);

		for (int j = 0; j < num_children; j++) {
			if (pids[j] == pid) {
				if (WIFEXITED(status)) {
					printf("Child %d (PID %d) exited with status %d\n", j, pid, WEXITSTATUS(status));
				} else if (WIFSIGNALED(status)) {
					printf("Child %d (PID %d) terminated by signal %d\n", j, pid, WTERMSIG(status));
				}
				break;
			}
		}
	}

    return 0;
}
