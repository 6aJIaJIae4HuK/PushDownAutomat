#include "State.h"

State::State(int num, bool start, bool finish) : m_num(num), m_isStart(start), m_isFinish(finish)
{

}

int State::getNum() const
{
	return m_num;
}

bool State::isStart() const
{
	return m_isStart;
}

bool State::isFinish() const
{
	return m_isFinish;
}

bool State::operator<(const State& state) const
{
	if (getNum() != state.getNum())
		return getNum() < state.getNum();
	if (isStart() != state.isStart())
		return isStart();
	if (isFinish() != state.isFinish())
		return isFinish();
	return false;
}
