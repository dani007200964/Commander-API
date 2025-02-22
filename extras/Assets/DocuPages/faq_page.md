@page faq_page Frequently Asked Questions
@tableofcontents

It's always great when questions arise in connection with such a project. Based on the experiences of recent years, we've gathered a few questions that many have asked, and we've tried to provide short, concise answers for each. If you need more information beyond these, feel free to ask on the [GitHub Discussions](https://github.com/dani007200964/Commander-API/discussions) platform.

💡 *Can I use Commander-API without Shellminator to save resources?*  
Absolutely! The `basic.ino` example demonstrates this. However, keep in mind that without Shellminator, you lose features like interactive editing and command history. If you really need to save resources, you can go this route—but only if a reduced user experience isn’t a concern.  

💡 *Does it work on other platforms without the Arduino environment?*  
Yes! We’ve been using it with STM32 for a long time without any issues. There’s even a guide in the Shellminator documentation on how to integrate it into an STM32 environment.  

💡 *Why does dynamic memory run out so quickly on AVR controllers?*  
This is a complex issue. AVR controllers don’t have a unified memory bus, meaning they can’t directly access data from flash memory. As a result, even `const char*` strings end up in dynamic memory. There are two ways to handle this: keep command descriptions short or use AVR-specific memory handling techniques.  

💡 *Does it only work with Serial?*  
Nope! You can use any channel derived from the `Stream` class. With Shellminator, you can even use TCP, WebSocket, or BLE for communication.