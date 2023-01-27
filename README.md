# EXEC_LKM
A LKM (Loadable Kernel Module) to execute a command as root;  I include a example of using netcat and a compiled(with source and steps on how to compile) reverse shell provided in C.

References
- https://stackoverflow.com/questions/17803517/linux-execute-a-normal-process-from-a-kernel-thread
  - http://www.ibm.com/developerworks/library/l-user-space-apps/
- **[Beej's Guide to Network Programming Using Internet Sockets](https://gta.ufrj.br/ensino/eel878/sockets/)**

`see the version B of the EXEC_LKM.c file`
```
1. make
2. listen to the specified port -> load it WITH parameters
---> 
  **(using same port as the listener) (the listener can be nc)**
---> (app path, port, .. and even the prefix of the hiding-plugin!) (sudo insmod lkm.ko <param1="somevalue"> <param2="someothervalue">)
3. get a rev.shell -> do some really nasty stuff -> exit it -> test the rootkit hiding feature (it is now active!)
4. unload it

```

