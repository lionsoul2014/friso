Friso完整版本(词库, 词库管理工具, winNT下的dll文件, 开发帮助文档)下载: https://code.google.com/p/friso/ <br />

<h3>一. 关于Friso: </h3>
friso中文分词器friso是使用c语言开发的一个开源中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完20万的词条，内存占用稳定为13.5M．


1。目前最高版本：friso 1.4.0，只支持UTF-8编码。

2。mmseg四种过滤算法，分词准确率达到了98.41%，请参考本算法的原作：http://technology.chtsai.org/mmseg/。

3。支持自定义词库。在dict文件夹下，可以随便添加/删除/更改词库和词库词条，并且对词库进行了分类。

4。词库使用了friso的Java版本jcseg的简化词库。

5。支持中英/英中混合词的识别(维护词库可以识别任何一种组合)。例如：卡拉ok, 漂亮mm, c语言，IC卡，哆啦a梦。

7。很好的英文支持，英文标点组合词识别, 例如c++, c#, 电子邮件，网址，小数，分数，百分数。

8。支持阿拉伯数字/小数基本单字单位的识别，例如2012年，1.75米，5吨，120斤，38.6℃。

9。自动英文圆角/半角，大写/小写转换。

10。自动中英文同义词追加/同义词匹配. (需要在friso.ini中开启friso.add_syn选项)

11。自动中英文停止词过滤。(需要在friso.ini中开启friso.clr_stw选项)

12。提供friso.ini配置文件, 可以配置自定义分词. 如何配置friso


<h3>二。分词速度: </h3>

测试环境：2.8GHZ/2G/Ubuntu 

简单模式：3.8M/秒  

复杂模式：1.8M/秒

<h3>三。Friso其他主页: </h3> 
Friso官方主页: https://code.google.com/p/friso/ <br />
Friso开源中国: http://www.oschina.net/p/friso <br />
Friso开发帮助文档: http://git.oschina.net/lionsoul/friso/attach_files <br />

<h3>四。联系作者: </h3>
作者: 狮子的魂 <br />
email: chenxin619315@gmail.com <br />
qq: 1187582057 <br />

