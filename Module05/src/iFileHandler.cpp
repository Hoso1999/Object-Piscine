#include "iFileHandler.h"
#include <algorithm>
#include <iostream>
namespace handler
{
	void iFileHandler::strip(std::string& token) const
	{
		auto start = std::find_if_not(token.begin(), token.end(), 
		[](unsigned char c)
		{
			return std::isspace(c);
		});

		// Find the position of the last non-whitespace character
		auto end = std::find_if_not(token.rbegin(), token.rend(), 
		[](unsigned char c)
		{
			return std::isspace(c);
		}).base();

   		// Return the substring without leading and trailing whitespace
   		token = (start < end) ? std::string(start, end) : "";
	}
	std::size_t iFileHandler::closeQuote(const std::string& str, std::size_t openQuotePos) const
	{
		char openQuote = str[openQuotePos];
		char closeQuote;
		switch (openQuote)
		{
			case '\'':
				closeQuote = '\'';
				break;
			case '\"':
				closeQuote = '\"';
				break;
			default:
				return std::string::npos; 
				// Return if it's not an open quote character
		}
		
		for (std::size_t i = openQuotePos + 1; i < str.length(); ++i)
		{
			// Found the position of the close quote
			if (str[i] == closeQuote)
				return i;
		}
		
		// Close quote not found
		return std::string::npos;
	}

	std::vector<std::string> iFileHandler::tokenize(const std::string& str, const std::string& delimiters) const
	{
		std::vector<std::string> tokens;
		std::stringstream ss(str);
		std::string token;
		while (std::getline(ss, token, '\n'))
		{
			// Tokenize by newline first
			std::size_t prev = 0, pos, end = std::string::npos;
			while (true)
			{
				end = std::string::npos;
				pos = token.find_first_of(delimiters, prev);
				if (pos == std::string::npos)
					break;
				if (token[pos] == '\"' || token[pos] == '\'')
					end = closeQuote(token, pos);
				if (end != std::string::npos)
				{
					tokens.push_back(token.substr(pos + 1, end - pos - 1));
					prev += end - pos + 1;
					if (prev >= token.size())
						break;
					continue;
				}
				if (pos > prev)
					tokens.push_back(token.substr(prev, pos - prev));
				prev = pos + 1;
			}
			if (prev < token.length())
				tokens.push_back(token.substr(prev, std::string::npos));
		}
		return tokens;
	}
	bool iFileHandler::isBalancedQuotes(const std::string& str) const
	{
		size_t quoteCounter = 0;
    
		for (char c : str)
		{
			if (c == '"')
				++quoteCounter;
			else if (c == '\'')
			{
				if (quoteCounter % 2)
					continue;
			}
		}
		// If the counter is even, all quotes were balanced
		return quoteCounter % 2 == 0;
	}
} // namespace handler
