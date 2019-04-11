import CryptoSwift
import Foundation
#if os(Linux) || os(FreeBSD)
import Glibc
#else
import Darwin
#endif

extension Array where Element == UInt8 {

    static func secureRandom(count: Int) -> [UInt8]? {
        var array = [UInt8](repeating: 0, count: count)

        let fd = open("/dev/urandom", O_RDONLY)
        guard fd != -1 else {
            return nil
        }
        defer {
            close(fd)
        }

        let ret = read(fd, &array, MemoryLayout<UInt8>.size * array.count)
        guard ret > 0 else {
            return nil
        }

        return array
    }
}

var hashed = false

var counter = 0
while !hashed {
    let password = Data([UInt8].secureRandom(count: 19)!)
    let hash = password.sha1()

    print(hash.toHexString())

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
