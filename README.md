# Description
In this Mini project-1 ,I have created a customised shell prompt by myself in C programming language.
In this I have implemented the command which is warp,seek,peek,pastevents,proclore and all other commands which can be background or foreground. In this I have two linked lists first to store history of commands and other for pids of all background processes which havn't terminated yet.
# Assumptions
The main assumption I have taken is that I have not made a command named exit to exit the terminal as it is the part of part B and part c ,so it will not be in my pastevents.txt file and in linked list.
My peek . is also not working but peek. -a ,-al,-l and all other combinations are working.
Also in some commands like neonate and others if i do redirection then in file my prompt line is also writing due to some glitch.
Also sed command will not work as i have tokenize the command. If i put the whole command together in execvp then it works.
Also when i convert background process to foreground it converts but never terminates according to me as next prompt is not coming.
Also i iMan command due to network glitches sometimes it displays invalid command but it works after two or three times.
Piping is also not working if combined with redirection but if redirection of > is at last command then working but >> is not working. But normal redirection and normal piping is working properly.