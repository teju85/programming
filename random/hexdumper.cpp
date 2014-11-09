#include <stdio.h>

/**
 * @brief Entry point function
 * @param argc number of commandline args
 * @param argv commandline args
 * @return 0 on success, else non-zero
 */
int main(int argc, char** argv) {
    int offset = 0x0611EF00;
    FILE* fp = fopen("rcm_applet.bin", "rb");
    char buffer[24];
    int len;
    while(!feof(fp)) {
        int read = fread(buffer, sizeof(char), 24, fp);
        if(read > 0) {
            printf("0x%08X ", offset);
            for(int i=0;i<read;++i) {
                printf(" %02x", (unsigned char)buffer[i]);
            }
            printf("\n");
            offset += read;
        }
    }
    fclose(fp);
    return 0;
}
