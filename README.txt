----- RVInjector Welcome Message -----

Thank you for downloading RVInjector.
To ensure optimal performance, I recommend placing both the executable and the DLL in your local Rumbleverse directory. While not mandatory, this practice helps prevent potential issues related to the program locating the DLL.

!!! IMPORTANT NOTICE !!!
DO NOT SEPARATE THE EXE AND THE DLL; ENSURE THEY RESIDE IN THE SAME DIRECTORY.
RVInjector relies on the presence of 'rumbleverse.dll' in the executable (RVInjetor's) directory.

If you encounter any issues or have questions, feel free to contact me on discord: nu11k3y

Disclaimer: Currently, RVInjector is optimized for the regular non-network test version of Rumbleverse. An issue has been identified with the NT version, and efforts are ongoing to resolve it. The error you may encounter is an EXCEPTION_ACCESS_VIOLATION reading address 0xffffffffffffffff, but this may also be due to the fact i modified my dllmain slightly in the VCXPROJ file for the SDK

For convenience, here is the error log:

here is the error: Unhandled Exception: EXCEPTION_ACCESS_VIOLATION reading address 0xffffffffffffffff

Rumbleverse!CG::FName::GetNameA() [A:\RumbleverseNT\Rumbleverse\SDK\BasicTypes_Package.cpp:648]
Rumbleverse!CG::FName::GetName() [A:\RumbleverseNT\Rumbleverse\SDK\BasicTypes_Package.cpp:670]
Rumbleverse!CG::UObject::GetName() [A:\RumbleverseNT\Rumbleverse\SDK\CoreUObject_Package.cpp:1100]
Rumbleverse!CG::UObject::GetFullName() [A:\RumbleverseNT\Rumbleverse\SDK\CoreUObject_Package.cpp:1123]
Rumbleverse!CG::UObject::FindObject<CG::UClass>() [A:\RumbleverseNT\Rumbleverse\SDK\CoreUObject_Classes.h:46]
Rumbleverse!CG::UObject::FindClass() [A:\RumbleverseNT\Rumbleverse\SDK\CoreUObject_Package.cpp:1144]
Rumbleverse!CG::APlayerController::StaticClass() [A:\RumbleverseNT\Rumbleverse\SDK\Engine_Package.cpp:23714]
Rumbleverse!CG::UObject::FindObjects<CG::APlayerController>() [A:\RumbleverseNT\Rumbleverse\SDK\CoreUObject_Classes.h:90]
Rumbleverse!projectKOMainThread() [A:\RumbleverseNT\Rumbleverse\dllmain.cpp:56]
kernel32
ntdll

i also got another error specifically mentioning an area around line 1560ish in the DLL itself. but its occasional. not sure whats causing it but ill look into it and see if it has anything to do with this injector specifically. or if it is specifically the DLL causing an issue. 


hope you enjoy! Happy Modding! -N0vaW01f

!---- Copyright Stuff ----! (This is required since i modified another persons program. you can read it if you feel like it) 

© 2009 Cypher, 2012-2023 Nefarius, 2023 N0vaW01f, All rights reserved.

Portions of this software were originally created by Cypher who initially wrote the injection-classes and Nefarius who wrote the rest of the command-line based injector. The original work is copyright protected, and all rights are reserved.

Modifications and enhancements to the original software have been made by N0vaW01f These contributions include but are not limited to:[Streamlined the source code to its essentials, eliminating the command-line interface operations for a seamless and automatic injection process. Enhanced injection efficiency, incorporated PID checks for precise Rumbleverse process identification, and implemented check code to verify the presence of 'Rumbleverse.dll' in the directory at all times unless modified and replaced, As well as elevating the user interface with vibrant colors and some neat ASCII ART. This ensures a sophisticated user experience. Experience effortless injection with just one click, epitomizing simplicity and efficiency." ]. N0vaW01f holds the copyright for these specific modifications.

All other aspects of the software remain the property of their respective copyright holders.

This software is distributed under the original license terms as provided by Cypher and Nefarius and is also subject to the MIT License for any additional modifications made. For details, refer to the original license agreement and the MIT License on GitHub or in the directory you are currently reading this in. The project follows the original MIT license and will be uploaded soon for open-source use on my GitHub. It upholds the values of transparency, collaboration, and open development.



--- Original GitHub Repo ---

https://github.com/nefarius/Injector


