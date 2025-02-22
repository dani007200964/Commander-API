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

#include "Commander-Autocomplete.hpp"

const char AutoComplete::empty_result = '\0';


AutoComplete::AutoComplete(TrieElement_t *trie_p){
    int i;
    trie = trie_p;
    for( i = 0; i < AUTOCOMPLETE_RESULT_SIZE; i++ ){
        result_pointers[ i ] = &empty_result;
    }
}

void AutoComplete::searchRecursive(int current_index, char *key, int key_size ){

    int i;
    int search_index;
    char search_char;

    //wprintf( L"current_index: %d\r\n", current_index );
    //wprintf( L"key: %.*s\r\n", key_size, key );

    // Check if we ran out of buffer memory. If so,
    // it is pointless to do anything else.
    if( result_buffer_counter >= buffer_size ){
        return;
    }

    if( result_counter >= AUTOCOMPLETE_RESULT_SIZE ){
        // Check if we has any result pointers left
        return;
    }

    // We have to check if we found a word_end.
    // If so, we have to copy all data from the working part
    // of the buffer to the next result part.
    if( trie[ current_index ].word_end ){

        for( i = 0; i < key_size; i++ ){
            buffer[ result_buffer_counter ] = key[ i ];
            result_buffer_counter++;

            if( result_buffer_counter >= buffer_size ){
                result_counter--;
                return;
            }
        }

        // Terminate the result string.
        buffer[ result_buffer_counter ] = '\0';
        result_buffer_counter++;

        if( result_buffer_counter >= buffer_size ){
            return;
        }

        result_counter++;
        if( result_counter >= AUTOCOMPLETE_RESULT_SIZE ){
            // Check if we has any result pointers left
            return;
        }
        result_pointers[ result_counter ] = &buffer[ result_buffer_counter ];

    }


    for( i = 0; i < trie[ current_index ].num_of_childs; i++ ){
        search_index = trie[ current_index ].child_indexes[ i ];
        search_char = trie[ search_index ].c;
        if( key_size >= work_buffer_size ){
            continue;
        }
        key[ key_size ] = search_char;
        searchRecursive( search_index, key, key_size + 1 );
    }

}

int AutoComplete::searchLastMatchingNode( const char* key ){

    int i;
    int next_index;
    int current_index = 0;
    int search_index;
    int search_char;

    if( *key == '\0' ){
        return -1;
    }

    while( true ){

        next_index = -1;
        for( i = 0; i < trie[ current_index ].num_of_childs; i++ ){

            search_index = trie[ current_index ].child_indexes[ i ];
            search_char = trie[ search_index ].c;

            if( *key == search_char ){
                next_index = search_index;
                break;
            }

        }

        if( next_index < 0 ){
            return -1;
        }

        key++;
        if( *key == '\0' ){
            return next_index;
        }

        current_index = next_index;

    }

    return -1;

}

int AutoComplete::generateHint( const char *key_p, char *buffer_p, int buffer_size_p ){
    int last_index;

    buffer = buffer_p;
    buffer_size = buffer_size_p;
    
    work_buffer_size  = buffer_size / 3;
    result_buffer_start = work_buffer_size + 1;
    result_buffer_counter = result_buffer_start;

    result_counter = 0;
    result_pointers[ result_counter ] = &buffer[ result_buffer_start ];

    last_index = searchLastMatchingNode( key_p );
    if( last_index < 0 ){
        return 0;
    }

    strncpy( buffer, key_p, work_buffer_size - 1 );
    buffer[ work_buffer_size - 1 ] = '\0';

    input_data_size = strlen( buffer );

    //wprintf( L"buffer: %s\r\n", buffer );
    //wprintf( L"last_index: %d\r\n", last_index );

    searchRecursive( last_index, buffer, strlen( buffer ) );

    if( result_counter < 0 ){
        result_counter = 0;
    }

    return result_counter;
}

const char* AutoComplete::getResult( int index, bool only_remaining_chars ){
    int offset = 0;

    if( index >= result_counter ){
        return &empty_result;
    }

    if( only_remaining_chars ){
        offset = input_data_size;
    }

    return result_pointers[ index ] + offset;
}

