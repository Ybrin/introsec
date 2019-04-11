import XCTest

#if !canImport(ObjectiveC)
public func allTests() -> [XCTestCaseEntry] {
    return [
        testCase(overshade_hasherTests.allTests),
    ]
}
#endif
