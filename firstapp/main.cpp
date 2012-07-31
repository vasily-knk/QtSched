#include "stdafx.h"
#include "schedscene.h"
#include "scheditem.h"



int main(int argc, char *argv[])
{
    const size_t N = 7;
    task_t task(N);
    perm_t perm(N);
    sched_t sched(N);

    for (size_t i = 0; i < N; ++i)
    {
        task[i].spans.resize(N);
        std::fill(task[i].spans.begin(), task[i].spans.end(), 60);

        //task[i].proc = 60;//(i + 1) * 40;
        task[i].tweight = (i + 1) * 20;
        task[i].due = 0;

        perm[i] = i;
    }
    std::swap(perm[0], perm[1]);


    QApplication app(argc, argv);

    SchedScene scene(&task, &perm, &sched);


    QGraphicsView view(&scene);
    view.setMouseTracking(true);

    view.show();
    view.setWindowTitle("My first app");

    return app.exec();
}


