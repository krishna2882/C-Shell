#include "headers.h"


void iman(char **args, int num_args) {
    if (num_args < 1) {
        printf("Error: No command provided.\n");
        return;
    }

    char *command = args[0];
    const char *host = "man.he.net";
    char url[4096];
    snprintf(url, sizeof(url), "http://man.he.net/?topic=%s&section=all", command);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return;
    }
    struct hostent *server = gethostbyname(host);
    if (!server) {
        fprintf(stderr, "Error: Could not resolve host '%s'.\n", host);
        close(sockfd);
        return;
    }
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(80)
    };
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to connect to server");
        close(sockfd);
        return;
    }

    char req[10240];
    snprintf(req, sizeof(req), "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", url, host);
    if (send(sockfd, req, strlen(req), 0) < 0) {
        perror("Failed to send request");
        close(sockfd);
        return;
    }

    char buffer[4096];
    ssize_t bytes_received;
    while ((bytes_received = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
        if (fwrite(buffer, 1, bytes_received, stdout) != bytes_received) {
            fprintf(stderr, "Error: Could not write the entire response to stdout.\n");
            break;
        }
    }
    if (bytes_received < 0) {
        perror("Failed to receive response");
    }

    close(sockfd);
}
