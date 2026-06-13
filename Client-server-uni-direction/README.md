# Client-Server Unidirectional Communication

## 📖 Overview

This project demonstrates basic TCP socket communication between a client and a server using the Winsock library in C.

In this implementation, communication is **one-way (unidirectional)**:

* Client sends a message.
* Server receives the message.
* No response is sent back to the client.

This program helps understand the fundamentals of socket programming and TCP/IP communication.

---

## 🎯 Objective

To establish a TCP connection between a client and a server and transmit a message from the client to the server.

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

1. Server starts and waits for connections.
2. Client connects to the server.
3. User enters a message on the client side.
4. Client sends the message.
5. Server receives and displays the message.
6. Connection closes.

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

### Step 3: Run Server

```bash
server.exe
```

Output:

```text
Initializing Winsock...
Receiver waiting for msg...
```

### Step 4: Run Client

```bash
client.exe
```

Example:

```text
enter msg to send : Hello Server
Msg sent: Hello Server
```

Server Output:

```text
Msg received: Hello Server
```

---

## 📚 Concepts Learned

* Socket Creation
* TCP Connection
* Client-Server Architecture
* Data Transmission
* Winsock API

---

## 🎓 Academic Relevance

Computer Networks Laboratory
Socket Programming Practical
TCP/IP Communication Fundamentals

---

## 👨‍💻 Author

Amit Kumar Maity
