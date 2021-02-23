/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitscramble.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 00:08:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/23 20:23:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

std::string encode(std::string message, std::string charset = "CODE")
{
	std::string output(message.size() * 4, '\0');
	size_t spread = message.size() / 4;
	if (spread % 2 == 0)
		spread++;

	for (size_t i = 0; i < message.size(); i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			size_t index = ((i * 4) + (j / 2) * (4 + spread)) % output.size();
			output[index] = output[index] * 2 + ((message[i] >> (7 - j)) & 1);
			if (j % 2 == 1)
				output[index] = charset[output[index]];
		}
	}
	return (output);
}

std::string decode(std::string message, std::string charset = "CODE")
{
	std::string output(message.size() / 4, '\0');
	size_t spread = output.size() / 4;
	if (spread % 2 == 0)
		spread++;
	char encoded;

	for (size_t i = 0; i < output.size(); i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (j % 2 == 0)
			{
				size_t index = ((i * 4) + (j / 2) * (4 + spread)) % message.size();
				encoded = (char)charset.find(message[index]);
			}
			output[i] = output[i] * 2 + ((encoded >> (1 - (j % 2))) & 1);
		}
	}
	return (output);
}

int main(int argc, char **argv)
{
	bool decode_flag = false;

	if (argc == 1)
		return (!!printf("Error: please provide atleast one argument\n"));
	for (size_t i = 1; i < argc; i++)
		if (string(argv[1]) == "-d")
			decode_flag = true;

	string output;
	if (decode_flag)
		output = decode(argv[2]);
	else
		output = encode(argv[1]);
	cout << output << endl;
	return (0);
}
