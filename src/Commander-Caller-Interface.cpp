#include "Commander-Caller-Interface.hpp"

CommandCaller::CommandCaller(){

}

void CommandCaller::setChannel( Stream* channel_p ){
    channel = channel_p;
}

Stream* CommandCaller::getChannel(){
    return channel;
}

void CommandCaller::clearChannel(){
    channel = NULL;
}



int CommandCaller::available(){

    if( channel == NULL ){
        return -1;
    }

    return channel -> available();

}

int CommandCaller::read(){

    if( channel == NULL ){
        return -1;
    }

	return channel -> read();

}

/// Flush the channel.
void CommandCaller::flush(){
	// Honestly I don't know what to do.
	// Arduino flush methods are weird.
    if( channel == NULL ){
        return;
    }
    channel -> flush();
}

int CommandCaller::peek(){

    if( channel == NULL ){
        return -1;
    }
    return channel -> peek();

}

size_t CommandCaller::write( uint8_t data ){
    if( channel == NULL ){
        return -1;
    }
    return channel -> write( data );
}

size_t CommandCaller::write( const uint8_t *data, size_t size ){
    if( channel == NULL ){
        return -1;
    }
    return channel -> write( data, size );
}
