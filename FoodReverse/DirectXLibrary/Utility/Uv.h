#ifndef UV_H
#define UV_H

namespace Utility
{
	class Uv
	{
	public:
		Uv(float Tu, float Tv, float TuSize, float TvSize) : tu(Tu), tv(tv), tu_size(TuSize), tv_size(TvSize) {}

		float tu;
		float tv;
		float tu_size;
		float tv_size;
	};
}

#endif
