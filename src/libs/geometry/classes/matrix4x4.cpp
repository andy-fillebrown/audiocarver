/**************************************************************************
**
** This file is part of AudioCarver
**
** Copyright (c) 2011 Andrew Fillebrown.
**
** Contact: Andy Fillebrown (andy.fillebrown@gmail.com)
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file.  Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
**************************************************************************/

#include "matrix4x4.h"

using namespace Geometry;
using namespace Geometry::Internal;

// The 4x4 matrix inverse algorithm is based on that described at:
// http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q24
// Some optimization has been done to avoid making copies of 3x3
// sub-matrices and to unroll the loops.

// Calculate the determinant of a 3x3 sub-matrix.
//     | A B C |
// M = | D E F |   det(M) = A * (EI - HF) - B * (DI - GF) + C * (DH - GE)
//     | G H I |
static inline real matrixDet3(const Matrix4x4Data &d,
                              int col0, int col1, int col2,
                              int row0, int row1, int row2)
{
    return
        d(col0,row0) *
        (   d(col1,row1) * d(col2,row2) -
            d(col1,row2) * d(col2,row1)
        ) -
        d(col1,row0) *
        (   d(col0,row1) * d(col2,row2) -
            d(col0,row2) * d(col2,row1)
        ) +
        d(col2,row0) *
        (   d(col0,row1) * d(col1,row2) -
            d(col0,row2) * d(col1,row1)
        );
}

// Calculate the determinant of a 4x4 matrix.
static inline qreal matrixDet4(const Matrix4x4Data &d)
{
    qreal det;
    det  = d(0,0) * matrixDet3(d, 1, 2, 3, 1, 2, 3);
    det -= d(1,0) * matrixDet3(d, 0, 2, 3, 1, 2, 3);
    det += d(2,0) * matrixDet3(d, 0, 1, 3, 1, 2, 3);
    det -= d(3,0) * matrixDet3(d, 0, 1, 2, 1, 2, 3);
    return det;
}

real Matrix4x4::determinant() const
{
    return real(matrixDet4(d));
}
