# Client-Server Bidirectional Communication

## 📖 Overview

This project demonstrates two-way communication between a client and a server using TCP sockets and the Winsock library.

Unlike unidirectional communication, both client and server can send and receive messages.

This implementation simulates a simple chat system.

---

## 🎯 Objective

To establish a TCP connection and enable real-time message exchange between client and server.

---

## 🛠 Technologies Used

* C Programming
* Winsock2 Library
* TCP Protocol
* Socket Programming

---

## 📂 Files

```text
client.c
server.c
```

---

## 🔄 Working Principle

1. Server starts and listens on Port 8080.
2. Client connects to the server.
3. Client sends a message.
4. Server receives the message.
5. Server sends a reply.
6. Client receives the reply.
7. Communication continues until "exit" is entered.

---

## ▶ How to Run

### Step 1: Compile Server

```bash
gcc server.c -o server -lws2_32
```

### Step 2: Compile Client

```bash
gcc client.c -o client -lws2_32
```

### Step 3: Start Server

```bash
server.exe
```

Output:

```text
Initializing Winsock...
Server listening on port 8080...
```

### Step 4: Start Client

```bash
client.exe
```

Output:

```text
Connected to server.
```

---

## 💬 Example Communication

### Client

```text
You: Hello
```

### Server

```text
Client: Hello
You: Hi Client
```

### Client

```text
Server: Hi Client
```

---

## ❌ Terminating Connection

Client:

```text
exit
```

Server:

```text
Client disconnected.
```

---

## 📚 Concepts Learned

* TCP Socket Programming
* Full Duplex Communication
* Connection Establishment
* Message Exchange
* Client-Server Architecture

---

## 🎓 Academic Relevance

Computer Networks Laboratory

TCP Communication Practical

Socket Programming Assignment

Networking Mini Project

---

## 🚀 Future Improvements

* Multi-client Chat System
* GUI Interface
* Encryption Support
* File Transfer Feature

---

## 👨‍💻 Author

Amit Kumar Maity
