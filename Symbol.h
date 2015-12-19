#pragma once

class Symbol
{
public:
	Symbol();
	Symbol(char c, bool empty = false, bool bottom = false);
	char getChar() const;
	bool isEmpty() const;
	bool isBottom() const;
	bool operator<(const Symbol& state) const;
	bool operator==(const Symbol& state) const;
private:
	char m_char;
	bool m_isEmpty;
	bool m_isBottom;
};