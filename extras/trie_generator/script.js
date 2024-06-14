require.config({ paths: { 'vs': 'https://cdnjs.cloudflare.com/ajax/libs/monaco-editor/0.31.1/min/vs' }});
require(['vs/editor/editor.main'], function() {
    const generateBtn = document.getElementById('generateBtn');
    const helpBtn = document.getElementById('helpBtn');
    const inputText = document.getElementById('inputText');
    
    // Initialize Monaco Editor
    const editor = monaco.editor.create(document.getElementById('outputText'), {
        value: '',
        language: 'cpp',
        theme: 'vs-dark',
        readOnly: true,
        lineNumbers: "on",
        minimap: {
            enabled: true
        },
        scrollBeyondLastLine: false,
        automaticLayout: true
    });

    generateBtn.addEventListener('click', function() {
        const input = inputText.value;
        const generatedOutput = generateTrie(input);
        editor.setValue(generatedOutput);
    });

    copyBtn.addEventListener('click', function() {
        const generatedOutput = editor.getValue();
        navigator.clipboard.writeText(generatedOutput).then(() => {
            alert('Copied to clipboard');
        });
    });

    helpBtn.addEventListener('click', function() {
        alert('Enter text into the input box. Click "Generate" to create the Trie. Use the "Copy" button to copy the generated output.');
    });

    function generateTrie(input) {

        var separateLines = input.split( '\n' );

        for( let i = 0; i < separateLines.length; i++ ){
            separateLines[ i ] = ' ' + separateLines[ i ].trim();
        }

        //console.log( separateLines );

        let trie = new Trie();

        for( let i = 0; i < separateLines.length; i++ ){
            trie.insert( separateLines[ i ] );
        }

        console.log( trie );

        trie.print();

        // Replace this with your actual Trie generation logic
        return trie.print();
    }
});
