#ifndef TASK_H
#define TASK_H

typedef float moment_t;
typedef float cost_t;

struct job_t
{
    moment_t due;
    moment_t proc;
    cost_t tweight;
};


typedef vector<size_t> perm_t;

typedef vector<job_t> task_t;
typedef vector<moment_t> sched_t;


/*struct task_t
{
    task_t (size_t n)
        : n(n)
        , dues(new moment_t[n])
        , procs(new moment_t[n])
        , tweights(new cost_t[n])
    {

    }

    size_t n;

    scoped_array<moment_t>::t dues;
    scoped_array<moment_t>::t procs;
    scoped_array<cost_t>::t tweights;
};

struct sched_t
{
    sched_t (size_t n)
        : n(n)
        , times(new moment_t[n])
    {

    }

    size_t n;
    scoped_array<moment_t>::t times;
};*/

void perm2sched(const task_t &task, const perm_t &perm, sched_t &out);


#endif // TASK_H
