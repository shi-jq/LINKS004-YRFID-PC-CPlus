#pragma once


class RingBuffer
{
public:
	RingBuffer(int nSize);
	~RingBuffer();
	bool Empty() const;
	bool Full() const;
	unsigned int BytesUsed() const;
	unsigned int BytesFree() const;
	void Clear();
	unsigned int Add(
            const unsigned char*    pBuffer,
            unsigned int          bufferSize
            );
	unsigned int Remove(
            unsigned char*  pBuffer,
            unsigned int  bufferSize
            );
private:
	unsigned char*        m_ring; 
	unsigned int          m_used; 
	unsigned int          m_head;     
	unsigned int          m_tail;   
	unsigned int		   RING_SIZE;
} ;