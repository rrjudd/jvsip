# About

This is a distribution of a VSIPL library.

VSIPL is a signal processing library specification developed by a working group of
diverse individuals from industry and government.  University participation was generally
sponsored by government contract.  The acknowledgment page of the specification contains
information on participants and there institutions.

The specification **VSIPL 1.3 API** is available in the **doc** directory. This was the last
specification approved before the working group moved to the Object Management Group (OMG);
and the last version I was personally involved with.  I am not involved with the OMG or 
the version of the specification there.

## C version
This distribution supports the C VSIPL specification and includes the C spec and C Code 
(ANSI C89) with many (not all) of the functions defined by the spec.  There are many 
examples and test code.

The code is written from the ground up with standard C; and is the de-facto reference 
implementation for the C VSIPL specification.  No other third party library is needed 
to make the code so the implementation is very portable.

## C++ version

Currently a C++ API exists; developed by the HPEC-SI working group.

The C++ API includes both a serial and parallel spec. This distribution does not support 
the C++ API.  For C++ VSIPL information I would recommend searching for VSIPL and the OMG.

# Some History

The original VSIPL was done by a working group (started in about 1995) which was specific
to C VSIPL. 
The VSIPL working group morphed into the HPEC-SI working group (High Performance Embedded 
Computing - Software Initiative) which developed the C++ API's. Note HPEC-SI was not 
specific to VSIPL.

This distribution is based on the TVCPP distribution. I wrote TVCPP while a government employee
and have been maintaining it into retirement.  I placed it on github and renamed the distribution
to JVSIP to prevent it's demise from lack of support. The **Copyright** document contains
additional information.

The original goal of VSIPL is that anybody can implement a VSIPL Library. The idea was that
multiple (hardware) vendors would implement VSIPL instead of their proprietary library and
software would be more portable when new hardware is purchased. The reality has been more 
toward software vendors creating VSIPL libraries for multiple platforms. 

# Current Affairs

This distribution is open and free to anybody that wants to use or modify the source code 
for their own uses. Only source code is distributed and only the user is responsible for 
any result of using the distribution.

If you need things like performance and support please go to a commercial signal processing
library. I may (or may not) be willing to supply advice depending upon the work involved 
and my own agenda. I am retired now and this is a hobby for me. I might have better 
things to do with my time.

## Not C VSIPL

In retirement I have explored other programming paradigms besides C.  A lot of this work
made it's way into JVSIP.  

I spent a lot of time on python and there is a very complete
_Proof of Concept_ in the **python** directory.  There are notebooks in the **doc** directory
which demonstrate the python code.  

There is a **c++** directory which is NOT very complete.
I don't know C++ and have not had much success trying to use it. It was a big time waister
so I decided to quit working with C++. (In particular I don't like generics in Swift or C++)

I work on an Apple platform and have started using Swift as my main language.  Some of this
work shows up in the **AppleXcode** directory. There are several projects available in this
directory and your mileage may vary.


# Directories 
A short overview of directory structure. Some folks won't be interested in everything.  
Note there are various documents available on how to make and use things.

**jvsip**   
> top level directory, you may have cloned into something else

> **AppleXcode**    
>> Stuff particular to an Apple Environment with the Xcode IDE  
   
> **c_VSIP_src**  
>> C source code for VSIPL     

> **c_VSIP_testing**
>> Source code for testing VSIPL codes
      
> **doc**
>> Most (but not all) documents. Includes how to make and use information
>> These documents are PDF.
            
> **examples**  and **c_VSIP_example**
>> Examples. Note c_VSIP_testing also may be examined for examples of how to do VSIPL code
      
> **python**  
>> Python modules are in this directory  

