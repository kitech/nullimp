nginx模块编写精要：
config：
    这是一个shell脚本，用来设定模块相关变量，包括模块名，模块源文件
    变量列表：
    
build:
    ./configure  --prefix=/serv/stow/nginx --with-debug  --add-module=nullimp/ngx_nullimg

注意：
    修改nginx-1.2.9/auto/cc/gcc，把-Werror去掉，因为这个插件使用的是c++11参数，会产生一个warning，导致编译无法通过。

在nginx.conf中最上面添加：
location /nimp {
    nullimp;
}
调试时，可在配置文件加上daemon off;，方便输出调试。

在nginx模块中，也只能读取nginx配置的DocumentRoot目录下的文件。

是否有办法在修改模块配置后不重新编译所有的代码？


也许upstream能实现后端耗时模块的功能，http://www.pagefault.info/?p=251
需要做成php fastcgi模式，还需要另外的进行提供服务，这种方式也是不太行。
不过，可以学习着写一写upstream方式的nginx模板。


如果直接在worker进程进行阻塞式的处理的话，可以加大worker进程数的方式，
进程数设置到100-1000，也许也可以
加大进程数也不行

使用nginx的non-blocking delay between request and response机制。        
http://forum.nginx.org/read.php?29,89914,90013#msg-90013

nginx的clang编译：
    CC=clang CXX=clang++ ./configure ---------

学习nginx的资料：
http://code.google.com/p/nginxsrp/wiki/NginxCodeReview
    
主要配置：
worker_processes 16;
events {
    multi_accept off;
    accept_mutex on;
    accept_mutex_delay 1ms;
    worker_connections  32; # [3,n]
}

http {
    keepalive_timeout 0; #关掉keepalive

}


还是考虑使用nginx，把worker数放在，把每个worker的连接数设置为1,把keep-alive去掉，这样是否能保证在worker进程数的范围内不会阻塞，不会把多个请求放一个worker上执行吧。
这样应该能够模拟nginx的轮换式接收请求。


########
参数：
fu,file_uri=http|file|memcache|fastdfs://pathname
pe,process_engine=gmagick|imagick|opencv
qa,=1-100
sr,scale_rate=0.0-x.y
ss,scale_size=aXb
wartermark=

