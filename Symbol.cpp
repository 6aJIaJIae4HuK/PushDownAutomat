#include "Symbol.h"

Symbol::Symbol() : m_char(0), m_isEmpty(false), m_isBottom(false)
{

}

Symbol::Symbol(char c, bool empty, bool bottom) : m_char(c), m_isEmpty(empty), m_isBottom(bottom)
{

}

char Symbol::getChar() const
{
	return m_char;
}

bool Symbol::isEmpty() const
{
	return m_isEmpty;
}

bool Symbol::isBottom() const
{
	return m_isBottom;
}

bool Symbol::operator<(const Symbol& symbol) const
{
	if (getChar() != symbol.getChar())
		return getChar() < symbol.getChar();
	if (isEmpty() != symbol.isEmpty())
		return isEmpty();
	if (isBottom() != symbol.isBottom())
		return isBottom();
	return false;
}

bool Symbol::operator==(const Symbol& symbol) const
{
	if (getChar() != symbol.getChar())
	{
		if (!(isEmpty() ^ symbol.isEmpty()) && !(isBottom() ^ symbol.isBottom()))
			return true;
		else
			return false;
	}
	else
	{
		return true;
	}
}