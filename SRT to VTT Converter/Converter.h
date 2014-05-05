#ifndef CONVERTER_H_
#define CONVERTER_H_

class Converter
{
public:
	Converter(int timeOffsetMs = 0);
	~Converter();

private:
	int _timeOffsetMs;
};

#endif