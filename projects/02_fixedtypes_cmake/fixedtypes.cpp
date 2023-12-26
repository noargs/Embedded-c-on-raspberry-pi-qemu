#include <iostream>

void SendDataToDevice(void* buffer, uint32_t size)
{
	// send data pointer by buffer
	std::cout << "Sending data chunk of size " << size << std::endl;
}

int main()
{
	char buffer[] = "Hello, world!";
	uint32_t size = sizeof(buffer);
	SendDataToDevice(&size, size);
	SendDataToDevice(buffer, size);
	return 0;
}