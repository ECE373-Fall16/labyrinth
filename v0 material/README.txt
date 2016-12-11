This code includes a sample XMLRPC client and server. 
The library is from here: http://xmlrpc-c.sourceforge.net/

You must first install the curl library:

sudo apt-get update
sudo apt-get install libcurl4-openssl-dev

The server shows how to setup XML-RPC to execute remote functions and
return the output. In this case, the example code shows you how to
transmit an array between the client and the server (rather than
add two numbers together).

To build, run:

$ make

To run, in one terminal run the server:

$ ./server

In another terminal, you can run the client:

$ ./client

A few notes on RPCs.  The examples here only passed integer.  
The client interface for the add example looks something like below:

myClient.call("http://localhost:8080/RPC2", "sample.add", "ii", &result, 5, 7);

Here, the "ii" specifies that the inputs to the remote sample.add function are two integers, 
which are then listed in order as the final parameters.  The first i is 5 and then the second i is 7.  
You can read the specifics of the "call" function's format here, along with a more complex example.

http://xmlrpc-c.sourceforge.net/doc/libxmlrpc_client++.html#call_simple_format

The "ii" is called a format string.  Of course, you can pass other primitive data types across 
the wire as well. The link below describes the possible ways to encode other data types, such as strings, arrays, etc.   
The example code on the calendar shows how to pass arrays.

http://xmlrpc-c.sourceforge.net/doc/libxmlrpc.html#formatstring

Finally, when implementing the RPCs, start from the example(s) in the starter code and 
make sure the RPCs themselves work before integrating with code.

