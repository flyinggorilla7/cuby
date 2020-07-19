//ili9341 driver header file


void ili9341_init();

void ili9341_write_data(unsigned int data);

void ili9341_write_command(unsigned int command);

//used for sending multiple data bytes on the same frame
void ili9341_write_bytes(unsigned int data);
