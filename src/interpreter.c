#include "../inc/interpreter.h"

API_t API_tree[NUM_OF_API_FUNCS];
uint32_t API_cntr;

uint32_t API_place_cntr;

//macro to add new instruction to the instructions binary tree
#define create_instruction_data(name, desc)            \
    const char *name##_API_NAME = (const char *)#name; \
    const char *name##_API_DESC = (const char *)desc;

//  *****  Create instruction data for the API  *****
create_instruction_data(cica, "cica fuggveny leirasa, jeeee :)");
create_instruction_data(kutya, "kutya fuggveny leirasa, joooo :)");
create_instruction_data(tehen, "tehen fuggveny leirasa, jii :)");
create_instruction_data(majom, "majom fuggveny leirasa, jaaaa :)");
create_instruction_data(eger, "eger fuggveny leirasa, gyoooo :)");
create_instruction_data(okor, "eger fuggveny leirasa, gyaaa :)");
create_instruction_data(csiga, "eger fuggveny leirasa, dikk :)");

#define add_instruction(name, func) add_interpreter_instruction(&name##_API_NAME, &name##_API_DESC, func);

void cica_func(char *args, char *response)
{
    printf("Cica!\r\n");
    printf("Args: %s\r\n", args);
}

void kutya_func(char *args, char *response)
{
    printf("Kutya!\r\n");
    printf("Args: %s\r\n", args);
}

void init_interpreter(void)
{
    //  Initialize the 'API_cntr' variable as zero before adding new items
    API_cntr = 0;

    //  *****  Create the binary tree of the instructions  *****
    add_instruction(majom, kutya_func);
    add_instruction(tehen, kutya_func);
    add_instruction(cica, cica_func);
    add_instruction(kutya, kutya_func);
    add_instruction(eger, kutya_func);
    add_instruction(okor, kutya_func);
    add_instruction(csiga, kutya_func);

    //  Index eache element to find their place in alphabetic order
    index_apis_in_order( &API_tree[0] );

    //  Optimise the API_tree to make it balanced
    optimise_api_tree( &API_tree[0] );

    //  Print the API list
    print_apis_in_order( &API_tree[0] );

    if( API_cntr != NUM_OF_API_FUNCS ){
        printf("**ERROR**\tAPI function number mismatch!!!\r\n");
    }
}

void add_interpreter_instruction(const char **name, const char **desc, void (*func)(char *, char *))
{
    API_t *next;
    API_t *prev;
    int32_t comp_res;

    //  if the API_cntr value is greater or equal than the defined maximum
    //  API command number, there is a problem in the code!
    if (API_cntr >= NUM_OF_API_FUNCS)
    {

        printf("**ERROR**\tToo many instruction, memory is full!\r\n");
        return;
    }

    //  print out the new command name
    //printf("%s\r\n", (char *)*name);

    //  if it is the first command we hacve to create the root of the
    //  binary tree
    if (API_cntr == 0)
    {
        API_tree[0].name = (const char**)name;  //  address of the name string( char** type )
        API_tree[0].desc = (const char**)desc;  //  address of the description string( char** type )
        API_tree[0].func = func;                //  function pointer to the actual function

        API_tree[0].left = NULL;    //  because it is the first element of the tree,
        API_tree[0].right = NULL;   //  left and right branches has to be NULL

        API_tree[0].place = 0;      //  default place = 0  
        
    }

    // if it is ot the first command we have to find it's place in the tree
    else
    {
        prev = &API_tree[0];                        //  get the address of the root element
        comp_res = strcmp( (char*)*(prev->name), (char*)*name );    //  compare the names and save the result to 'comp_res'

        //  compare( ABC order ) the root element name and the new element name
        (comp_res > 0) ? (next = (prev->left)) : ( next = (prev->right));

        //  find the place in the tree
        while (next != 0)
        {
            prev = next;
            comp_res = strcmp( *(prev->name), *name);
            (comp_res > 0) ? (next = (prev->left)) : (next = (prev->right));
        }

        //  link the new item on the previous branch
        ( comp_res > 0 ) ? ( ( prev->left ) = &API_tree[API_cntr] ) : ( ( prev->right ) = &API_tree[API_cntr] );        

        //  Fill the new item parameters

        API_tree[API_cntr].name = (const char**)name;  //  address of the name string( char** type )
        API_tree[API_cntr].desc = (const char**)desc;  //  address of the description string( char** type )
        API_tree[API_cntr].func = func;                //  function pointer to the actual function

        API_tree[API_cntr].left = NULL;     //  close the branch
        API_tree[API_cntr].right = NULL;

        API_tree[API_cntr].place = 0;       //  default place = 0  

    }

    API_cntr++;

}

