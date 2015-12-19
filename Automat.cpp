#include "Automat.h"

#include <fstream>
#include <iostream>

Automat::Automat()
{

}

void Automat::loadFromFile(const std::string& fileName)
{
	m_terminal.clear();
	m_nonTerminal.clear();
	m_graph.clear();

	std::ifstream input(fileName);

	std::string line;
	State state(0, true, true);
	std::string left;
	std::string right;
	int pos = -1;
	bool first = true;
	while (std::getline(input, line))
	{
		pos = line.find('>');
		if (pos == std::string::npos)
			throw std::exception("Incorrect line");
		left = line.substr(0, line.find('>'));
		right = line.substr(line.find('>') + 1);

		if (left.size() != 1 || !(left[0] >= 'A' && left[0] <= 'Z'))
			throw std::exception("Incorrect left part!");
		
		if (first)
		{
			m_initialNonTerminal = left[0];
		}

		m_nonTerminal.insert(left[0]);
		
		auto l = right.begin();
		for (auto it = right.begin(); it != right.end(); it++)
		{
			if (*it >= 'A' && *it <= 'Z')
			{
				m_nonTerminal.insert(Symbol(*it));
			}
			else
			if (*it == '|')
			{
				addTranslation(state, Symbol(0, true, false), left[0], state, std::string(l, it));
				l = it;
				l++;
			}
			else
			{
				m_terminal.insert(Symbol(*it));
			}
		}
		addTranslation(state, Symbol(0, true, false), left[0], state, std::string(l, right.end()));
		first = false;
	}
	for (auto it = m_terminal.begin(); it != m_terminal.end(); it++)
	{
		addTranslation(state, Symbol(*it), Symbol(*it), state, "");
	}
	addTranslation(state, Symbol(0, true, false), Symbol(0, false, true), state, "");
}

void Automat::addTranslation(const State& firstState, const Symbol& c, const Symbol& h, const State& secondState, const std::string& chain)
{
	m_graph.insert(std::make_pair(std::make_pair(firstState, std::make_pair(c, h)), std::make_pair(secondState, chain)));
}

bool Automat::isAcceptably(const std::string& string)
{
	m_string.clear();
	m_configurationChain.clear();
	while (!m_stack.empty())
		m_stack.pop();

	for (auto it = string.begin(); it != string.end(); it++)
	{
		m_string.push_back(Symbol(*it));
	}

	m_stack.push(Symbol(0, false, true));
	m_stack.push(m_initialNonTerminal);

	bool res = recursive(0, State(0, true, true));
	if (res)
	{
		std::reverse(m_configurationChain.begin(), m_configurationChain.end());
		showChain();
	}
	else
	{
		std::cout << "NonAcceptable" << std::endl;
	}
	return res;
}

bool Automat::recursive(int index, State state)
{
	bool res = false;
	if (index < m_string.size() && !m_stack.empty())
	{
		auto ints = m_graph.equal_range(std::make_pair(state, std::make_pair(m_string[index], m_stack.top())));
		if (ints.first != ints.second)
		{
			m_stack.pop();
			for (auto it = ints.first; it != ints.second && !res; it++)
			{
				for (auto it1 = it->second.second.rbegin(); it1 != it->second.second.rend(); it1++)
				{
					m_stack.push(Symbol(*it1));
				}

				res = res || recursive(index + 1, it->second.first);

				for (auto it1 = it->second.second.rbegin(); it1 != it->second.second.rend(); it1++)
				{
					m_stack.pop();
				}
				if (res)
				{
					m_configurationChain.push_back(std::make_pair(state, std::make_pair(std::vector<Symbol>(), m_stack)));
					for (int i = index; i < m_string.size(); i++)
						m_configurationChain.back().second.first.push_back(m_string[i]);
				}
			}

			m_stack.push(ints.first->first.second.second);
		}
		
		ints = m_graph.equal_range(std::make_pair(state, std::make_pair(Symbol(0, true), m_stack.top())));
		if (ints.first != ints.second)
		{
			m_stack.pop();
			for (auto it = ints.first; it != ints.second && !res; it++)
			{
				for (auto it1 = it->second.second.rbegin(); it1 != it->second.second.rend(); it1++)
				{
					m_stack.push(Symbol(*it1));
				}

				res = res || recursive(index, it->second.first);
				
				for (auto it1 = it->second.second.rbegin(); it1 != it->second.second.rend(); it1++)
				{
					m_stack.pop();
				}
				if (res)
				{
					m_configurationChain.push_back(std::make_pair(state, std::make_pair(std::vector<Symbol>(), m_stack)));
					for (int i = index; i < m_string.size(); i++)
						m_configurationChain.back().second.first.push_back(m_string[i]);

				}
			}

			m_stack.push(ints.first->first.second.second);
		}
	}
	else
	{
		if (!m_stack.empty() && m_stack.top() == Symbol(0, false, true))
		{
			m_configurationChain.push_back(std::make_pair(state, std::make_pair(std::vector<Symbol>(), m_stack)));
			return true;
		}
		else
			return false;
	}
	return res;
}

void Automat::showChain()
{
	for (auto it = m_configurationChain.begin(); it != m_configurationChain.end(); it++)
	{
		std::cout << "(s" << it->first.getNum() << ", ";
		for (auto it1 = it->second.first.begin(); it1 != it->second.first.end(); it1++)
			std::cout << it1->getChar();
		std::cout << ", ";
		while (!it->second.second.empty())
		{
			std::cout << it->second.second.top().getChar();
			it->second.second.pop();
		}
		std::cout << ")" << std::endl;
	}
}