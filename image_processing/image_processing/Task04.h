#pragma once
#include "ITask.h"
class Task04 final:
	public ITask
{
public:
	Task04() = default;
	virtual ~Task04() = default;
	void run() const override;
};

