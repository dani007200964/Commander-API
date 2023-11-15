@page user_settings User Settings

# Modify default settings in Arduino IDE

If you use this library with Arduino IDE, you need to do a few extra steps to modify the
default settings of the library.

First, you need to download Commander-Settings.zip file and extract it to
__Documents\Arduino\libraries__ folder. The folder structure should look like
this:

```bash
Documents
└── Arduino
    └── libraries
        └── Commander-Settings
            └── Commander-Settings.hpp
```

The __Commander-Settings.hpp__ file contains a pre-made configuration,
where all the user-modifiable parameters can be found. If you need to change
one, just uncomment it and set the desired value for it.

Why is this so difficult? Sadly, Arduino IDE separates the project file
from the library. Because of this, the library can not 'see' the project files.
Luckily, the libraries can find each others source files. If you want to
modify the defines in a library, a helper library is needed, to overwrite the
parameters in the original library.

@note If someone knows a better solution, please let me know.