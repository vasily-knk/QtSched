#ifndef STDAFX_H
#define STDAFX_H

#include <cmath>
#include <QtGui>

#include <boost/scoped_array.hpp>

template <typename T>
struct scoped_array
{
    typedef boost::scoped_array<T> t;
};

#include <vector>
using std::vector;

#include <boost/optional.hpp>
using boost::optional;


#include "task.h"

#endif // STDAFX_H
