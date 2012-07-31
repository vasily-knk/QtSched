#include "stdafx.h"
#include "task.h"

void perm2sched(const task_t &task, const perm_t &perm, sched_t &out)
{
    assert (task.size() == perm.size());
    assert (task.size() == out.size());

    moment_t last = 0;
    for (size_t i = 0; i < task.size(); ++i)
    {
        out[perm[i]] = last;
        last += task[perm[i]].proc;
    }
}