//  Creates indexes by alphabetical order for each element
//  The result is stored in the 'place' variable inside the API_t structure
void index_apis_in_order(API_t *head){

    API_place_cntr = 0;

    recursive_indexer( head );

    printf( "Indexer finished...\r\n" );

}

//  This function is used by the 'index_apis_in_order' function
void recursive_indexer(API_t *head){

    //  End of recursive algorythm
    if( head == 0 ){

        return;

    }

    recursive_indexer( head -> left );

    head -> place = API_place_cntr;
    API_place_cntr++;

    recursive_indexer( head -> right );   

}

//  This function is used to print out the API to the console
void print_apis_in_order(API_t *head){
  
    //  End of recursive algorythm
    if( head == 0 ){
        return;
  }

    print_apis_in_order( head -> left );
    printf( "%d.\t%s\r\n", head -> place , *(head -> name) );
    print_apis_in_order( head -> right );

}

//  Finds the array index( API_tree index ) by place( alphabetical order )
uint16_t find_api_index_by_place( uint16_t place ){

    uint16_t i;

    for( i = 0; i < NUM_OF_API_FUNCS; i++ ){

        if( API_tree[i].place == place ){
            
            return i;

        }

    }
    return 0;
}

//  This function is used to put an element in API_tree by index from place
//  Example: to put the place=3 node to API_tree[0]
//              swap_api_elements( 0, 3 );
void swap_api_elements( uint16_t index, uint16_t place ){

    API_t buffer;
    uint16_t current_index;

    //  Find the index in the array by place of the 'i'-th element
    current_index = find_api_index_by_place( place );

    //  save the context of the 'i'-th element to the buffer
    buffer = API_tree[index];

    //  write the 'current_index'-th element to the 'i'-th element
    API_tree[index] = API_tree[current_index];

    //  write the buffer to the 'current_index'-th element
    API_tree[current_index] = buffer;

}

//  This function is used to balance the API_tree to get the highest
//  search performance
void optimise_api_tree(API_t *head){

    uint32_t i;
    API_t buffer;

    //  recursive optimiser need to initialise 'API_cntr' to 0
    API_cntr = 0;

    //  recursively finds the order which is optimal for a balanced tree
    recursive_optimiser( 0, NUM_OF_API_FUNCS - 1 );


    //  The order is good, but the connection between the branches broken,
    //  because we swapped the API_tree array elements.
    //  To fix this problem we have to reinitialise the tree, and use
    //  'add_interpreter_instruction' function again for all elements.
    API_cntr = 0;
    for( i = 0; i < NUM_OF_API_FUNCS; i++ ){

        //  Put the data to the buffer then rewrite the data with fixed parameters.
        buffer = API_tree[i];

        add_interpreter_instruction( buffer.name, buffer.desc, buffer.func );

        //  Save the place data as well.
        API_tree[i].place = buffer.place;

    }
}

//  This function is used to order the elements in API_tree array to
//  get the fastest search speed
//  this function needs 'API_cntr' to be zeroed out before the first call
void recursive_optimiser( int32_t start_index, int32_t stop_index ){

    int32_t mid;

    //  End of recursive algorythm
    if( start_index > stop_index ){

        return;

    }

    //  Find the middle of the intervall
    mid = ( start_index + stop_index ) / 2;

    //  Put the right element to it's place
    swap_api_elements( API_cntr, mid );
    API_cntr++;

    //  Do some recursion for the other intervalls
    recursive_optimiser( start_index, mid - 1 );
    recursive_optimiser( mid + 1, stop_index );


}
