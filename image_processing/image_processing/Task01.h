#pragma once
#include "ITask.h"
class Task01 final :
	public ITask
{
public:
	Task01() = default;
	virtual ~Task01() = default;
	void run() const override;
};

