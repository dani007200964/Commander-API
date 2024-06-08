/*
 * Created on June 18 2020
 *
 * Copyright (c) 2020 - Daniel Hajnal
 * hajnal.daniel96@gmail.com
 * This file is part of the Commander-API project.
 * Modified 2022.02.06
*/

/*
MIT License

Copyright (c) 2020 Daniel Hajnal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __COMMANDER_CALLER_INTERFACE_HPP__
#define __COMMANDER_CALLER_INTERFACE_HPP__

#include "Stream.h"

class CommandCaller : public Stream{

public:
    CommandCaller();

    /// Available bytes in the channel.
    ///
    /// @returns The available bytes in the channel.
    int available() override;

    /// Read one byte form the channel.
    ///
    /// @returns Read and return one byte form the channel. The byte will be removed from the channel.
	int read() override;

    /// Peek the firtst byte from the channel.
    ///
    /// @returns Read and return one byte form the channel. The byte will NOT be removed from the channel.
	int peek() override;

    /// Flush the channel.
	void flush() override;

    /// Write one byte to the channel.
    ///
    /// @param b The value that has to be written to the channel.
    /// @returns The number of bytes that has been successfully written to the channel. Because it is the base class, it returns 0.
	size_t write( uint8_t b ) override;

	size_t write( const uint8_t *buffer, size_t size ) override;

    void setChannel( Stream* channel_p );
    Stream* getChannel();
    void clearChannel();

    virtual void beep(){}
    virtual void setBannerText( const char* text_p ){}
    virtual void setPathText( const char* text_p ){}
    virtual void clear( const char* text_p ){}

private:
    Stream* channel = NULL;

};

#endif