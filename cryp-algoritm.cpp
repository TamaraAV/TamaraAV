#include "Crypt-Algorithms.h"

int RowColumn(char* input, char* output)
{
	int i, j;
	while (strlen(input) % 9 != 0) {
		strcat(input, " ");
	}
	*(input + strlen(input) - 1) = '\0';
	while (*input)
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				*output = *(input + j * 3);
				output++;
			}
			input++;
		}
		input += 6;
	}


	return 0;
}

std::string RLE_enc(std::string str)
{
    std::string encoding = "";
    int count;
    for (int i = 0; str[i]; i++)
    {
        count = 0;
        while (str[i] == str[i + 1]) {
            count++, i++;
        }
        if (count) encoding += "|" + std::to_string(count + 1);
        encoding += str[i];
    }

    return encoding;
}

std::string RLE_dec(std::string str)
{
    std::string decoding = "";
    int count, i = 0;
    while (str[i])
    {
        if (str[i] == '|')
        {
            count = int(str[i + 1] - '1');
            for (int j = 0; j < count; j++) decoding += str[i + 2];
            i += 2;
        }
        else
        {
            decoding += str[i];
            i++;
        }

    }
    return decoding;
}

int Shablon(const char* arr1, const char* arr2, char* input, char* output) {
	int i;
	while (*input)
	{
		for (i = 0; i <= strlen(arr1); i++)
		{

			if (*input == arr1[i])
			{
				*output = arr2[i];
				break;
			}
			else { *output = *input; }
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
