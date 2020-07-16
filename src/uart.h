//UART header file

void uart_init();

void printString(char * string);

void printChar(char alpha);

void write_uart(unsigned int data);

void uart_print32(unsigned int number);

void uart_reverse32(char s[], int length);

void uart_print32_hex(unsigned int number);
