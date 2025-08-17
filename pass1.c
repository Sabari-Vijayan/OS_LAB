#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

  //DELCARING THE VARIABLES

  FILE *f1, *f2, *f3, *f4;
  char label[30], opcode[30], operand[30];
  char opcode_file_op[30], opcode_file_code[30];
  int locctr = 0, found;

  //OPENING THE FILES

  f1 = fopen("input.txt", "r");
  f2 = fopen("opcode.txt", "r");
  f3 = fopen("out1.txt", "w");
  f4 = fopen("sym1.txt", "w");

  if (!f1 || !f2 || !f3 || !f4) {
    printf("\nCould not open the files\n");
    return 1;
  } else {
    printf("\nFiles succesfully read\n");
  }

  //PRINTING THE ASSEMBLY CODE
  
  /*while (fscanf(f1, "%s %s %s", label, opcode, operand) != EOF) {
    printf("%s %s %s\n", label, opcode, operand);
  }*/

  //PASS 1

  fscanf(f1, "%s %s %s", label, opcode, operand);

  if (strcmp(opcode, "START") == 0) {
    locctr = atoi(operand);
    fprintf(f3, "%s %s %s\n", label, opcode, operand);
    fscanf(f1, "%s %s %s", label, opcode, operand);
  }

  while (strcmp(opcode, "END") != 0) {
    
    found = 0;

    //IF LABEL ADD TO SYMBOL TABLE
    if (strcmp(label, "**") != 0) {
      fprintf(f4, "%d %s\n", locctr, label);
    }

    //SEARCHING OPCODE IN OPCODE TABLE

    rewind(f2);

    while (fscanf(f2, "%s %s", opcode_file_op, opcode_file_code) != EOF) {
      if(strcmp(opcode, opcode_file_op) == 0) {
	found = 1;
	break;
      }
    }

    if(found) {
      fprintf(f3, "%d %s %s %s\n", locctr, label, opcode, operand);
      locctr += 3;
    } else if (strcmp(opcode, "WORD") == 0) {
      fprintf(f3, "%d %s %s %s\n", locctr, label, opcode, operand);
      locctr += 3;
      printf("%d",1);
    } else if (strcmp(opcode, "RESW") == 0) {
      fprintf(f3, "%d %s %s %s\n", locctr, label, opcode, operand);
      locctr += (3 * atoi(operand));
    } else if (strcmp(opcode, "RESB") == 0) {
      fprintf(f3, "%d %s %s %s\n", locctr, label, opcode, operand);
      locctr += atoi(operand);
    } else if (strcmp(opcode, "BYTE") == 0) {
      fprintf(f3, "%d %s %s %s\n", locctr, label, opcode, operand);
      locctr += 1;
    } else {
      printf("Error: Invalid opcode %s\n", opcode);
    }

    fscanf(f1, "%s %s %s", label, opcode, operand);

  }

  fprintf(f3, "%d %s %s %s\n", locctr, label, opcode, operand);

  //CLOSING THE FILES

  fclose(f1);
  fclose(f2);
  fclose(f3);
  fclose(f4);

  return 0;

}














































