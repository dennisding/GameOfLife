
#include "rectangle.hpp"

void TriangleSet::add_rectangle(float x, float y, float xdelta, float ydelta)
{
	// ���6������, ����������
	vertexs_.push_back(x);
	vertexs_.push_back(y);
	vertexs_.push_back(x + xdelta);
	vertexs_.push_back(y + ydelta);
	vertexs_.push_back(x);
	vertexs_.push_back(y + ydelta);

	// �ڶ�������
	vertexs_.push_back(x);
	vertexs_.push_back(y);
	vertexs_.push_back(x + xdelta);
	vertexs_.push_back(y);
	vertexs_.push_back(x + xdelta);
	vertexs_.push_back(y + ydelta);
}
