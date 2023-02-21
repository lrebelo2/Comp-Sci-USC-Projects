# *************************************************************************
#  Name:Lucas Rebelo
#
#
#  HashMap class implementation
#  This class is a simple implementation of a fixed-size hash map
#  that associates string keys with arbitrary data object references
#  It stores lists (to handle collisions) of objects in a fixed-size array, mapped from a
#  string key.
#  The reason the hash map stores lists of objects, instead of the objects themselves
#  is to handle cases of duplicate key -> value computations (with different keys!)
#  known as collision and it is common with very short hash maps or with poor hash functions
#  The number of entries in the HashMap refers to the number of lists (not keys) so the load()
#  function maximum value stays 1

#
# *************************************************************************


import sys


class HashMap:
    # Helper class to store in the hash map. Contains the key and value pair
    # This is needed to compare keys in the same hash map entry (that happened due to collision)
    class Node:
        # Node class constructor
        def __init__(self, key, value):
            self.key = key
            self.value = value

    # HashMap class constructor
    def __init__(self, size=9973):
        self.hash_size = abs(int(size))
        self.number_of_entries = 0.0
        self.number_of_keys = 0.0
        self.data = [None for x in range(self.hash_size)]  # None instead of empty lists to save memory

    # is_in_list: Static helper function to navigate a list and search for a Node that contains
    #             the key in the argument. return None if key not present, or the value otherwise
    @staticmethod
    def is_in_list(key, list_test):
        for x in list_test:
            if key == x.key:
                return x
        return None

    # delete_from_list: Static helper function to navigate a list and search for a Node that contains
    #             the key in the argument.
    @staticmethod
    def delete_from_list(key, list_test):
        for x in list_test:
            if key == x.key:
                list_test.remove(x)
                return x
        return None

    # set: stores a given key, value pair in the hash map
    #      returns True/False on success/fail, respectively
    def set(self, key, value):
        if type(key) is str:
            node = self.Node(key, value)
            index = key.__hash__() % self.hash_size  # built-in hashing function
            if self.data[index] is None:
                self.data[index] = []
                self.number_of_entries += 1
                self.number_of_keys += 1
                self.data[index].append(node)
                return True
            else:
                x = self.is_in_list(key, self.data[index])
                if x is not None:
                    # update value
                    x.value = value
                    return True
                else:
                    self.number_of_keys += 1
                    self.data[index].append(node)
                    return True
        return False

    # get: gets the value in the hash map from a given string key
    #      returns the value of the key if present, otherwise None
    def get(self, key):
        if type(key) is str:
            index = key.__hash__() % self.hash_size
            if self.data[index] is None:
                return None
            else:
                x = self.is_in_list(key, self.data[index])
                if x is None:
                    return None
                else:
                    return x.value
        return None

    # get: deletes the entry in the hash map respective to a given string key
    #      returns the value of the key if present, otherwise None
    def delete(self, key):
        if type(key) is str:
            index = key.__hash__() % self.hash_size
            if self.data[index] is None:
                return None
            else:
                x = self.delete_from_list(key, self.data[index])
                if x is None:
                    return None
                else:
                    self.number_of_keys -= 1
                    if len(self.data[index]) == 0:
                        self.number_of_entries -= 1
                        self.data[index] = None
                    return x.value
        return None

    # load: returns a float value representing the load factor: number of entries /  size of hash map
    def load(self):
        return self.number_of_entries / self.hash_size

        # I included a true_load method which returns the load factor including
        # collision cases handled in this implementation(all the keys stored in one entry of the hash map
        # as opposed to all the entries). Naturally, this result can be more than 1.

    #
    #   true_load: returns a float value representing the load factor: number of stored keys /  size of hash map
    def true_load(self):
        return self.number_of_keys / self.hash_size


# Test the set method from HashMap class
def test_set(hash_map):
    print "\n   Testing set method:"

    print "     Storing 'dog' -> 'fish'"
    if hash_map.set('dog', 'fish'):
        print "         Storing successful!"
    else:
        print "         Storing unsuccessful"

    print "     Storing 'cat' -> 'mammal'"
    if hash_map.set('cat', 'mammal'):
        print "         Storing successful!"
    else:
        print "         Storing unsuccessful"

    print "     Storing 'salmon' -> 'fish'"
    if hash_map.set('salmon', 'fish'):
        print "         Storing successful!"
    else:
        print "         Storing unsuccessful"

    print "     Storing 'blue jay' -> 'bird'"
    if hash_map.set('blue jay', 'bird'):
        print "         Storing successful!"
    else:
        print "         Storing unsuccessful"

    print "     Storing 'dog' -> 'mammal'"
    if hash_map.set('dog', 'mammal'):
        print "         Storing successful! --updated value"
    else:
        print "         Storing unsuccessful"

    print "     Storing 1234 -> 'crustacean'"
    if hash_map.set(1234, 'crustacean'):
        print "         Storing successful! --updated value"
    else:
        print "         Storing unsuccessful -- invalid key type"


# Test the get method from HashMap class
def test_get(hash_map):
    print "\n   Testing get method:"

    print "     Getting 'dog'"
    if hash_map.get('dog') is not None:
        print "         Value:", hash_map.get('dog')
    else:
        print "         Key not present"

    print "     Getting 'horse'"
    if hash_map.get('horse') is not None:
        print "         Value:", hash_map.get('horse')
    else:
        print "         Key not present"


# Test the delete method from HashMap class
def test_delete(hash_map):
    print "\n   Testing delete method:"

    print "     Getting 'dog'"
    if hash_map.get('dog') is not None:
        print "         Value:", hash_map.get('dog')
    else:
        print "         Key not present"

    print "     Deleting 'dog'"
    print "         Deleted value: ", hash_map.delete('dog')

    print "     Getting 'dog' after delete"
    if hash_map.get('dog') is not None:
        print "         Value:", hash_map.get('dog')
    else:
        print "         Key not present"


# Test the load method from HashMap class
def test_load(hash_map):
    print "\n   Testing load method:"
    print "         Load:", hash_map.load()


# Test the true_load method from HashMap class
def test_true_load(hash_map):
    print "\n   Testing true_load method:"
    print "         True load:", hash_map.true_load()


print "\n\nLucas Rebelo's Hash Map class testing:"

# try and catch here?
if len(sys.argv[1:]) == 0:
    hashMap = HashMap(9973)
else:
    hash_size = sys.argv[1]
    try:
        hashMap = HashMap(hash_size)
    except ValueError:
        hashMap = HashMap()


test_set(hashMap)
test_get(hashMap)
test_delete(hashMap)
test_load(hashMap)
test_true_load(hashMap)
raw_input()
