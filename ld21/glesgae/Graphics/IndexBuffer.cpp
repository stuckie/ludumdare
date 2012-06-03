#include "IndexBuffer.h"

#include <cstring> // for memcpy
#if defined(GLX)
	#include "GLee.h"
#elif defined(GLES1)
	#if defined(PANDORA)
		#include <GLES/gl.h>
	#endif
#elif defined(GLES2)
	#if defined(PANDORA)
		#include <GLES2/gl2.h>
	#endif
#endif

using namespace GLESGAE;

IndexBuffer::IndexBuffer(unsigned char* const data, const unsigned int size, const FormatType format)
: mData(new unsigned char[size])
, mSize(size)
, mVboId(0U)
, mFormat(format)
{
	std::memcpy(mData, data, size);
	
	glGenBuffers(1U, &mVboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSize, mData, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(const IndexBuffer& indexBuffer)
: mData(indexBuffer.mData)
, mSize(indexBuffer.mSize)
, mVboId(indexBuffer.mVboId)
, mFormat(indexBuffer.mFormat)
{
}
