/*
class TrieNode {
    constructor() {
        this.children = {};
        this.isEndOfWord = false;
        this.index = -1;
    }
}

class Trie {
    constructor() {
        this.root = new TrieNode();
        this.elementCounter = 0;
        this.text = {};
    }
  
    insert(word) {
        let node = this.root;
        for (let i = 0; i < word.length; i++) {
            let char = word[i];
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
        }
        node.isEndOfWord = true;
    }

    index_rec( start ){
        start.index = this.elementCounter;
        this.elementCounter++;
        for( let child in start.children ){
            this.index_rec( start.children[ child ] );
        }
    }

    index(){
        this.elementCounter = 0;
        this.index_rec( this.root );
    }

    print_rec( start ){
        //console.log( this.elementCounter, start.isEndOfWord, start.children, Object.keys(start.children).length );
        //if( !this.text[ start.index ] ){
        //    this.text[ start.index ] = 
        //} 
        //this.elementCounter++;
        for( let child in start.children ){
            console.log( start.children[ child ] );
            //this.text[ start.children[ child ].index ] = start.children[ child ];
            this.print_rec( start.children[ child ] );
        }
    }

    print(){
        this.index();
        //console.log( this.root );
        this.text = new Array( this.elementCounter ).fill( 'a' );
        //console.log( this.text );
        //console.log( Object.keys( this.root.children ) );
        this.print_rec( this.root );
        //console.log( this.text );
    }
  
}

*/

class TrieNode {
    constructor() {
        this.character = '\0';
        this.children = {};
        this.isEndOfWord = false;
        this.index = -1;
    }
}

class Trie {
    constructor() {
        this.root = new TrieNode();
        this.elementCounter = 0;
        this.array_text = {};
        this.index_text = {};
        this.name = "trie";
    }

    setName( name_p ){
        this.name = name_p;
    }
  
    insert(word) {
        let node = this.root;
        for (let i = 0; i < word.length; i++) {
            let char = word[i];
            if (!node.children[char]) {
                node.children[char] = new TrieNode();
            }
            node = node.children[char];
            node.character = char;
        }
        node.isEndOfWord = true;
    }
  
    index_rec( start ){
        start.index = this.elementCounter;
        this.elementCounter++;
        for( let child in start.children ){
            this.index_rec( start.children[ child ] );
        }
    }

    index(){
        this.elementCounter = 0;
        this.index_rec( this.root );
    }


    print_rec( start ){
        //console.log( this.elementCounter, start.isEndOfWord, start.children, Object.keys(start.children).length );
        //if( !this.text[ start.index ] ){
        //    this.text[ start.index ] = 
        //} 
        //this.elementCounter++;
        let char_local = start.character;
        if( char_local == '\u0000' ){
            char_local = "\\0";
        }
        let array_text_local = "{ \'" + char_local + "\', ";
        array_text_local    += start.isEndOfWord + ", ";
        array_text_local    += Object.keys( start.children ).length + ", ";

        if( Object.keys( start.children ).length > 0 ){
            let index_array_name = this.name + "_element_" + start.index + "_indexes";
            let index_text_local = "uint16_t " + index_array_name + "[] = { ";
            for( let child in start.children ){
                index_text_local += start.children[ child ].index + ", ";
            }
            index_text_local = index_text_local.substring( 0, index_text_local.length - 2 );
            index_text_local += " };";
            if( !this.index_text[ start.index ] ){
                this.index_text[ start.index ] = new String( index_text_local );
            }
            array_text_local += index_array_name + " }";
        }
        else{
            array_text_local += "NULL }";
        }

        if( !this.array_text[ start.index ] ){
            this.array_text[ start.index ] = new String( array_text_local );
        }
        //this.array_text[ start.index ] = start.character;
        for( let child in start.children ){
            console.log( start.children[ child ] );
            //this.text[ start.children[ child ].index ] = start.children[ child ];
            this.print_rec( start.children[ child ] );
        }
    }

    print(){
        this.index();
        //console.log( this.root );
        // this.array_text = new Array( this.elementCounter ).fill( 'a' );
        // this.array_text
        //console.log( this.text );
        //console.log( Object.keys( this.root.children ) );
        this.print_rec( this.root );
        //console.log( this.array_text );
        //console.log( this.index_text );
        
        let output_text  = "// Generated with Commander Trie Generator\n";
        output_text     += "// Trie name: " + this.name + "\n";

        for( let text in this.index_text ){
            output_text += this.index_text[ text ] + "\n";
        }

        output_text += "\nAutoComplete::TrieElement_t " + this.name + "[] = {\n";

        for( let text in this.array_text ){
            output_text += "\t" + this.array_text[ text ] + ",\n";
        }

        output_text = output_text.substring( 0, output_text.length - 2 );
        output_text += "\n};\n";

        console.log( output_text );
        return output_text;

    }
  
}
