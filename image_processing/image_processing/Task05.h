#pragma once
#include "ITask.h"
class Task05 final :
	public ITask
{
public:
	Task05() = default;
	virtual ~Task05() = default;

	void run() const override;
};

