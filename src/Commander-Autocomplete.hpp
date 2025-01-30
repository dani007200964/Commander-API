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

#ifndef __COMMANDER_AUTOCOMPLETE_HPP__
#define __COMMANDER_AUTOCOMPLETE_HPP__

#include <stdint.h>
#include <string.h>

/*
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
*/

#define AUTOCOMPLETE_RESULT_SIZE    10

class AutoComplete{

public:

	typedef struct{
        char c;
        uint8_t word_end;
        uint8_t num_of_childs;
        uint16_t* child_indexes;
    } TrieElement_t;

    AutoComplete( TrieElement_t* trie_p );

    void searchRecursive( int current_index, char* key, int key_size );
    int searchLastMatchingNode( const char* key );

    int generateHint( const char *key_p, char *buffer_p, int buffer_size_p );
    const char* getResult( int index, bool only_remaining_chars = false );

private:
    TrieElement_t* trie = NULL;
    char *buffer;
    int buffer_size;
    int input_data_size;

    int work_buffer_size;
    int result_buffer_start;

    int result_buffer_counter;
    static const char empty_result;
    const char* result_pointers[ AUTOCOMPLETE_RESULT_SIZE ];
    int result_counter;
};


#endif


/*  Test data
    https://media.geeksforgeeks.org/wp-content/uploads/20220828232752/Triedatastructure1.png

    AutoComplete::TrieElement_t trie[ 9 ];
    uint16_t trie_indexes_element_0[] = { 1, 2 };
    uint16_t trie_indexes_element_1[] = { 3 };
    uint16_t trie_indexes_element_2[] = { 4, 5 };
    uint16_t trie_indexes_element_3[] = { 6, 7 };
    uint16_t trie_indexes_element_4[] = { 8 };

    AutoComplete test( trie );

    trie[ 0 ].c = '\0';
    trie[ 0 ].word_end = false;
    trie[ 0 ].num_of_childs = 2;
    trie[ 0 ].child_indexes = trie_indexes_element_0;

    trie[ 1 ].c = 'a';
    trie[ 1 ].word_end = false;
    trie[ 1 ].num_of_childs = 1;
    trie[ 1 ].child_indexes = trie_indexes_element_1;

    trie[ 2 ].c = 'd';
    trie[ 2 ].word_end = false;
    trie[ 2 ].num_of_childs = 2;
    trie[ 2 ].child_indexes = trie_indexes_element_2;

    trie[ 3 ].c = 'n';
    trie[ 3 ].word_end = false;
    trie[ 3 ].num_of_childs = 2;
    trie[ 3 ].child_indexes = trie_indexes_element_3;

    trie[ 4 ].c = 'a';
    trie[ 4 ].word_end = false;
    trie[ 4 ].num_of_childs = 1;
    trie[ 4 ].child_indexes = trie_indexes_element_4;

    trie[ 5 ].c = 'o';
    trie[ 5 ].word_end = true;
    trie[ 5 ].num_of_childs = 0;
    trie[ 5 ].child_indexes = NULL;

    trie[ 6 ].c = 'd';
    trie[ 6 ].word_end = true;
    trie[ 6 ].num_of_childs = 0;
    trie[ 6 ].child_indexes = NULL;

    trie[ 7 ].c = 't';
    trie[ 7 ].word_end = true;
    trie[ 7 ].num_of_childs = 0;
    trie[ 7 ].child_indexes = NULL;

    trie[ 8 ].c = 'd';
    trie[ 8 ].word_end = true;
    trie[ 8 ].num_of_childs = 0;
    trie[ 8 ].child_indexes = NULL;




*/