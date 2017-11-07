#  About
Note that J is the first letter of my last name.  The letter V generaly stands for VSIPL (vector signal image processing library); a project I have worked on for years.  I am retired and do this as a hobby.  The AppleXcode directory is where I keep code specific to Apple.  So naming a swift project will generally include the letters V and J and S for swift.  This directory predates swift so also includes some efforts not including swift.
## JVSwift.workspace
Not everything in the AppleXcode directory falls under this workspace but a lot does.  In the begining I tried mightily to create an importable Swift module for C VSIPL.  The only way I could figure out how to make this work was to put everything in the same workspace.  That way playgrounds and other swift code could find my **vsip** module.
### vsip module
The vsip group contains the **vsip** module.  Make this first.  Be carefull.  The **c** source code contained in the **vsip** project is the same source code that is made for the **C VSIPL** library and is also used by the Python code.  It resides in the **c_VSIP_src** directory in the root of the **jvsip** project.
### Playgrounds
Examples of using the **vsip** module are in **example20, example18, and KOmegaBFEx*.

The **PngEx* playground doesn't really have anything to do with VSIPL.  Just figuring out how to do a bitmap.

Other playgrounds (like **TryIt*) are just for playing while trying to figure things out.

### SJVsip and SwiftVsip
These projects are proof of concept for encapsulating **C VSIPL** in an object oriented Swift module.  The **SJVsip** project is the newest effort.

### Other projects

I have some other projects where I am trying to learn how to use various features of Cocoa and other Xcode technologies.  They are not very complete.

The directory **jvsipF* is not part of the  JVSwift workspace.  It contains an earlier effort to build a C VSIPL framework.

