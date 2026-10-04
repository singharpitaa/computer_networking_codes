#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int serverSocket, clientSocket;

    int h[13] = {0};
    int data[9] = {0};

    int i;
    int choice;
    int p1, p2, p4, p8;
    int errorPosition;
    int value = 0;

    char codeword[13];

    struct sockaddr_in server, client;
    socklen_t length = sizeof(client);

    printf("===== HAMMING CODE RECEIVER =====\n");

    // Create TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Server address
    server.sin_family = AF_INET;
    server.sin_port = htons(9000);
    server.sin_addr.s_addr = inet_addr("127.0.0.12");

    // Bind socket
    bind(serverSocket,
         (struct sockaddr *)&server,
         sizeof(server));

    // Listen for sender
    listen(serverSocket, 5);

    printf("\nWaiting for sender...\n");

    // Accept connection
    clientSocket = accept(serverSocket,
                          (struct sockaddr *)&client,
                          &length);

    // Receive Hamming Code
    memset(codeword, 0, sizeof(codeword));

    recv(clientSocket,
         codeword,
         sizeof(codeword) - 1,
         0);

    // Convert received codeword into bits
    for(i = 1; i <= 12; i++)
        h[i] = codeword[i - 1] - '0';

    // Display menu
    printf("\n1. Data received without Error");
    printf("\n2. Data received with Error");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    // Introduce random error
    if(choice == 2)
    {
        srand(time(NULL));

        // Select random bit from position 1 to 12
        errorPosition = rand() % 12 + 1;

        // Flip the selected bit
        h[errorPosition] = h[errorPosition] ^ 1;

        // Display corrupted Hamming Code
        printf("\nReceived Hamming Code: ");

        for(i = 1; i <= 12; i++)
            printf("%d", h[i]);

        printf("\n");
    }

    // Calculate parity bits
    p1 = h[1] ^ h[3] ^ h[5] ^ h[7] ^ h[9] ^ h[11];

    p2 = h[2] ^ h[3] ^ h[6] ^ h[7] ^ h[10] ^ h[11];

    p4 = h[4] ^ h[5] ^ h[6] ^ h[7] ^ h[12];

    p8 = h[8] ^ h[9] ^ h[10] ^ h[11] ^ h[12];

    // Display parity bits in P8 P4 P2 P1 order
    printf("\nParity Bits (P8 P4 P2 P1): %d%d%d%d",
           p8, p4, p2, p1);

   
    errorPosition = p1 + (2 * p2) + (4 * p4) + (8 * p8);

    // Check for error
    if(errorPosition == 0)
    {
        printf("\nNo Error Detected\n");
    }
    else
    {
        printf("\nError Detected at Position: %d",
               errorPosition);

        // Correct the error
        h[errorPosition] = h[errorPosition] ^ 1;

        printf("\nError Corrected");

        // Display corrected Hamming Code
        printf("\nCorrected Hamming Code: ");

        for(i = 1; i <= 12; i++)
            printf("%d", h[i]);

        printf("\n");
    }

    // Extract original 8 data bits
    data[1] = h[3];
    data[2] = h[5];
    data[3] = h[6];
    data[4] = h[7];
    data[5] = h[9];
    data[6] = h[10];
    data[7] = h[11];
    data[8] = h[12];

    // Display recovered binary data
    printf("\nRecovered Binary Data: ");

    for(i = 1; i <= 8; i++)
    {
        printf("%d", data[i]);

        // Convert binary to decimal
        value = value * 2 + data[i];
    }

    // Display recovered character
    printf("\nRecovered Character: %c", value);
    printf("\nASCII Value: %d\n", value);

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
