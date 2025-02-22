[![Commander-API](extras/Assets/DocuImages/banner.png)](https://www.commanderapi.org/html/index.html)

# 🚀 About  

Commander-API is an easy-to-use command parser library designed for microcontroller environments. Thanks to its low resource requirements, it runs on almost any microcontroller. It’s **Arduino-compatible out of the box**, making it accessible for hobbyists and beginner programmers alike.  

# 🔄 What’s New?  

### 🏗 Argument Handling  
We’re really proud of this feature! Now you can easily and efficiently add arguments to your commands. The argument parser extracts the parameters you need from the raw argument string and even **automatically parses them into strings, floats, and integers** for convenience.  

### 🌍 Environment Variables  
Access and modify C++ variables directly! This makes it much easier to tweak system parameters at runtime. Hopefully, tuning your **PID controller** just got a whole lot easier. 😉  

### 🔧 Major Refactoring  
We know "refactoring" isn’t the most exciting word—especially when it affects backward compatibility—but we believe in improving the project. We put a **huge amount of effort** into optimizing the internal structure (including a new **template-based database**—more on that later) to make Commander-API **faster, cleaner, and more scalable**.  

### 📂 Database Overhaul  
This was one of our biggest tasks! The command storage system, previously tied to Commander, has been modularized for **broader use cases** (like environment variables). We also removed **recursion** entirely—even during initialization—so **embedded developers can breathe a sigh of relief**.  

### ⌨️ Auto-Complete (Experimental)  
We’re working on it! Early results are promising, but for now, **we don’t recommend using it yet**. Stay tuned!  

### 🔌 Abstraction Layers  
As the project grew, we realized it was time to **increase abstraction** for better integration into complex systems. That’s why we introduced the **CommandCaller interface**, making it easier to integrate Commander-API into larger projects.  

### 📡 Pipe Module (Almost Ready!)  
We’re finalizing a **refactored version** of the Pipe module, which should be **more stable, easier to configure, and more flexible** than before. We just need a bit more time to document it—stay tuned for updates!  

### 📖 Better Documentation  
We finally invested the time to create **a user-friendly, well-organized, and example-rich documentation**. It’s available as part of the **Shellminator documentation**, so check it out!  

### ❌ Removal of Built-in Commands  
We had to say goodbye to built-in system commands. 😢 The reason? It was nearly impossible to create a **one-size-fits-all** solution for every microcontroller. The implementation became messy, and it wasn’t fun to look at. **The good news:** We have a new approach in mind, and we’re actively working on a solution!  

# 📚 Documentation  

Commander-API has its own [technical documentation](https://www.commanderapi.org/html/index.html), but **most of the examples are found in the Shellminator documentation**. The Commander-specific docs are for those who want to **dive deep** into how it works under the hood. If you’re impatient, you might even find some **spoilers** about upcoming features!  

# 🤝 Feedback and Contributions  

We've poured **a lot of time and effort** into making this project **stable and easy to use**, but no software is perfect. Bugs happen. Features can improve. And that’s where you come in!  

If you have **feature suggestions, bug reports, or ideas for enhancements**, we’d love to hear from you. Your feedback makes Commander-API better for everyone!  

**Ways to contribute:**  
- 🐛 [Submit an issue](https://github.com/dani007200964/Commander-API/issues/new?template=bug_report.md) 
- 💬 [Join discussions](https://github.com/dani007200964/Commander-API/discussions)
- 🛠 [Share your use cases](https://github.com/dani007200964/Commander-API/discussions/categories/show-and-tell) 

Every contribution, big or small, helps us grow!  

# ❤️ Support  

If this project has been helpful to you and you’d like to **buy us a coffee**, we’d really appreciate it! ☕ Every little bit helps keep this small team motivated.
[![Support](extras/Assets/DocuImages/support.png)](https://ko-fi.com/danielhajnal)

# 🗨️ Contact  

Have a question? Need help? Just want to say hi?  
- 🗨️ [Join the discussions](https://github.com/dani007200964/Commander-API/discussions)
- 🎧 [Find us on Discord](https://github.com/dani007200964/Commander-API/discussions)

We’d love to hear from you! 🚀

# 📃 License  

Commander-API is licensed under the **MIT License**.

© Daniel Hajnal

✉️ hajnal.daniel96@gmail.com