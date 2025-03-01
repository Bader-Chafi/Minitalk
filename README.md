# **Minitalk 📨**  
A low-level message-passing system using UNIX signals (`SIGUSR1` & `SIGUSR2`)  

## **Overview**  
Minitalk is a **42 project** that demonstrates **Inter-Process Communication (IPC)** using UNIX signals. It consists of a **server** and a **client**, where the client sends messages **bit by bit** using signals. The server reconstructs the message and prints it to the terminal, supporting **ASCII and UTF-8 characters (including emojis 🎉).**  

This project provides a deeper understanding of:  
✔️ **Signal handling (`sigaction`)**  
✔️ **Bitwise operations for data transmission**  
✔️ **Process synchronization**  

## **How It Works**  
1. The **client** converts each character of the message into binary.  
2. It sends **each bit** using:  
   - `SIGUSR1` → Represents **0**  
   - `SIGUSR2` → Represents **1**  
3. The **server** captures each signal and reconstructs the message **bit by bit**.  
4. After receiving 8 bits, the server **stores the full byte**, detects multi-byte sequences (for UTF-8), and prints the message when fully received.  

---

## **Key Features**  
✅ **Precise bitwise transmission using signals**  
✅ **Supports ASCII and multi-byte UTF-8 characters (like emojis 🎉, Arabic, Chinese, etc.)**  
✅ **Handles long messages without data loss**  
✅ **Manages multiple clients sending messages to the same server**  
✅ **Acknowledge receipt by sending feedback signals to the client**  

---

## **Installation & Usage**  

### **1️⃣ Compile the Project**  
```sh
make
```  

### **2️⃣ Start the Server**  
Run the server first:  
```sh
./server
```
This will display the **Process ID (PID)**.  

### **3️⃣ Send a Message from the Client**  
```sh
./client <server_pid> "Hello, Minitalk! 🚀"
```
For example:  
```sh
./client 12345 "42 is awesome! 🎯"
```

### **4️⃣ Expected Output (on the server)**  
```sh
42 is awesome! 🎯
```

---

## **Handling Unicode (UTF-8) Characters**  
Minitalk **correctly transmits UTF-8 characters**, even **multi-byte** ones (e.g., emojis, Arabic, Japanese, etc.), because it **transfers raw bytes instead of ASCII characters**.  

### **UTF-8 Encoding Example**  
If you send `"🚀"` (the rocket emoji), the client transmits **4 bytes**:  
```
11110000 10011111 10011001 10000010
```
The server reconstructs the bits **byte by byte** and prints the correct UTF-8 character.  

---

## **Advanced Technical Details**  

### **1️⃣ Signal Handling (`sigaction`)**  
Minitalk uses `sigaction()` instead of `signal()` because it provides **better control** and allows access to `siginfo_t` (which contains sender PID).  

Example of signal handling in the server:  
```c
struct sigaction sa;
sa.sa_sigaction = signal_handler;
sa.sa_flags = SA_SIGINFO;
sigaction(SIGUSR1, &sa, NULL);
sigaction(SIGUSR2, &sa, NULL);
```
- The `SA_SIGINFO` flag allows capturing sender **PID**.  
- This prevents signal mix-ups when **multiple clients** are communicating.  

---

### **2️⃣ Bitwise Operations for Efficient Transmission**  
Each **character** is converted into **8 bits**, and the client sends one bit at a time.  

Example of encoding and sending bits:  
```c
for (int i = 7; i >= 0; i--)
{
    if ((character >> i) & 1)
        kill(server_pid, SIGUSR2);  // Send '1'
    else
        kill(server_pid, SIGUSR1);  // Send '0'
    usleep(100); // Prevent signal loss
}
```
- **Bitwise shift (`>>`)** extracts bits one by one.  
- **Logical AND (`& 1`)** checks if the bit is 0 or 1.  
- **usleep()** prevents race conditions and ensures reliable transmission.  

---

### **3️⃣ Acknowledgments for Reliability**  
The **server** can send **confirmation signals** (`SIGUSR1`) back to the **client** after receiving a full byte.  

This prevents **packet loss** and allows for a **smoother message flow**.  

Example in the server:  
```c
if (received_char == '\0')
    kill(sender_pid, SIGUSR1);  // Notify client that message is complete
```

---

## **Bonus Features**  
✔️ **Handles concurrent clients without data loss**  
✔️ **UTF-8 multi-byte character support**  
✔️ **Graceful error handling (invalid PIDs, broken pipes, etc.)**  
✔️ **Optimized timing to prevent signal loss**  

---

## **Resources & Further Reading**  
📖 **UNIX Signals** → [`man 2 kill`](https://man7.org/linux/man-pages/man2/kill.2.html)  
📖 **Inter-Process Communication (IPC)** → [`man 7 signal`](https://man7.org/linux/man-pages/man7/signal.7.html)  
📖 **UTF-8 Encoding & Multi-byte Characters** → [UTF-8 Specification](https://www.utf8-chartable.de/)  

---

## **Final Thoughts**  
Minitalk is a **powerful exercise** in **bitwise operations, process synchronization, and signal handling**. It demonstrates how signals can be used to **transmit data between processes efficiently**.  

Enjoy In Your Own Code (: 🚀
