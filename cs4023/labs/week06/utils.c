int approxEqual(float input, float compare, float range)
{
	return (compare - range <= input && input <= compare + range);
}

char flipChar(char input)
{
	if ('a' <= input && input <= 'z')
	{
		input = 'z' - input;
		return 'a' + input;
	}
	else if ('A' <= input && input <= 'Z')
	{
		input = 'Z' - input;
		return 'A' + input;
	}
	else if ('0' <= input && input <= '9')
	{
		input = '9' - input;
		return '0' + input;
	}
}
