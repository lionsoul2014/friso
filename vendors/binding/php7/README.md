# friso 的PHP扩展(php7版本, linux)

### 安装步骤
* git clone https://github.com/lionsoul2014/friso.git 到当前目录
* cd friso/src 安装 friso, 执行以下命令

    ~~~shell
    $ make 
    $ sudo make install
    ~~~

以上命令将会把 libfriso.so 安装到 /usr/lib, 同时将头文件安装到 ／usr/include/friso 
	 
* 在当前目录运行以下命令安装

        phpize
        ./configure
        make && sudo make install

* 配置 php 扩展文件 friso.ini 指定ini_file路径，(cli/fpm) 
    
        extension=friso.so
        friso.ini_file=/path/to/friso.ini // 这个文件是 friso 的配置文件, (查看 friso/friso.ini)

通常的做法是在 ／etc/php/7.0/mods-available 中新建 friso.ini, 然后分别在 cli 和 fpm
的 conf.d 目录下新建一个软链接指向上面的 /etc/php/7.0/mods-available/friso.ini

* 测试 
    
    demo 目录下有对应的测试脚本，执行
    
    ~~~shell
    $ cd demo
    $ php friso.fun.php
    ~~~

