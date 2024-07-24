#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>


uint32_t bin_read(char* path) {
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL) return (uint32_t)1;

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (size != 4) return (uint32_t)1;

    uint32_t output[4];
    fread(output, sizeof(output), 1, fp);
    fclose(fp);
    return ntohl(*output);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("syntax : add-nbo <file1> <file2>\n");
        return 1;
    }

    uint32_t bin1 = bin_read(argv[1]);
    uint32_t bin2 = bin_read(argv[2]);
    if (bin1 == 1 || bin2 == 1) {
        printf("error : file size mismatch\n");
        return 1;
    }
    uint32_t res = bin1 + bin2;
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", bin1, bin1, bin2, bin2, res, res);

    return 0;
}