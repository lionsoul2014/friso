一. 关于Friso
friso是使用c语言开发的一个中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入到其他程序中，例如：MySQL，PHP等。
分词准确率高达98.41%。

详细介绍: https://code.google.com/p/friso/
Wiki文档: https://code.google.com/p/friso/w/list
开发API: https://code.google.com/p/friso/#四。使用方法

二. 如何安装:
cd src
make
sudo make install

三. 如何运行测试程序:
friso -lex {friso lex path}

#for example:
#the configuration file is in the $(HOME) dictionary name friso.ini
#try:
friso -init $(HOME)/friso.ini

四. 如何卸载
sudo rm /usr/local/bin/friso
 
作者: 狮子的魂
email: chenxin619315@gmail.com
qq: 1187582057

