# Programming-Assignment-5
Amanda Mathison

Problem statement:
Create a program that the server accepts a filename from the client and sends back what is inside the file, such as a hello.txt file. 
The client also requests a file and prints the server's response. The file contents must also not be longer than 255 characters. These programs should also handle invalid files, file
not found, and print a default message if the original message is too long.

Describe the Solution:
Overall:
-a file that is invalid will send an error message
-a file that is not found will send FNF
-a file that is too long will send a default message

Server: 
-bind it to socket so it can listen for instructions from the client
-Can read the filename from the client upto 255 characters
-sends file content back to the client or error

Client:
-can connect to the server
-sends filename request
-prints the server response

Pros:
-handles basic file errors
-the server informs the client of errors
Cons:
-only handles one client at a time
-can't read files longer than 255 characters
