#include "stdafx.h"
#include "task.h"
#include "schedscene.h"
#include "scheditem.h"

struct Marker : QGraphicsItem
{
    Marker() : size(10) {}

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    const int size;
};

QRectF Marker::boundingRect() const
{
    return QRectF (-size, -size, size * 2, size);
}

void Marker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(-size, -size, 0, 0);
    painter->drawLine(0, 0, size, -size);
}


SchedScene::SchedScene(task_t *task, perm_t *perm, sched_t *sched, QObject *parent)
    : QGraphicsScene(parent)
    , task_(task)
    , perm_(perm)
    , sched_(sched)
    , items_(task->size())
    , marker(new Marker)
    , tRect_(NULL)

{
    for (size_t i = 0; i < task->size(); ++i)
    {
        items_[i] = new SchedItem(this, i);
        items_[i]->setPos(sched->operator[](i), 0);

        addItem(items_[i]);
    }

    marker->setPos(0, 0);
    addItem(marker);

    tRect_ = addRect(0, 0, 0, 0);
    tRect_->setPen(QPen(Qt::red, 1));
    tRect_->setBrush(QBrush(Qt::red, Qt::Dense5Pattern));


    updateItems();
}

void SchedScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    /*QPointF point = mouseEvent->scenePos();


    size_t best = 0;
    for (size_t i = 0; i < sched_->n; ++i)
    {
        if (std::abs(sched_->times[i] - point.x()) < std::fabs(sched_->times[best] - point.x()))
            best = i;
    }
    point.setX(sched_->times[best]);
    point.setY(0);
    marker->setPos(point);*/

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void SchedScene::clickItem(size_t id)
{
    if (!selected_.is_initialized())
    {
        selectItem(id);
    }
    else if (*selected_ == id)
    {
        deselectItem();
    }
    else
    {
        swapItems(*selected_, id);
        selectItem(id);
    }
}

void SchedScene::swapItems(size_t i, size_t j)
{
    const size_t job_i = i;//item2job(i);
    const size_t job_j = j;//item2job(j);
    std::swap((*perm_)[job_i], (*perm_)[job_j]);

    items_[i]->updateData();
    items_[j]->updateData();

    updateItems();
}

void SchedScene::selectItem(size_t i)
{
    selected_.reset(i);
    items_[i]->updateData();
}

void SchedScene::deselectItem()
{
    if (selected_.is_initialized())
        items_[*selected_]->updateData();

    selected_.reset();
}

void SchedScene::showTRect(size_t item)
{
    const size_t job = item2job(item);

    moment_t tardiness = (*sched_)[job] - (*task_)[job].due;

    if (tardiness > 0)
    {
        tRect_->setRect((*task_)[job].due, 0, tardiness, (*task_)[job].tweight);
        tRect_->setVisible(true);
    }
    else
        tRect_->setVisible(false);

    //tRect_->update();
}

void SchedScene::hideTRect()
{
    tRect_->setVisible(false);
    //tRect_->update();
}


size_t SchedScene::item2job(size_t item) const
{
    return (*perm_)[item];
}

size_t SchedScene::job2item(size_t job) const
{
    return (std::find(perm_->begin(), perm_->end(), job) - perm_->begin());
}

void SchedScene::updateItems()
{
    perm2sched(*task_, *perm_, *sched_);

    for (size_t i = 0; i < items_.size(); ++i)
        items_[i]->setPos((*sched_)[(*perm_)[i]], 0);

    invalidate();
}

