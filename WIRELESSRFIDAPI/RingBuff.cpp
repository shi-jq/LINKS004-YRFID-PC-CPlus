#include "StdAfx.h"
#include "RingBuff.h"
#include <assert.h>

RingBuffer::RingBuffer(int nSize):
	m_used(0),
	m_head(0),
	m_tail(0)
{
	RING_SIZE = nSize;
	m_ring = new unsigned char[RING_SIZE];
}

RingBuffer::~RingBuffer()
{
	if (m_ring)
	{
		delete[] m_ring;
		m_ring = NULL;
	}
}

bool RingBuffer::Empty() const
{
	return m_used == 0;		
}

bool RingBuffer::Full() const
{
	return m_used == RING_SIZE;
}

unsigned int RingBuffer::BytesFree() const
{
	return RING_SIZE - m_used;
}

void RingBuffer::Clear()
{
	m_head = m_tail = m_used = 0;
}

unsigned int RingBuffer::Add(const unsigned char* pBuffer, unsigned int bufferSize)
{
	assert(bufferSize <= this->BytesFree());


	if ((m_tail + bufferSize) > RING_SIZE)
	{

		unsigned int  appendSize = RING_SIZE - m_tail;
		memcpy(m_ring + m_tail, pBuffer, appendSize);

		unsigned int  prependSize = bufferSize - appendSize;
		memcpy(m_ring, pBuffer + appendSize, prependSize);
	}
	else
	{

		memcpy(m_ring + m_tail, pBuffer, bufferSize);
	}

	m_used += bufferSize;
	m_tail = (m_tail + bufferSize) % RING_SIZE;

	return this->BytesFree();
}

unsigned int RingBuffer::Remove(unsigned char* pBuffer, unsigned int bufferSize)
{
	assert(bufferSize <= this->BytesUsed());

	if ((m_head + bufferSize) > RING_SIZE)
	{

		unsigned int  firstCopy = RING_SIZE - m_head;
		memcpy(pBuffer, m_ring + m_head, firstCopy);

		unsigned int  secondCopy = bufferSize - firstCopy;
		memcpy(pBuffer + firstCopy, m_ring, secondCopy);
	}
	else
	{

		memcpy(pBuffer, m_ring + m_head, bufferSize);
	}

	m_used -= bufferSize;
	m_head = (m_head + bufferSize) % RING_SIZE;

	return this->BytesUsed();
}

unsigned int RingBuffer::BytesUsed() const
{
	return m_used;
}




