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
        unsigned char password[20];

        printf("%s\n", correct_hash);

        printf("Insert your password: ");
        scanf("%37s", password);
        printf("%s\n", password);
        for (int i = 0; i < 20; i++) {
          printf("%d", correct_hash[i]);
        }
        printf("\n");
        printf("%s\n", password);
        SHA1(password, strlen((char *)password), password);
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

stud492@testbed:~$ gcc -lssl overshade.c -lcrypto -fno-stack-protector
stud492@testbed:~$ ./a.out
AAAAAAAAAAAAAAAAAAAA
Insert your password: zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
12212212212212206565656565656565656565656565
zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
WRONG PASSWORD!
stud492@testbed:~$ cat /challenges/overshade/
flag         overshade    overshade.c
stud492@testbed:~$ cat /challenges/overshade/overshade.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

int
main(void) {
        FILE *file;
        unsigned char flag[128];
        unsigned char correct_hash[20] = {
                0x4a, 0xc9, 0xb0, 0x57, 0xf8, 0x02, 0x12, 0x60, 0x6c, 0xea,
                0xab, 0xf3, 0xc6, 0x50, 0x5d, 0xaf, 0xed, 0x40, 0xa4, 0x50
        };
        unsigned char password[20];

        printf("Insert your password: ");
        scanf("%37s", password);
        SHA1(password, strlen((char *)password), password);
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
