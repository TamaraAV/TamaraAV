#include "Shablon.h"
int Crypt(const char* arr1, const char* arr2, char* input, char* output)
{
	int i;
	while (*input)
	{
		for (i = 0; i < strlen(arr1); i++)
		{
			if (*input == arr1[i])
			{
				*output = arr2[i];
				break;
			}
		}
		if (i == strlen(arr1))
		{
			*output = *input;
		}
		output++;
		input++;
	}
	*output = 0;
		return 0;
}
