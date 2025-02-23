# **Minitalk** 📨  
*A simple message-passing system using UNIX signals (SIGUSR1 & SIGUSR2)*  

## **Overview**  
Minitalk is a 42 project that demonstrates **Inter-Process Communication (IPC)** using **signals**. It consists of a **server** and a **client**, where the client sends messages to the server **bit by bit** using `SIGUSR1` and `SIGUSR2`. The server reconstructs the message and prints it to the terminal.

## **Features**  
✅ Send messages between processes using signals  
✅ Support for **UTF-8 characters** (including emojis 🎉)  
✅ Handles **variable-length messages**  
✅ Manages **multiple clients** communicating with the server  

## **How It Works**  
1. The **client** converts each character of the message into **binary**.  
2. It sends **each bit** using `SIGUSR1` (0) or `SIGUSR2` (1) to the **server**.  
3. The **server** receives the signals, reconstructs the character, and prints the message.  

## **Installation & Usage**  

### **1. Compile the Project**  
```sh
make
```

### **2. Start the Server**  
```sh
./server
```
- The server will display its **Process ID (PID)**.  

### **3. Send a Message from the Client**  
```sh
./client <server_pid> "Hello, Minitalk! 🚀"
```

### **4. Expected Output (on the server)**  
```
Hello, Minitalk! 🚀
```

## **Handling Unicode (UTF-8) Characters**  
Minitalk correctly sends and reconstructs **multi-byte characters** (like emojis, Arabic, Chinese, etc.) because it transmits **raw bytes** of UTF-8 sequences.

## **Bonus Features**  
✔️ Handle long messages without data loss  
✔️ Implement acknowledgments for reliable communication  
✔️ Support multiple clients  

## **Resources**  
- UNIX Signals: [`man 2 kill`](https://man7.org/linux/man-pages/man2/kill.2.html)  
- Inter-Process Communication: [`man 7 signal`](https://man7.org/linux/man-pages/man7/signal.7.html)  
- UTF-8 Encoding: [UTF-8 Specification](https://en.wikipedia.org/wiki/UTF-8)  

---

🚀
