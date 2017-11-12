#  Swift JVsip (SJVsip)
A signal processig library.
## About
The  **SJVsip** project is an example of encapsulation of the **C VSIPL** library under a Swift object oriented wrapper.
## Example
```
    import vsip //Needed for some flags; for insance VSIP_ROW
    import SJVsip
    // a vector of length 10 and type double
    let aVector = Vector(length: 10, type: .d)
    //a Matrix of size (5,10) and type double
    let aMatrix = Matrix(collength: 5, rowlength: 10, type: .d, major: VSIP_ROW)
    //fill with some random data
    aVector.randn(8); aMatrix.randn(4)
    let output = Vector(length: aMatrix.collength, type: aMatrix.type)
    prod(aMatrix, aVector, outputIn: output)

```
