A simple program that copies files in accordance with the configuration file.
The configuration file must be in xml format. 
For each file, the configuration file must specify its name, the source path, and the path to copy the file to.

The program is written in c++, on linux Ubuntu 20.04.2 LTS.
Using the gcc version 9.3.0 compiler (Ubuntu 9.3.0-17ubuntu1~20.04).

1. To use it, clone the repository.
2. Do make to build the program.
3. Run ./programm.
4. Follow the instructions.

Example
Configuration file:

<config>
<file
source_path="C:\Windows\system32"
destination_path="C:\Program files"
file_name="kernel32.dll"
/>
<file
source_path="/var/log"
destination_path="/etc"
file_name="server.log"
/>
</config>
