#include "pch.h"
#include "byte_reader.h"

char				byte_reader::read_int8() {
	buffer_position++;
	return *(buffer_pointer + buffer_position - 1);
}
unsigned char		byte_reader::read_uint8() {
	buffer_position++;
	return *(buffer_pointer + buffer_position - 1);
}
short				byte_reader::read_int16() {
	buffer_position += 2;
	return *(short*)(buffer_pointer + buffer_position - 2);
}
unsigned short		byte_reader::read_uint16() {
	buffer_position += 2;
	return *(unsigned short*)(buffer_pointer + buffer_position - 2);
}
int					byte_reader::read_int32() {
	buffer_position += 4;
	return *(int*)(buffer_pointer + buffer_position - 4);
}
unsigned int		byte_reader::read_uint32() {
	buffer_position += 4;
	return *(unsigned int*)(buffer_pointer + buffer_position - 4);
}
float				byte_reader::read_float() {
	buffer_position += 4;
	return *(float*)(buffer_pointer + buffer_position - 4);
}
__int64				byte_reader::read_int64() {
	buffer_position += 8;
	return *(__int64*)(buffer_pointer + buffer_position - 8);
}
unsigned __int64	byte_reader::read_uint64() {
	buffer_position += 8;
	return *(unsigned __int64*)(buffer_pointer + buffer_position - 8);
}
double				byte_reader::read_double() {
	buffer_position += 8;
	return *(double*)(buffer_pointer + buffer_position - 8);
}
void*				byte_reader::read_text() {
	size_t strLength = strlen((char*)(buffer_pointer + buffer_position));
	void* retString = malloc(strLength + 1);
	memcpy(retString, buffer_pointer + buffer_position, strLength);
	*((char*)retString + strLength) = 0;
	buffer_position += strLength + 1;
	return retString;
}
void*				byte_reader::read_buffer(__int64 size) {
	buffer_position += size;
	return buffer_pointer + buffer_position - size;
}

byte_reader::byte_reader(void* pointer, __int64 size, __int64 position) {
	buffer_pointer = (unsigned char*)pointer;
	buffer_size = size;
	buffer_position = position;
}