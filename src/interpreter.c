#include "../inc/interpreter.h"

API_t API_tree[NUM_OF_API_FUNCS];
uint32_t API_cntr;

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

        API_tree[0].left = NULL;  //  because it is the first element of the tree,
        API_tree[0].right = NULL; //  left and right branches has to be NULL
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

        API_tree[API_cntr].name = (const char**)name;  //  address of the name string( char** type )
        API_tree[API_cntr].desc = (const char**)desc;  //  address of the description string( char** type )
        API_tree[API_cntr].func = func;                //  function pointer to the actual function

        API_tree[API_cntr].left = NULL;  //  close the branch
        API_tree[API_cntr].right = NULL;
    }

    API_cntr++;

}

void print_apis_in_order(API_t *head){
  
  if( head==0 ){
    return;
  }

  print_apis_in_order( head -> left );
  printf( "%s\r\n", *(head->name) );
  print_apis_in_order( head -> right );
}
