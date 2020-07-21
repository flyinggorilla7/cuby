//ili9341 driver header file


void ili9341_init();

void ili9341_write_data(unsigned int data);

void ili9341_write_command(unsigned int command);

//used for sending multiple data bytes on the same frame
void ili9341_write_bytes(unsigned int data);
//Sets active columns to write memory to
void ili9341_set_columns(unsigned int start, unsigned int end);

//Sets active rows to write memory to
void ili9341_set_rows(unsigned int start, unsigned int end);

//Draw Outline of square to current row and column selection
void ili9341_outline_square();
