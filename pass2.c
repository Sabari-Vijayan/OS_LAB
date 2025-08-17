#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char opcode[20], operand[20], symbol[20], label[20];
    char code[20], mnemonic[25], objectcode[20], add[20];
    char character;
    int flag, flag1, locctr, loc;

    FILE *fp1, *fp2, *fp3, *fp4;

    // Open files
    fp1 = fopen("out1.txt", "r");    // Intermediate file from Pass 1
    fp2 = fopen("twoout.txt", "w");  // Final output listing
    fp3 = fopen("opcode.txt", "r");  // Opcode table
    fp4 = fopen("sym1.txt", "r");    // Symbol table

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening files!\n");
        return 1;
    }

    // Read first line (START statement)
    fscanf(fp1, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        fprintf(fp2, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%d %s %s %s", &locctr, label, opcode, operand);
    }

    // Process till END
    while (strcmp(opcode, "END") != 0) {
        flag = 0;

        // Search opcode in OPTAB
        rewind(fp3);
        while (fscanf(fp3, "%s %s", code, mnemonic) != EOF) {
            if ((strcmp(opcode, code) == 0) && (strcmp(mnemonic, "*") != 0)) {
                flag = 1;
                break;
            }
        }

        if (flag == 1) {  // opcode found
            flag1 = 0;
            rewind(fp4);

            // Search operand in SYMTAB
            while (fscanf(fp4, "%s %d", symbol, &loc) != EOF) {
                if (strcmp(symbol, operand) == 0) {
                    flag1 = 1;
                    break;
                }
            }

            if (flag1 == 1) {
                sprintf(add, "%d", loc); // convert address to string
                strcpy(objectcode, mnemonic);
                strcat(objectcode, add);
            }
        }
        else if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0) {
            if (operand[0] == 'C' || operand[0] == 'X') {
                character = operand[2];          // e.g., C'Z'
                sprintf(add, "%d", character);   // ASCII value
                strcpy(objectcode, add);
            }
            else {
                strcpy(objectcode, operand);     // direct constant
            }
        }
        else {
            strcpy(objectcode, ""); // No object code for RESW, RESB, etc.
        }

        // Write to output file
        fprintf(fp2, "%s\t%s\t%s\t%d\t%s\n", label, opcode, operand, locctr, objectcode);

        // Read next line
        fscanf(fp1, "%d %s %s %s", &locctr, label, opcode, operand);
    }

    // Write END statement
    fprintf(fp2, "%s\t%s\t%s\t%d\n", label, opcode, operand, locctr);

    // Close all files
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}
