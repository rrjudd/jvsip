#!/bin/sh
cc -o svd_test_f svd_test_f.c svd.c -I$HOME/local/src/jvsip/include -L$HOME/local/src/jvsip/lib -lvsip
cc -o csvd_test_f csvd_test_f.c svd.c -I$HOME/local/src/jvsip/include -L$HOME/local/src/jvsip/lib -lvsip
cc -o svd_test_d svd_test_d.c svd.c -I$HOME/local/src/jvsip/include -L$HOME/local/src/jvsip/lib -lvsip
cc -o csvd_test_d csvd_test_d.c svd.c -I$HOME/local/src/jvsip/include -L$HOME/local/src/jvsip/lib -lvsip
