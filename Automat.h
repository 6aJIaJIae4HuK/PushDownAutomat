#pragma once

#include <string>
#include <map>
#include <stack>
#include <vector>
#include <set>

#include "State.h"
#include "Symbol.h"

class Automat
{
public:
	Automat();
	void loadFromFile(const std::string& fileName);
	bool isAcceptably(const std::string& string);
	void addTranslation(const State& firstState, const Symbol& c, const Symbol& h, const State& secondState, const std::string& chain);
private:
	bool recursive(int index, State state);
	void showChain();
	std::multimap<std::pair<State, std::pair<Symbol, Symbol>>, std::pair<State, std::string>> m_graph;
	std::stack<Symbol> m_stack;
	std::vector<Symbol> m_string;
	std::set<Symbol> m_terminal;
	std::set<Symbol> m_nonTerminal;
	
	std::vector<std::pair<State, std::pair<std::vector<Symbol>, std::stack<Symbol>>>> m_configurationChain;

	Symbol m_initialNonTerminal;
};