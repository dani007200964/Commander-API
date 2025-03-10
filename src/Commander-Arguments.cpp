#include "Commander-Arguments.hpp"

Argument::Argument( const char* source_p, int place_p ){

    // Save the source and set its size to an invalid value by default.
    // if the source is valid, the size will be calculated accordingly.
    source = source_p;
    sourceSize = -1;

    // Save the place to an internal variable.
    place = place_p;

    // In this case the short name is irrelevant,
    // set it to string terminator.
    shortName = '\0';

    // In this case the long name is irrelevant,
    // set it to NULL.
    longName = NULL;

    // By default set te parsed and found flags to false.
    bFields.parsed = false;
    bFields.found = false;

    // If the source is defined correctly,
    // calculate its size.
    if( source ){
        sourceSize = strlen( source );
    }

}

Argument::Argument( const char* source_p, char shortName_p ){

    // Save the source and set its size to an invalid value by default.
    // if the source is valid, the size will be calculated accordingly.
    source = source_p;
    sourceSize = -1;

    // In this case the place is irrelevant,
    // set it to -1.
    place = -1;

    // Save the short name character to internal variable.
    shortName = shortName_p;

    // long name is not defined with this constructor,
    // set it to NULL.
    longName = NULL;

    // By default set te parsed and found flags to false.
    bFields.parsed = false;
    bFields.found = false;

    // If the source is defined correctly,
    // calculate its size.
    if( source ){
        sourceSize = strlen( source );
    }

}

Argument::Argument( const char* source_p, char shortName_p, const char* longName_p ){

    // Save the source and set its size to an invalid value by default.
    // if the source is valid, the size will be calculated accordingly.
    source = source_p;
    sourceSize = -1;

    // In this case the place is irrelevant,
    // set it to -1.
    place = -1;

    // Save the short name character to internal variable.
    shortName = shortName_p;

    // Save the pointer to the long name.
    longName = longName_p;

    // By default set te parsed and found flags to false.
    bFields.parsed = false;
    bFields.found = false;

    // If the source is defined correctly,
    // calculate its size.
    if( source ){
        sourceSize = strlen( source );
    }

}

int Argument::findShortName(){

    // Tracks the current index of the investigated character.
    int index = 0;
    int searchIndex = 0;

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

        // If the '--' string can not be found in the rest of the source array,
        // we have to quit with a negative number.
        if( ( indexFirst - index ) < 0 ){
            return -1;
        }

        // We have to check if we are in a string.
        if( inString( indexFirst ) ){
            //If it is the case we have to search further.
            index++;
            continue;
        }

        // If the first and the second part is next to each other,
        // the second part must be 2 characters behind the first part. 
        if( ( indexSecond - indexFirst ) != 2 ){
            // If it is not the case, we have to search further.
            // We increment the index, and start a next iteration.
            index++;
            continue;
        }

        // If we are here, that means we found a valid combination of
        // the two parts. Still, we have to check the next character after the
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

        // Check if we found string terminator at the end of the long name.
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
            index++;
            continue;
        }

        // If we are here, that means, we have a white
        // space character after the found long name.
        // Set the found flag
        // found = true;
        bFields.found = true;

        // 'Remove' white space characters. Basically, we skip every white space
        // characters to find the real index of the first character of the argument.
        while( ( source[ index ] == ' ' ) || ( source[ index ] == '\t' ) ){

            index++;

            // Check if we found string terminator.
            if( source[ index ] == '\0' ){
                // Set the found flag
                // found = true;
                bFields.found = true;
                return index;
            }

            // Check and handle buffer overflow.
            if( index > sourceSize ){
                return -1;
            }

        }

        // Return with the start index of the data.
        return index;

    }

    // If we are here, that means, w did not found the long name.
    // In this case, we have to return wit negative number.
    return -1;

}

