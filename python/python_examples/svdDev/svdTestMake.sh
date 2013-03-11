cc -o test_svd_f test_svd_f.c svd_f.c -I$HOME/local/src/jvsip/include -L$HOME/local/src/jvsip/lib -lvsip
cc -o test_svd_d test_svd_d.c svd_d.c -I$HOME/local/src/jvsip/include -L$HOME/local/src/jvsip/lib -lvsip
cc -o test_csvd_f test_csvd_f.c csvd_f.c -I$HOME/local/src/jvsip/include -L$HOME/local/src/jvsip/lib -lvsip
cc -o test_csvd_d test_csvd_d.c csvd_d.c -I$HOME/local/src/jvsip/include -L$HOME/local/src/jvsip/lib -lvsip
