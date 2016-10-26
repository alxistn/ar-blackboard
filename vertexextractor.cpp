#include "vertexextractor.h"

VertexExtractor::VertexExtractor()
{
_cap.open(0);
}

bool VertexExtractor::updateFrame()
{
    if (_cap.isOpened()){
        _cap >> _frame;
        return true;
    }
    return false;
}

