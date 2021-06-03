// See LICENSE for license details.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"

void print_misa(void)
{
    int misa_bits = __read_csr(CSR_MISA);
    static char misa_chars[30];
    uint8_t index = 0;
    if ((misa_bits >> 30) == 1) {
        misa_chars[index++] = '3';
        misa_chars[index++] = '2';
    } else if ((misa_bits >> 30) == 2) {
        misa_chars[index++] = '6';
        misa_chars[index++] = '4';
    } else if ((misa_bits >> 30) == 3) {
        misa_chars[index++] = '1';
        misa_chars[index++] = '2';
        misa_chars[index++] = '8';
    }
    if ((misa_bits & 0x00000100) != 0) {
        misa_chars[index++] = 'I';
    }
    if ((misa_bits & 0x00001000) != 0) {
        misa_chars[index++] = 'M';
    }
    if ((misa_bits & 0x00000001) != 0) {
        misa_chars[index++] = 'A';
    }
    if ((misa_bits & 0x00000002) != 0) {
        misa_chars[index++] = 'B';
    }
    if ((misa_bits & 0x00000004) != 0) {
        misa_chars[index++] = 'C';
    }
    if ((misa_bits & 0x00000010) != 0) {
        misa_chars[index++] = 'E';
    }
    if ((misa_bits & 0x00000020) != 0) {
        misa_chars[index++] = 'F';
    }
    if ((misa_bits & 0x00000008) != 0) {
        misa_chars[index++] = 'D';
    }
    if ((misa_bits & 0x00010000) != 0) {
        misa_chars[index++] = 'Q';
    }
    if ((misa_bits & 0x00000080) != 0) {
        misa_chars[index++] = 'H';
    }
    if ((misa_bits & 0x00000200) != 0) {
        misa_chars[index++] = 'J';
    }
    if ((misa_bits & 0x00000800) != 0) {
        misa_chars[index++] = 'L';
    }
    if ((misa_bits & 0x00002000) != 0) {
        misa_chars[index++] = 'N';
    }
    if ((misa_bits & 0x00040000) != 0) {
        misa_chars[index++] = 'S';
    }
    if ((misa_bits & 0x00008000) != 0) {
        misa_chars[index++] = 'P';
    }
    if ((misa_bits & 0x00080000) != 0) {
        misa_chars[index++] = 'T';
    }
    if ((misa_bits & 0x00100000) != 0) {
        misa_chars[index++] = 'U';
    }
    if ((misa_bits & 0x00200000) != 0) {
        misa_chars[index++] = 'V';
    }
    if ((misa_bits & 0x00800000) != 0) {
        misa_chars[index++] = 'X';
    }

    misa_chars[index++] = '\0';

    printf("MISA: RV%s\r\n", misa_chars);
}

int main(void)
{
    srand(__get_rv_cycle()  | __get_rv_instret() | __read_csr(CSR_MCYCLE));
    uint32_t rval = rand();
    rv_csr_t misa = __read_csr(CSR_MISA);

    printf("MISA: 0x%lx\r\n", misa);
    print_misa();

    for (int i = 0; i < 20; i ++) {
        printf("%d: Hello World From Nuclei RISC-V Processor!\r\n", i);
    }

    return 0;
}

