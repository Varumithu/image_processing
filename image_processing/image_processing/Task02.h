#pragma once
#include "ITask.h"
class Task02 final :
	public ITask
{
public:
	Task02() = default;
	virtual ~Task02() = default;
	void run() const override;
};

