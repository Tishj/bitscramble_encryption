/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitscramble.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/23 00:08:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/23 12:37:34 by tbruinem      ########   odam.nl         */
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

	for (size_t i = 0; i < message.size(); i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			output[((i * 4) + (j / 2) * (4 + spread)) % output.size()] = output[((i * 4) + (j / 2) * (4 + spread)) % output.size()] * 2 + ((message[i] >> (7 - j)) & 1);
			if (j % 2 == 1)
				output[((i * 4) + (j / 2) * (4 + spread)) % output.size()] = charset[output[((i * 4) + (j / 2) * (4 + spread)) % output.size()]];
		}
		
	}
	return (output);
}

std::string decode(std::string message, std::string charset = "CODE")
{
	std::string output(message.size() / 4, '\0');
	size_t spread = output.size() / 4;
	char encoded;

	for (size_t i = 0; i < output.size(); i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (j % 2 == 0)
				encoded = (char)charset.find(message[((i * 4) + ((j / 2) * (4 + spread))) % message.size()]);
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
