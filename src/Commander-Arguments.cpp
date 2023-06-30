#include "Commander-Arguments.hpp"

Argument::Argument( const char* source_p, int place_p ){

    source = source_p;
    sourceSize = -1;

    place = place_p;
    shortName = '\0';
    longName = NULL;
    //parsed = false;
    //found = false;
    bFields.parsed = false;
    bFields.found = false;

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
    //parsed = false;
    //found = false;
    bFields.parsed = false;
    bFields.found = false;

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
    //parsed = false;
    //found = false;
    bFields.parsed = false;
    bFields.found = false;

    if( source ){
        sourceSize = strlen( source );
    }

}

int Argument::findShortName(){

    // Tracks the current index of the investigated character.
    int index = 0;
    int searchIndex = 0;
    int offset = 0;

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

    while( true ){

        // Try to find the argument name in the source array.
        index = substring( expected, (char*)&source[ searchIndex ] );

        // Check if we found the short name in the source.
        // If not, return with invalid address.
        if( index < 0 ){

            return -1;

        }

        if( !inString( index + searchIndex ) ){
            searchIndex += 2;
            // Check and handle buffer overflow.
            if( ( index + searchIndex ) > sourceSize ){
                return -1;
            }

            if( ( source[ index + searchIndex ] == ' ' ) || ( source[ index + searchIndex ] == '\t' ) || ( source[ index + searchIndex ] == '\0' ) ){
                break;            
            }
        }

        searchIndex += 2;
        // Check and handle buffer overflow.
        if( ( index + searchIndex ) > sourceSize ){
            return -1;
        }

    }

    index = index + searchIndex;

    // Set the found flag
    // found = true;
    bFields.found = true;

    // Jump after the short name. It is 2 characters long.
    //index += 2;

    // Check and handle buffer overflow.
    if( index > sourceSize ){

        return -1;

    }

    // Remove white space characters.
    while( ( source[ index ] == ' ' ) || ( source[ index ] == '\t' ) ){

        index++;

        // Check and handle buffer overflow.
        if( index > sourceSize ){

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
    while( index <= sourceSize ){

        // This is tricky. We have to offset the return value of substring wiht the index;
        // Also, in every iteration we have to offset the start address of the sorce array with index.
        indexFirst = index + substring( expected, (char*)&source[ index ] );
        indexSecond = index + substring( (char*)longName, (char*)&source[ index ] );

        // If the '--' string can not be found in the rest of the source array, we have to quit.
        if( ( indexFirst - index ) < 0 ){

            return -1;

        }

        // We have to check if we are in a string.
        if( inString( indexFirst ) ){
            //If it is the case we have to search further.
            index++;
            continue;

        }

        // If the first and the second part is next to each other, the second part is 2 characters
        // behind the first part. 
        if( ( indexSecond - indexFirst ) != 2 ){

            // If it is not the case, we have to search further.
            // We increment the index, and start a next iteration.
            index++;
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
        if( index > sourceSize ){

            return -1;

        }

        if( source[ index ] == '\0' ){
            // Set the found flag
            // found = true;
            bFields.found = true;
            return index;
        }

        // We need at least one white space character after the name.
        if( !( ( source[ index ] == ' ' ) || ( source[ index ] == '\t' ) ) ){

            // If it is not the case, we have to search further.
            // We increment the index, and start a next iteration from here.
            continue;

        }

        // Set the found flag
        // found = true;
        bFields.found = true;

        // Remove white space characters.
        while( ( source[ index ] == ' ' ) || ( source[ index ] == '\t' ) ){

            index++;

            // Check and handle buffer overflow.
            if( index > sourceSize ){

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

int Argument::findStart(){

    // This will hold the return value.
    int startIndex;

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

                return -1;

            }

        }
    
    }

    return startIndex;

}

bool Argument::parseInt(){

    // It will store the start address of the data for the current argument.
    int startIndex;

    // It will store the status of the string to integer conversation.
    int status;

    // Clear the parsed flag.
    // parsed = false;
    bFields.parsed = false;

    // Try to find the argument.
    startIndex = findStart();

    // Handle if it is not found.
    if( startIndex < 0 ){
        return false;
    }

    // Try to convert string to integer number.
    status = sscanf( &source[ startIndex ], "%d", &ret.i );

    // Check if the conversation was succesful.
    // Store the result to the parsed variable.
    // parsed = status == 1;
    bFields.parsed = status == 1;;

    // Return with the result.
    return bFields.parsed;

}

bool Argument::parseFloat(){

    // It will store the start address of the data for the current argument.
    int startIndex;

    // Clear the parsed flag.
    // parsed = false;
    bFields.parsed = false;

    // Try to find the argument.
    startIndex = findStart();

    // Handle if it is not found.
    if( startIndex < 0 ){
        return false;
    }

    // The first character must be a number, or + or - character
    if( ( ( source[ startIndex ] >= '0' ) && ( source[ startIndex ] <= '0' ) ) || ( source[ startIndex ] == '+' ) || ( source[ startIndex ] == '-' ) ){
        // Try to convert string to integer number.
        ret.f = (float)atof( &source[ startIndex ] );

        // Check if the conversation was succesful.
        // Store the result to the parsed variable.

        bFields.parsed = true;
    }

    // Return with the result.
    return bFields.parsed;

}

bool Argument::parseStringFunction( char* buffer, int bufferSize ){
    
    // It will store the start address of the data for the current argument.
    int startIndex;

    // It will store the status of the string to integer conversation.
    int status;

    // Points to the next free element in the buffer.
    int bufferIndex;

    // It indicates quotation mark bounded string.
    bool quotation = false;

    // Next character that is rad from the source buffer.
    char c;

    // Clear the parsed flag.
    // parsed = false;
    bFields.parsed = false;

    // Set an invalid addres to the outStringBuffer by default.
    // outStringBuffer = NULL;
    ret.c = NULL;

    // Check for invalid buffer size.
    if( bufferSize < 1 ){

        return false;

    }

    // Try to find the argument.
    startIndex = findStart();

    // Handle if it is not found.
    if( startIndex < 0 ){
        return false;
    }

    // The first character of the string should not be a '-'
    // Character.
    if( source[ startIndex ] == '-' ){
        return false;
    }

    if( source[ startIndex ] == '\"' ){
        quotation = true;
        startIndex++;

        // Check and handle buffer overflow.
        if( startIndex >= sourceSize ){
            return false;
        }

    }


    for( bufferIndex = 0; bufferIndex < bufferSize; bufferIndex++ ){
        
        // Check and handle buffer overflow.
        if( ( startIndex + bufferIndex ) > sourceSize ){
            return false;
        }

        // Read the next character from the source buffer.
        c = source[ startIndex + bufferIndex ];

        // First case is when the input string is bounded with " characters.
        if( quotation ){

            if( c != '\"' ){
                buffer[ bufferIndex ] = c;
            }

            else{
                buffer[ bufferIndex ] = '\0';
                //outStringBuffer = buffer;
                //parsed = true;
                bFields.parsed = true;
                ret.c = buffer;
                return true;
            }

        }

        // Second case is when the input string is ended with a white space character or string terminator.
        else{

            if( ( c == ' ' ) || ( c == '\t' ) || ( c == '\0' ) ){
                buffer[ bufferIndex ] = '\0';
                // outStringBuffer = buffer;
                ret.c = buffer;
                //parsed = true;
                bFields.parsed = true;
                return true;
            }

            else{
                buffer[ bufferIndex ] = c;
            }

        }

    }

    // If we are here, that means we did not found the end of the string.
    // It probably means, that the buffer is too short, or the " bounded
    // string is not terminated.
    return false;

}

bool Argument::find(){

    // Reset the found flag.
    // found = false;
    bFields.found = false;

    findLongName();
    findShortName();

    return bFields.found;

}

Argument::operator int(){

    //if( parsed ){
    if( bFields.parsed ){
        return ret.i;
    }
    return 0;

}

Argument::operator float(){

    //if( parsed ){
    if( bFields.parsed ){
        return ret.f;
    }
    return 0.0;

}

Argument::operator bool(){

    //return parsed;
    return bFields.parsed;

}

Argument::operator char*(){

    //if( ( !parsed ) || ( ret.c == NULL ) ){
    if( ( !bFields.parsed ) || ( ret.c == NULL ) ){

        return (char*)&failedString;

    }

    return ret.c;

}

bool Argument::isFound(){
    //return found;
    return bFields.found;
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

bool Argument::inString( int index ){

    int i;
    bool ret = false;

    // Check if the source is not set correclty.
    if( source == NULL ){
        return false;
    }

    if( index < 0 ){
        return false;
    }

    for( i = 0; i < index; i++ ){

        if( source[ i ] == '\"' ){
            ret = !ret;
        }

    }

    return ret;
    
}

const char Argument::failedString = '\0';
