# **Friso**是什么？

Friso 是使用 c 语言开发的一款开源的高性能中文分词器，使用流行的mmseg算法实现。完全基于模块化设计和实现，可以很方便的植入其他程序中，
例如：MySQL，PHP，源码无需修改就能在各种平台下编译使用，加载完 20 万的词条，内存占用稳定为 14.5M.


# **Friso**核心功能：

- [x] 中文分词：mmseg算法 + **Friso** 独创的优化算法，四种切分模式。
- [ ] 关键字提取：基于textRank算法。
- [ ] 关键短语提取：基于textRank算法。
- [ ] 关键句子提取：基于textRank算法。


# **Friso**中文分词：

四种切分模式：
- [x] 简易模式：FMM 算法，适合速度要求场合。
- [x] 复杂模式- MMSEG 四种过滤算法，具有较高的岐义去除，分词准确率达到了98.41%。
- [x] 检测模式：只返回词库中已有的词条，很适合某些应用场合。(1.6.1版本开始)。
- [ ] 最多模式：细粒度切分，专为检索而生，除了中文处理外（不具备中文的人名，数字识别等智能功能）其他与复杂模式一致（英文，组合词等）。

1. 同时支持对 UTF-8/GBK 编码的切分，支持 php5 和 php7 扩展和 sphinx token 插件。
2. 支持自定义词库。在 dict 文件夹下，可以随便添加/删除/更改词库和词库词条，并且对词库进行了分类。
3. 简体/繁体/简体混合支持, 可以方便的针对简体，繁体或者简繁体切分。同时还可以以此实现简繁体的相互检索。
4. 支持中英/英中混合词的识别(维护词库可以识别任何一种组合)。例如：卡拉ok, 漂亮mm, c语言，IC卡，哆啦a梦。
5. 很好的英文支持，英文标点组合词识别, 例如c++, c#, 电子邮件，网址，小数，百分数。
6. 自定义保留标点：你可以自定义保留在切分结果中的标点，这样可以识别出一些复杂的组合，例如：c++, k&r，code.google.com。
7. 复杂英文切分的二次切分：默认 Friso 会保留数字和字母的原组合，开启此功能，可以进行二次切分提高检索的命中率。例如：qq2013会被切分成：qq/ 2013/ qq2013。
8. 支持阿拉伯数字/小数基本单字单位的识别，例如2012年，1.75米，5吨，120斤，38.6℃。
9. 自动英文圆角/半角，大写/小写转换。
10. 同义词匹配：自动中文/英文同义词追加. (需要在 friso.ini 中开启 friso.add_syn 选项)。
11. 自动中英文停止词过滤。(需要在 friso.ini 中开启 friso.clr_stw 选项)。
12. 多配置支持, 安全的应用于多进程/多线程环境。


# **Friso**快速体验：

#### 终端测试：

1. cd到 **Friso**根目录。
2. make
3. 运行：./src/friso -init ./friso.ini
4. 你将看到类似如下的终端界面
5. 在光标处输入文本开始测试

```
Initialized in 0.093152sec
Mode: Complex
+-Version: 1.6.2 (UTF-8)
+---------------------------------------------------------------+
| Friso - a Chinese word segmentation writen by c.              |
| bug report email - chenxin619315@gmail.com.                   |
| or: visit https://github.com/lionsoul2014/friso.              |
|     java edition for https://github.com/lionsoul2014/jcseg    |
| type 'quit' to exit the program.                              |
+---------------------------------------------------------------+
```

#### 测试样板：

##### 分词文本

~~~text
歧义和同义词:研究生命起源，混合词: 做B超检查身体，x射线本质是什么，今天去奇都ktv唱卡拉ok去，哆啦a梦是一个动漫中的主角，单位和全角: 2009年８月６日开始大学之旅，岳阳今天的气温为38.6℃, 也就是101.48℉, 英文数字: bug report example@gmail.com or visit http://code.google.com/p/jcseg, we all admire the hacker spirit!特殊数字: ① ⑩ ⑽ ㈩.
~~~

##### 分词结果：

~~~text
歧义 和 同义词 : 研究 琢磨 研讨 钻研 生命 起源 ， 混合词 : 做 b超 检查 身体 ， x射线 本质 是 什么 ， 今天 去 奇都ktv 唱 卡拉ok 去 ， 哆啦a梦 是 一个 动漫 中 的 主角 ， 单位 和 全角 : 2009年 8月 6日 开始 大学 之旅 ， 岳阳 今天 的 气温 为 38.6℃ , 也就是 101.48℉ , 英文 英语 数字 : bug report example gmail com example@gmail.com or visit http : / / code google com code.google.com / p / jcseg , we all admire appreciate like love enjoy the hacker spirit mind ! 特殊 数字 : .
~~~



# Friso 安装

### Linux:
cd到friso的根目录，运行：
```shell
make
sudo make install

# for testing
make testing
```
备注：如果是 64 位的系统，请将/usr/lib/libfriso.so 拷贝一份到/usr/lib64 中

### Winnt:
1. 使用 VS 编译得到 dll 和 lib 文件，具体可以参考 Friso 讨论：http://www.oschina.net/question/853816_135216
2. 使用 cygwin 从源码编译：
安装好 cygwin 后, 删除原有的 Makefile, 更改 Makefile.cygwin 为 Makefile, 打开 cygwin 的终端。
cd 到 Friso 的 src 目录，运行:
```shell
make
```
备注：在Friso的src目录下即可得到friso.exe和friso.dll文件。




# 相关附录

### 1，参考文献：
* 1，MMSEG算法原著：http://technology.chtsai.org/mmseg/


### 2，技术交流分享
* 1，旧版的参考pdf参考文献：请参考项目下的 friso-help-doc.pdf
* 2，使用案例典范：[RediSearch~信息检索](https://github.com/RediSearch/RediSearch)
* 3，NLP交流分享：微信：lionsoul2014(请备注Friso)，ＱＱ：1187582057(很少关注)

> This is the end line and thanks for reading !!!
