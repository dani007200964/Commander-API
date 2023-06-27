#include "Commander-Arguments.hpp"

Argument::Argument( const char* source_p, int place_p ){

    source = source_p;
    sourceSize = -1;

    place = place_p;
    shortName = '\0';
    longName = NULL;
    parsed = false;

    if( source ){
        sourceSize = strlen( source );
    }

}

Argument::Argument( const char* source_p, char shortName_p ){

    source = source_p;
    sourceSize = -1;

    place = -1;
    shortName = shortName_p;
    longName = NULL;
    parsed = false;

    if( source ){
        sourceSize = strlen( source );
    }

}

Argument::Argument( const char* source_p, char shortName_p, const char* longName_p ){

    source = source_p;
    sourceSize = -1;

    place = -1;
    shortName = shortName_p;
    longName = longName_p;
    parsed = false;

    if( source ){
        sourceSize = strlen( source );
    }

}

int Argument::findShortName(){

    // Tracks the current index of the investigated character.
    int index;

    // Array, that contains the searched argument name.
    char expected[ 3 ] = { '-', '\0', '\0' };

    // Check if the source is not set correctly.
    if( source == NULL ){
        return -1;
    }

    // Only alphabetical characters are valid.
    if( !( ( ( shortName >= 'A' ) && ( shortName <= 'Z' ) ) || ( ( shortName >= 'a' ) && ( shortName <= 'z' ) ) ) ){
        return -1;
    }

    // The alphabetical identifier is added to the expected string.
    expected[ 1 ] = shortName;

    // Try to find the argument name in the source array.
    index = substring( expected, (char*)source );

    // Check if we found the short name in the source.
    // If not, return with invalid address.
    if( index < 0 ){

        return -1;

    }

    // Jump after the short name. It is 2 characters long.
    index += 2;

    // Check and handle buffer overflow.
    if( index >= sourceSize ){

        return -1;

    }

    // Remove white space characters.
    while( ( source[ index ] == ' ' ) || ( source[ index ] == '\t' ) ){

        index++;

        // Check and handle buffer overflow.
        if( index >= sourceSize ){

            return -1;

        }

    }

    // Return with the start index of the data.
    return index;

}

int Argument::findLongName(){

    // Tracks the current index of the investigated character.
    int index = 0;

    // The long argument name looks like this: --name
    // It can be splitted to two parts: -- , name
    // The first part is is fix, it always look like this: --
    // The second part is the actual name of the argument,
    // it is stored in longName.
    // According to this we will try to find the start index of
    // the two parts.
    int indexFirst;
    int indexSecond;

    // Expected string array for the first part.
    char expected[ 3 ] = { '-', '-', '\0' };

    // Check if the source is not set correclty.
    if( source == NULL ){
        return -1;
    }

    // Check if the longName is not set correclty.
    if( longName == NULL ){
        return -1;
    }

    // Try to find a valid combination for the first and second part.
    // The exit event is when we run out of the bounds of the source array.
    while( index < sourceSize ){

        // This is tricky. We have to offset the return value of substring wiht the index;
        // Also, in every iteration we have to offset the start address of the sorce array with index.
        indexFirst = index + substring( expected, (char*)&source[ index ] );
        indexSecond = index + substring( (char*)longName, (char*)&source[ index ] );

        // If the '--' string can not be found in the rest of the source array, we have to quit.
        if( indexFirst < 0 ){

            return -1;

        }

        // If the first and the second part is next to each other, the second part is 2 characters
        // behind the first part. 
        if( ( indexSecond - indexFirst ) != 2 ){

            // If it is not the case, we have to search further.
            // We increment the index, and start a next iteration from here.
            index = indexFirst + 1;
            continue;

        }

        // If we are here, that means we found a valid combination of
        // the two parts. Still we have to check the next character after the
        // second part.
        // For example:
        // --name
        // --nameeee
        // These strings will both come here because the compensation happens from left to right.
        // We have to detect the end of the token as well.
        index = indexSecond + strlen( longName );

        // Check and handle buffer overflow.
        if( index >= sourceSize ){

            return -1;

        }

        // We need at least one white space character after the name.
        if( !( ( source[ index ] == ' ' ) || ( source[ index ] == '\t' ) ) ){

            // If it is not the case, we have to search further.
            // We increment the index, and start a next iteration from here.
            continue;

        }

        // Remove white space characters.
        while( ( source[ index ] == ' ' ) || ( source[ index ] == '\t' ) ){

            index++;

            // Check and handle buffer overflow.
            if( index >= sourceSize ){

                return -1;

            }

        }

        // Return with the start index of the data.
        return index;

    }

    return -1;

}

int Argument::findPlace(){

    int placeCounter = 0;
    int index = 0;

    bool prevWhiteSpace = false;
    bool whiteSpace;

    // Check if the place is invalid.
    if( place < 0 ){
        return -1;
    }

    // Check if the source is not set correclty.
    if( source == NULL ){
        return -1;
    }

    // Iterate through all the characters in the source buffer.
    for( index = 0; index < sourceSize; index++ ){

        // Check if we found the right place.
        if( placeCounter == place ){

            // Remove white space characters.
            while( ( source[ index ] == ' ' ) || ( source[ index ] == '\t' ) ){

                index++;

                // Check and handle buffer overflow.
                if( index >= sourceSize ){

                    return -1;

                }

            }

            // Return with the start index of the data.
            return index;

        }

        // Detect if we changing from non whitespace to whitespace character.
        whiteSpace = ( source[ index ] == ' ' ) || ( source[ index ] == '\t' );

        if( ( prevWhiteSpace == false ) && ( whiteSpace == true ) ){

            // It means we have to increment the place counter.
            placeCounter++;
        }

        // Store the current state for the next iteration.
        prevWhiteSpace = whiteSpace;


    }

    return -1;

}

bool Argument::parseInt(){

    // It will store the start address of the data for the current argument.
    int startIndex;

    // It will store the status of the string to integer conversation.
    int status;

    // Try to find the long name.
    startIndex = findLongName();

    // If it fails the next step is to find the short name.
    if( startIndex < 0 ){
    
        // Try to find the short name.
        startIndex = findShortName();
    
        // If it fails the next step is to find by place.
        if( startIndex < 0 ){

            // Try to find by place.
            startIndex = findPlace();

            // If it fails we can't do anything.
            if( startIndex < 0 ){

                return false;

            }

        }
    
    }

    // Try to convert string to integer number.
    status = sscanf( &source[ startIndex ], "%d", &intResult );

    // Check if the conversation was succesful.
    // Store the result to the parsed variable.
    parsed = status == 1;

    // Return with the result.
    return parsed;

}

Argument::operator int(){

    return intResult;

}

Argument::operator bool(){

    return parsed;

}


int Argument::substring( char* str1, char* str2 ){

  // https://www.geeksforgeeks.org/check-string-substring-another/

  int i;
  int j;

  int m = strlen( str1 );
  int n = strlen( str2 );

  for( i = 0; i <= ( n - m ); i++ ){

    for( j = 0; j < m; j++ ){

      if( str2[ i + j ] != str1[ j ] ){
        break;
      }

    }

    if( j == m ){

      return i;

    }

  }

  return -1;

}

