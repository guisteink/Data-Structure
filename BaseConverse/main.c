/*
 * eletronica digital. 2019/2
 * funcoes que convertem binarios, decimal para respectivas bases
 * guilherme stein kuhn
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************************************
 * PROGRAMA 1 - CONVERSAO BINARIO PARA DECIMAL
 */
int hasVirg(char dec_num[], int tam) {
  int i;
  for (i = 0; i <= tam; i++)
    if (dec_num[i] == ',')
      return i + 1;
  return 0;
}
void convertBinDec(char dec_num[]) {
  int len = strlen(dec_num);           // tamanho do numero decimal
  int posVirg = hasVirg(dec_num, len); // posi�ao da virgula binaria

  if (posVirg == 0) {
    float num = 0;
    int j = 0, valor = 0;

    while (j < len) {
      // valor � convertido de char pra inteiro;;;
      valor = (int)(dec_num[j] > 47 && dec_num[j] < 58) ? dec_num[j] - 48 : -1;
      num = num + valor * pow(2, len - j - 1);
      j++;
    }
    printf("\ndecimal: %f", num);
  }
  if (posVirg != 0) {
    float num = 0;
    int j = 0, valor = 0;

    while (j < posVirg) {
      valor = (int)(dec_num[j] > 47 && dec_num[j] < 58) ? dec_num[j] - 48 : -1;
      num = num + valor * pow(2, posVirg - j - 1);
      j++;
    }
    while (j < len) {
      valor = (int)(dec_num[j] > 47 && dec_num[j] < 58) ? dec_num[j] - 48 : -1;
      num = num + valor * (1 / pow(2, len - j - 1));
      j++;
    }
    printf("\ndecimal: %.3f", num);
  }
}

/************************************************
 * PROGRAMA 2 - CONVERSAO DE DECIMAL PARA BINARIO
 */
int find2(int decimal_number) {
  if (decimal_number == 0)
    return 0;
  else
    return (decimal_number % 2 + 10 * find2(decimal_number / 2));
}
void convertDecBin(char bin_num[]) {
  int num = atoi(bin_num);
  int num_dec = find2(num);
  printf("\nbinario: %d", num_dec);
}

/*
 * PROGRAMA 3 - CONVERSAO DE BASE X PARA BASE Y
 */

int find8(int decimal_number) {
  if (decimal_number == 0)
    return 0;
  else
    return (decimal_number % 8 + 10 * find8(decimal_number / 8));
}
int find16(int decimal_number) {
  if (decimal_number == 0)
    return 0;
  else
    return (decimal_number % 16 + 10 * find16(decimal_number / 16));
}

/*
 * converte todas as entradas de base X, para decimal
 */
int toDec(char numero[], int base) {
  if (numero == "0")
    return 0;
  int tam = strlen(numero);
  int posVirgula = hasVirg(numero, tam);

  if (posVirgula == 0) {
    float num = 0;
    int i = 0, valor = 0;
    while (i < tam) {
      valor = (int)(numero[i] > 47 && numero[i] < 58) ? numero[i] - 48 : -1;
      num = num + valor * pow(base, tam - i - 1);
      i++;
    }
    return num;
  }
  if (posVirgula != 0) {
    float num = 0;
    int i = 0, valor = 0;
    while (i < posVirgula) {
      valor = (int)(numero[i] > 47 && numero[i] < 58) ? numero[i] - 48 : -1;
      num = num + valor * pow(base, tam - i - 1);
      i++;
    }
    while (posVirgula < tam) {
      valor = (int)(numero[i] > 47 && numero[i] < 58) ? numero[i] - 48 : -1;
      num = num + valor * (1 / pow(base, tam - i - 1));
      i++;
    }
    return num;
  }
}

void convert(char numero[], int basex, int basey) {
  if (basex == basey) {
    if (basex == 2) {
      printf("\nbinario: %s", numero);
    }
    if (basex == 8) {
      printf("\noctal: %s", numero);
    }
    if (basex == 10) {
      printf("\ndecimal: %s", numero);
    }
    if (basex == 16) {
      printf("\nhexadecimal: %s", numero);
    }
  }
  if ((basex || basey) != (2 || 8 || 10 || 16))
    printf("\nerro!!!");
  int chave = 0;

  switch (basex) {
  case 2:
    switch (basey) {
    case 8:
      chave = toDec(numero, 2);
      int octal = find8(chave);
      printf("\noctal: %d", octal);
      break;
    case 10:
      convertBinDec(numero);
      break;
    case 16:
      chave = toDec(numero, 2);
      int hexa = find16(chave);
      printf("\nhexa: %d", hexa);
      break;
    default:
      break;
    }

  case 8:
    switch (basey) {
    case 2:
      chave = toDec(numero, 8);
      int bin = find2(chave);
      printf("\nbinario: %d", bin);
      break;
    case 10:
      chave = toDec(numero, 8);
      printf("\ndecimal: %d", chave);
      break;
    case 16:
      chave = toDec(numero, 8);
      int hexa = find16(chave);
      printf("\nhexa: %d", hexa);
      break;

    default:
      break;
    }
  case 10:
    switch (basey) {
    case 2:
      convertDecBin(numero);
      break;
    case 8:
      chave = atoi(numero);
      int octal = find8(chave);
      printf("\noctal: %d", octal);
      break;
    case 16:
      chave = atoi(numero);
      int hexa = find16(chave);
      printf("\nhexa: %d", hexa);
      break;
    }
  default:
    break;

  case 16:
    switch (basey) {
    case 2:
      chave = toDec(numero, 16);
      int bin = find16(chave);
      printf("\nbinario: %d", bin);
      break;
    case 8:
      chave = toDec(numero, 16);
      int octal = find8(chave);
      printf("\noctal: %d", octal);
      break;
    case 10:
      chave = toDec(numero, 16);
      printf("\ndecimal: %d", chave);
      break;

    default:
      break;
    }
  }
}

int main() {
  char *numero = (char *)calloc(100, sizeof(char));
  int base;
  printf("\nPermitindo apenas numeros.\nDigite o numero a ser convertido: ");
  setbuf(stdin, NULL);
  gets(numero);
  printf("Digite a base do numero digitado: ");
  scanf("%d", &base);

  convert(numero, base, 2);
  convert(numero, base, 8);
  convert(numero, base, 10);
  convert(numero, base, 16);

  return 0;
}
