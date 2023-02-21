
 Name:Lucas Rebelo


 To run, if Python is installed (python.exe set to default interpreter), simply double click the hashMap.py file
 or run the command line function below from a shell:
 
 
 Command line function :
 
	python hashMap.py [n]
	
	Where n is the size of the hash map. If n is left blank OR invalid, it will be set ot the default value
	
	Examples:
	
	python hashMap.py 1233
	
	python hashMap.py


 HashMap class implementation
 This class is a simple implementation of a fixed-size hash map
 that associates string keys with arbitrary data object references
 It stores lists (to handle collisions) of objects in a fixed-size array, mapped from a
 string key.
 The reason the hash map stores lists of objects, instead of the objects themselves
 is to handle cases of duplicate key -> value computations (with different keys!)
 known as collision and it is common with very short hash maps or with poor hash functions
 The number of entries in the HashMap refers to the number of lists (not keys) so the load()
 function maximum value stays 1
 
 I included a true_load() method which returns the load factor including
 collision cases handled in this implementation(all the keys stored in one entry of the hash map
 as opposed to all the entries). Naturally, this result can be more than 1.


 
 
