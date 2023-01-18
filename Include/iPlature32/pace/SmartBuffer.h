#ifndef __PACE_SMART_BUFFER__
#define __PACE_SMART_BUFFER__

#include <vector>
#include <string>
#include <exception>
#include <IceUtil/IceUtil.h>
#include <pace/SmartData.h>
#include <string.h>

namespace iPlature
{
/**
 *
 *
 */
class SmartBufferException : public std::exception
{
public:
    virtual ~SmartBufferException() throw();
    SmartBufferException(const std::string& msg);
    SmartBufferException(const int pos,
                         const int length,
                         const std::string& msg);
    virtual const char* what() const throw();
private:   
    std::string  _what;
};

class SmartBuffer : IceUtil::noncopyable
{
public:
   /**
    * construct a SmartBuffer instance and create a 
    * buffer which size is length,the buffer will be
    * freed by the SmartBuffer before the SmartBuffer
    * instance is destroyed.
    * @param length the buffer size to be allocated.
    *
    */
   SmartBuffer();
   explicit SmartBuffer(const unsigned int length);
   explicit SmartBuffer(const std::vector<unsigned char>& msg);
   explicit SmartBuffer(std::vector<unsigned char>& msg);
   /**
    * construct a SmartBuffer instance and associate 
    * the internal buffer with the given buffer.
    * @warn in this case SmartBuffer do not own the buffer,
    *       and cann't control the buffer's life cycle.Thus
    *       the SmartBuffer will never free the buffer.
    * @param buffer the given buffer pointer.
    * @param length the given buffer size.
    */
   SmartBuffer(void* buffer,const unsigned int length);

   virtual ~SmartBuffer();
   /**
    * @return the internal buffer.
    */
   void* buffer() const;
   const std::vector<unsigned char>& vBuffer() const;
   /**
    * @return the internal buffer size.
    */
   int size() const;

   /**
    *  read fixed-size types,such as:
    *  char,unsigned char,
    *  short,unsigned short,
    *  int,unsigned int,
    *  long,unsigned long,
    *  float,double
    *  @return SmartBuffer
    */  
   template <typename T>
   SmartBuffer& read(T& v)
   {
      if(_pos + sizeof(T) <= _len)
      {
        memcpy(&v,
               _buffer + _pos,
               sizeof(T)); 
        _pos += sizeof(T);
      }
      else
      {
         throw SmartBufferException(_pos,_len,"read");
      }
      return *this;
   }

   
   /**
    *
    *
    *  @return SmartBuffer
    */
   SmartBuffer& read(SmartData& rhs);
   
   /**
    *
    *
    *  @return SmartBuffer
    */
   SmartBuffer& write(SmartData& rhs);
   /**
    *  write fixed-size types,such as:
    *  char,unsigned char,
    *  short,unsigned short,
    *  int,unsigned int,
    *  long,unsigned long,
    *  float,double
    *  @return SmartBuffer
    */  
   template <typename T>
   SmartBuffer& write(const T& v)
   {
      if(_auto)
      {
         char* c = reinterpret_cast<char*>(const_cast<T*>(&v));
         for(int i = 0; i < sizeof(T); i++)
         {
            _vBuffer.push_back(*c++);
         }   
         _len = _vBuffer.size();
         _buffer = &(_vBuffer.front());
         return *this;
      }

      if((! _readonly) && (_pos + sizeof(T) <= _len))
      {
        memcpy(_buffer +_pos,&v,sizeof(T)); 
        _pos += sizeof(T);
      }
      else
      {
         throw SmartBufferException(_pos,_len,"write");
      }
      return *this;
   }
   /**
    * read a bunch of value into a stl container.
    * @note the Container::value_type must be fixed-size basic type.
    * @param Container a stl sequence container,like
    *        vector,list,queue,dequeue,etc.
    * @param count read count size of elements into the container.
    * @return the SmartBuffer
    */
   template <typename Container>
   SmartBuffer& readSequence(Container& c,int count )
   {
      if(!c.empty())
      {
         c.clear();
      }
      typename Container::value_type v;
      for(int i=0;i<count;i++)
      {
         this->read(v);
         c.insert(c.end(),v);
      }
      return *this;
   }

   /**
    * write a bunch of value into a stl container.
    * @note the Container::value_type must be fixed-size basic type.
    * @param Container a stl sequence container,like
    *        vector,list,queue,dequeue,etc.
    * @return the SmartBuffer
    */
   template <typename Container>
   SmartBuffer& writeSequence(Container& c)
   {
      if(!_readonly)
      {
         for(typename Container::const_iterator i = c.begin();
             i!= c.end();
             i++)
         {
            this->write(*i);
         }
      }
      else
      {
         throw SmartBufferException("writeSequence not permitted in this smart buffer");
      }
      return *this;
   }
   /**
    * read a string from buffer.
    * @param str the string container.
    * @param length read string length
    * @return the SmartBuffer
    */
   SmartBuffer& readString(std::string& dest,int length);
   SmartBuffer& readCString(char* dest,int length);
   /**
    * write a string into buffer.
    * @param str the string to be writen.
    * @param terminator if or not write a 
    *        c stype string terminator:'\0',default false.
    * @return SmartBuffer
    */
   SmartBuffer& writeString(const std::string& str,bool terminator=false);
   SmartBuffer& writeCString(const char* src,bool terminator=false);

   /**
    * move the read point of the buffer forward size bytes.
    * @param bytes the count of bytes to be skiped.
    * @return SmartBuffer
    */
   SmartBuffer& skip(int bytes);
   /**
    * move the current read/write offset to the given position.
    * @param pos the position move to.
    * @return SmartBuffer
    */
   SmartBuffer& seek(int pos);
   /**
    * @return the current read/write offset point of the buffer.
    */
   int where() const;
private:
   void check(const std::string& msg);
   std::vector<unsigned char> _vBuffer;
   unsigned char* _buffer;
   int _len;
   int _pos;
   bool _readonly;
   bool _auto;
};

//specialization for std::string
template <>
SmartBuffer& SmartBuffer::read(std::string& v);
//specialization for std::string
template <>
SmartBuffer& SmartBuffer::write(const std::string& v);

}//namespace pace

#endif



