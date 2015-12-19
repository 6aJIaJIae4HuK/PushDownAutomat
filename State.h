#pragma once

class State
{
public:
	State(int num, bool start, bool finish);
	int getNum() const;
	bool isStart() const;
	bool isFinish() const;
	bool operator<(const State& state) const;
private:
	int m_num;
	bool m_isStart;
	bool m_isFinish;
};