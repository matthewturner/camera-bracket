#ifndef IStreamReader_h
#define IStreamReader_h

class IStreamReader
{
public:
    virtual bool available() = 0;
    virtual int read() = 0;
};

#endif