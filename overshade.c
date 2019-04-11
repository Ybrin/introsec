#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

int
main(void) {
        FILE *file;
        unsigned char flag[128];
        unsigned char correct_hash[20] = {
                0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
                0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41
        };
        unsigned char password[40];

        printf("%s\n", correct_hash);

        for (int i = 0; i < 20; i++) {
          printf("%d", correct_hash[i]);
        }
        printf("\n");

        printf("Insert your password: ");
        scanf("%37s", password);

        for (int i = 0; i < 40; i++) {
          printf("%d ", password[i]);
        }
        printf("\n");

        for (int i = 0; i < 20; i++) {
          printf("%d", correct_hash[i]);
        }
        printf("\n");

        SHA1(password, strlen((char *)password), password);

        for (int i = 0; i < 40; i++) {
          printf("%d ", password[i]);
        }
        printf("\n");

        if(memcmp(password, correct_hash, 20) == 0) {
                printf("CORRECT PASSWORD!\n");
                file = fopen("/challenges/overshade/flag", "r");
                if(file != NULL) {
                        fscanf(file, "%s", flag);
                        fclose(file);
                        printf("Flag: %s\n", flag);
                } else {
                        printf("Error while opening the flag file\n");
                }
        } else {
                printf("WRONG PASSWORD!\n");
        }
        fflush(stdout);

        return 0;
}
