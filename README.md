# Hey!
Uses hybrid encryption to store password of various applications. Written in cpp.
(What is hybrid encryption? Check [this]() out)
## Installation 
`unzip` the downloaded [source code .zip](https://github.com/ChrompyCoder/Shwifty-encrypted-password-manager/releases/latest) file in a folder with the permission to w/r/create new files.
Run the `runthis.cpp` file after compiling it on any c++ compiler.

Note:
The file which stores your password in encrypted form will be present in the folder which contains the `runthis.cpp` file.
To change it, add the complete location for `lockhead.txt` in the `runthis.cpp` file.

Now, chill and beep it?
## Advantages
- Pretty fast.
- Simple interface.
- Secure.
## Library used
[hash-library](https://github.com/stbrumme/hash-library) by @stbrumme
## Disadvantages
- Anyone can view your password file and manipulate it.( however, many applications have this so its not that big of a deal)
- Cannot store password of applications other than 6 (`[add new: a, discord: d, facebook: f, github: g, insta: i, mail:m, reddit: r]`). Cannot store custom application password.
## How can you contribute
- Add a simple GUI
- Add code to store custom application password.
- Add a block which prompts you to recheck the password of the application you just entered for storing.
- Provision to edit passwords/username.

Feel free to throw a [Pull Request](https://github.com/ChrompyCoder/Shwifty-encrypted-password-manager/compare).

### If you want to know the issues i faced while building this, check out this [blog](https://chrompycoder.github.io/blog/01.html).
