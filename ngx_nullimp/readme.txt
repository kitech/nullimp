修改nginx-1.2.9/auto/cc/gcc，把-Werror去掉，因为这个插件使用的是c++11参数，会产生一个warning，导致编译无法通过。
