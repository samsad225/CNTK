#include "stdafx.h"
#include "Matrix.h"
#include "MatrixQuantizer.h"
#include "MatrixQuantizerCPU.h"
#include "MatrixQuantizerGPU.h"

namespace Microsoft { namespace MSR { namespace CNTK {
    
    template<class ElemType>
    /*static*/ MatrixQuantizer<ElemType>*
    MatrixQuantizer<ElemType>::CreateMatrixQuantizer(const Matrix<ElemType>& inMatrix)
    {
        if (inMatrix.GetDeviceId() >= 0)
        {
            return new MatrixQuantizerGPU<ElemType>(inMatrix);
        }
        else
        {
            return new MatrixQuantizerCPU<ElemType>(inMatrix);
        }
    }

    template<class ElemType>
    MatrixQuantizer<ElemType>::MatrixQuantizer(const Matrix<ElemType>& inMatrix)
    : m_inMatrix(inMatrix)
    {
        m_residual = new Matrix<ElemType>(inMatrix.GetNumRows(), inMatrix.GetNumCols(), inMatrix.GetDeviceId(), DENSE);
    }

    template<class ElemType>
    MatrixQuantizer<ElemType>::~MatrixQuantizer()
    {
        if (nullptr != m_residual)
        {
            delete m_residual;
            m_residual = nullptr;
        }    
    }

    template class MatrixQuantizer<float>;
    template class MatrixQuantizer<double>;
    
}}}
