The program will have a few options. The first is to insert some (key, value) pairs into the database. This is accomplished as follows:

prompt> ./kv

prompt> ./kv p,10,100

prompt> ./kv p,20,200 p,40,400

This simple key-value store assumes that keys and values are integers

prompt> ./kv g,10

100

prompt>

Here you can see that when we get the key 10, the program prints out the key value.


The full list of commands are:

put: The format is p,key,value, where key is an integer, and value an intefer.

get: The format is g,key, where key is an integer.

delete: The format is d,key, which either deletes the relevant key-value pair (and prints nothing), or fails to do so (and prints K not found where K is the actual value of the key, i.e., some integer).

clear: The format is c. This command simply removes all key-value pairs from the database.

all: The format is a. This command prints out all key-value pairs in the database, in any order, with one key-value pair per line, each key and value separated by a comma.
