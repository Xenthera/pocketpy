#pragma once

const char* __BUILTINS_CODE = R"(
def len(x):
    return x.__len__()

def __str4__mul__(self, n):
    return ''.join([self for _ in range(n)])
str.__mul__ = __str4__mul__

def __str4split(self, sep):
    if sep == "":
        return list(self)
    res = []
    i = 0
    while i < len(self):
        if self[i:i+len(sep)] == sep:
            res.append(self[:i])
            self = self[i+len(sep):]
            i = 0
        else:
            i += 1
    res.append(self)
    return res
str.split = __str4split

def __list4__repr__(self):
    a = []
    for i in self:
        a.append(repr(i))
    return '[' + ', '.join(a) + ']'
list.__repr__ = __list4__repr__

def __tuple4__repr__(self):
    a = []
    for i in self:
        a.append(repr(i))
    return '(' + ', '.join(a) + ')'
tuple.__repr__ = __tuple4__repr__

def __list4extend(self, other):
    for i in other:
        self.append(i)
list.extend = __list4extend

def __list4__mul__(self, n):
    a = []
    for i in range(n):
        a.extend(self)
    return a
list.__mul__ = __list4__mul__

def __iterable4__eq__(self, other):
    if len(self) != len(other):
        return False
    for i in range(len(self)):
        if self[i] != other[i]:
            return False
    return True
list.__eq__ = __iterable4__eq__
tuple.__eq__ = __iterable4__eq__

def __iterable4__contains__(self, item):
    for i in self:
        if i == item:
            return True
    return False
list.__contains__ = __iterable4__contains__
tuple.__contains__ = __iterable4__contains__

# https://github.com/python/cpython/blob/main/Objects/dictobject.c
class dict:
    def __init__(self):
        self._capacity = 8
        self._a = [None] * self._capacity
        self._len = 0
        
    def __len__(self):
        return self._len

    def __probe(self, key):
        i = hash(key) % self._capacity
        while self._a[i] is not None:
            if self._a[i][0] == key:
                return [True, i]
            i = ((5*i) + 1) % self._capacity
        return False,i

    def __getitem__(self, key):
        ok, i = self.__probe(key)
        if not ok:
            raise KeyError(key)
        return self._a[i][1]

    def __contains__(self, key):
        ok, i = self.__probe(key)
        return ok

    def __setitem__(self, key, value):
        ok, i = self.__probe(key)
        if ok:
            self._a[i][1] = value
        else:
            self._a[i] = [key, value]
            self._len += 1
            if self._len > self._capacity * 0.6:
                self.__resize_2x()

    def __delitem__(self, key):
        ok, i = self.__probe(key)
        if not ok:
            raise KeyError(key)
        self._a[i] = None
        self._len -= 1

    def __resize_2x(self):
        old_a = self._a
        self._capacity *= 2
        self._a = [None] * self._capacity
        self._len = 0
        for kv in old_a:
            if kv is not None:
                self[kv[0]] = kv[1]

    def keys(self):
        return [kv[0] for kv in self._a if kv is not None]

    def values(self):
        return [kv[1] for kv in self._a if kv is not None]

    def items(self):
        return [kv for kv in self._a if kv is not None]

    def __repr__(self):
        ret = '{'
        for kv in self.items():
            ret += repr(kv[0]) + ': ' + repr(kv[1]) + ', '
        if ret[-2:] == ', ':
            ret = ret[:-2]
        return ret + '}'

)";