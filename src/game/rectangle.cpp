
#include "rectangle.hpp"

void TriangleSet::add_rectangle(float x, float y, float xdelta, float ydelta)
{
	// 添加6个顶点, 两个三角形
	vertexs_.push_back(x);
	vertexs_.push_back(y);
	vertexs_.push_back(x + xdelta);
	vertexs_.push_back(y + ydelta);
	vertexs_.push_back(x);
	vertexs_.push_back(y + ydelta);

	// 第二三角形
	vertexs_.push_back(x);
	vertexs_.push_back(y);
	vertexs_.push_back(x + xdelta);
	vertexs_.push_back(y);
	vertexs_.push_back(x + xdelta);
	vertexs_.push_back(y + ydelta);
}