int Argument::findByPlace(){

    int placeCounter = 0;
    int index = 0;
    int startIndex = 0;;

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

    // Remove white space characters.
    while( ( source[ startIndex ] == ' ' ) || ( source[ startIndex ] == '\t' ) ){

        startIndex++;

        // Check and handle buffer overflow.
        if( startIndex >= sourceSize ){
            return -1;
        }

    }

    // Iterate through all the characters in the source buffer.
    for( index = startIndex; index < sourceSize; index++ ){

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
        whiteSpace &= !inString( index );

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

    // By default set it to NULL. It will be changed to a valid address if
    // the argument is a system variable.
    systemVariable = NULL;

    // Try to find the long name.
    startIndex = findLongName();

    // If it fails the next step is to find the short name.
    if( startIndex < 0 ){
    
        // Try to find the short name.
        startIndex = findShortName();
    
        // If it fails the next step is to find by place.
        if( startIndex < 0 ){

            // Try to find by place.
            startIndex = findByPlace();

            // If it fails we can't do anything.
            if( startIndex < 0 ){
                return -1;
            }

        }
    
    }

    // Check if it is a system variable.
    if( source[ startIndex ] == '$' ){
        systemVariable = Commander::getSystemVariable( &source[ startIndex + 1 ] );
    }

    return startIndex;

}

bool Argument::parseInt(){

    // It will store the start address of the data for the current argument.
    int startIndex;

    // It will store the status of the string to integer conversation.
    int status = 0;

    // Clear the parsed flag.
    // parsed = false;
    bFields.parsed = false;

    // Try to find the argument.
    startIndex = findStart();

    // Handle if it is not found.
    if( startIndex < 0 ){
        return false;
    }

    if( systemVariable != NULL ){

        if( ( systemVariable -> data.type ) == Commander::VARIABLE_INT ){
            ret.i = *( systemVariable -> data.data.intData );
            status = 1;
        }

        else if( ( systemVariable -> data.type ) == Commander::VARIABLE_FLOAT ){
            ret.i = (int)*( systemVariable -> data.data.floatData );
            status = 1;
        }

    }

    else{

        // Try to convert string to integer number.
        status = sscanf( &source[ startIndex ], "%d", &ret.i );

    }

    // Check if the conversation was succesful.
    // Store the result to the parsed variable.
    // parsed = status == 1;
    bFields.parsed = status == 1;

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

    if( systemVariable != NULL ){

        if( ( systemVariable -> data.type ) == Commander::VARIABLE_FLOAT ){
            ret.f = *( systemVariable -> data.data.floatData );
            bFields.parsed = true;
        }

        else if( ( systemVariable -> data.type ) == Commander::VARIABLE_INT ){
            ret.f = (float)*( systemVariable -> data.data.intData );
            bFields.parsed = true;
        }

    }

    else{

        // The first character must be a number, or + or - character
        if( ( ( source[ startIndex ] >= '0' ) && ( source[ startIndex ] <= '9' ) ) || ( source[ startIndex ] == '+' ) || ( source[ startIndex ] == '-' ) ){
            // Try to convert string to integer number.
            ret.f = (float)atof( &source[ startIndex ] );

            // Check if the conversation was successful.
            // Store the result to the parsed variable.
            bFields.parsed = true;
        }

    }

    // Return with the result.
    return bFields.parsed;

}

bool Argument::parseStringFunction( char* buffer, int bufferSize ){
    
    // It will store the start address of the data for the current argument.
    int startIndex;

    // Points to the next free element in the buffer.
    int bufferIndex;

    // It indicates quotation mark bounded string.
    bool quotation = false;

    // Next character that is rad from the source buffer.
    char c;

    // Return status for snprintf;
    int status;

    // Clear the parsed flag.
    // parsed = false;
    bFields.parsed = false;

    // Set an invalid address to the outStringBuffer by default.
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

    // If a system variable is requested, but it is not found, we have a problem.
    if( ( source[ startIndex ] == '$' ) && systemVariable == NULL ){
        return false;
    }

    if( systemVariable != NULL ){

        if( ( systemVariable -> data.type ) == Commander::VARIABLE_STRING ){
            strncpy( buffer, systemVariable -> data.data.strData, bufferSize );
            buffer[ bufferSize - 1 ] = '\0';
            ret.c = buffer;
            bFields.parsed = true;
            return true;
        }

        else if( ( systemVariable -> data.type ) == Commander::VARIABLE_INT ){
            status = snprintf( buffer, bufferSize, "%d", *systemVariable -> data.data.intData );
            buffer[ bufferSize - 1 ] = '\0';
            if( ( status > 0 ) && ( status < bufferSize ) ){
                ret.c = buffer;
                bFields.parsed = true;
                return true;
            }
            else{
                return false;
            }
        }

        else if( ( systemVariable -> data.type ) == Commander::VARIABLE_FLOAT ){
            status = Commander::floatToString( *systemVariable -> data.data.floatData, buffer, bufferSize );
            buffer[ bufferSize - 1 ] = '\0';
            if( ( status > 0 ) && ( status < bufferSize ) ){
                ret.c = buffer;
                bFields.parsed = true;
                return true;
            }
            else{
                return false;
            }
        }

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

Commander::systemVariable_t* Argument::getSystemVariable(){
    return systemVariable;
}

const char Argument::failedString = '\0';
