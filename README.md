# nm-otool

## - ft_nm : 

display name list (symbol table)

```
./ft_nm ft_otool
0000000100000000 T __mh_execute_header
                 U _exit
                 U _free
                 U _fstat$INODE64
0000000100001a30 T _ft_isdigit
0000000100000a80 T _ft_otool
0000000100001cb0 T _ft_putchar
0000000100001d30 T _ft_putendl
0000000100001ce0 T _ft_putstr
[...]
```


## - ft_otool

Disply content of text section

```
/ft_otool ft_nm
ft_nm:
Contents of (__TEXT,__text) section
0000000100000820	55 48 89 e5 41 57 41 56 53 50 49 89 d6 49 89 f7
0000000100000830	81 ff cf fa ed fe 75 20 41 83 f8 01 75 1a be 01
0000000100000840	00 00 00 41 b8 02 00 00 00 4c 89 ff 4c 89 f2 e8
0000000100000850	2c 06 00 00 31 db eb 28 81 ff cf fa ed fe 75 2d
0000000100000860	44 89 c0 83 c8 02 83 f8 02 75 22 31 db 31 f6 41
0000000100000870	b8 02 00 00 00 4c 89 ff 4c 89 f2 e8 00 06 00 00
0000000100000880	89 d8 48 83 c4 08 5b 41 5e 41 5f 5d c3 81 ff ce
0000000100000890	fa ed fe 75 1d 41 83 f8 01 75 17 be 01 00 00 00
00000001000008a0	b9 02 00 00 00 4c 89 ff 4c 89 f2 e8 00 08 00 00
00000001000008b0	eb a2 81 ff ce fa ed fe 75 1b 45 85 c0 75 16 31
[...]
```
